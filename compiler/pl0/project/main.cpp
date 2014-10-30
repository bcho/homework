/*** PL0 compiler with code generation */

#ifdef CPP_BUILDER

#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

#define GET_STRING_LENGTH(s) (s.Length())

#else

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <string>
#include <sstream>

// Mock C++ builder's String.
using std::string;
typedef string String;

#define GET_STRING_LENGTH(s) (s.length())

string IntToStr(int n) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}

#endif  /* #ifdef CPP_BUILDER */


//------------------------------------------------------------------------
// Global Constants
//------------------------------------------------------------------------
#define NORW        19      /* Counts of reserviced keywords. */
#define IDMAX       10      /* Maximum length of identitys. */
#define TXMAX       100     /* Size of symbol table. */
#define LINEMAX     81      /* Maximum length of program line. */
#define NMAX        14      /* Max number of number digits. */
#define AMAX        2047    /* Maximum address. */
#define LEVMAX      3       /* Maximum nesting procedure level. */
#define CXMAX       200     /* Size of code storage. */
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Language Components
//------------------------------------------------------------------------
typedef enum {
    // basic symbols
    SYM_NUL, SYM_IDENT, SYM_NUMBER,

    // operators
    SYM_PLUS, SYM_MINUS, SYM_TIMES, SYM_OVER,
    SYM_ODD, SYM_EQL, SYM_NEQ, SYM_LSS, SYM_LEQ, SYM_GTR, SYM_GEQ,
    SYM_LPAREN, SYM_RPAREN, SYM_COMMA, SYM_SEMICOLON, SYM_PERIOD,
    SYM_ASSIGN, SYM_ADD_ASSIGN, SYM_SUB_ASSIGN, SYM_MUL_ASSIGN, SYM_DIV_ASSIGN,
    SYM_AND, SYM_OR, SYM_NOT,

    // keywords
    SYM_CONST, SYM_VAR, SYM_PROG, SYM_PROC,
    SYM_BEGIN, SYM_END, SYM_RETURN,
    SYM_IF, SYM_THEN, SYM_ELSE,
    SYM_WHILE, SYM_DO, SYM_UNTIL, SYM_FOR, SYM_STEP,
    SYM_WRITE, SYM_READ, SYM_CALL
} SYMBOL;

// symbols in string form.
const char *SYMOUT[] = {
    "NUL", "IDENT", "NUMBER",

    "PLUS", "MINUS", "TIMES", "OVER",
    "ODD", "EQ", "NEQ", "LSS", "LEQ", "GTR", "GEQ",
    "LPAREN", "RPAREN", "COMMA", "SEMICOLON", "PERIOD",
    "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN",
    "AND", "OR", "NOT",

    "CONST", "VAR", "PROGRAM", "PROCEDURE",
    "BEGIN", "END", "RETURN",
    "IF", "THEN", "ELSE",
    "WHILE", "DO", "UNTIL", "FOR", "STEP",
    "WRITE", "READ", "CALL"
};

#define SYMBOLS_COUNT ((int) (sizeof(SYMOUT) / sizeof(SYMOUT[0])))

// object type
typedef enum {
    KIND_CONSTANT,
    KIND_VARIABLE,
    KIND_PROCEDURE
} OBJECT_KIND;



typedef char ALFA[IDMAX+1];         /* identity container */

typedef struct {
    ALFA NAME;
    OBJECT_KIND KIND;
    union {
        int VAL;                    /* contant */
        struct {
            int LEVEL, ADDRESS, SIZE;
        } vp;                       /* variable/procedure reference */
    };
} TABLE_ITEM;                       /* symbol table item */
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Machine Instructions
//------------------------------------------------------------------------
// instruction function type
typedef enum {      /* TYP L A -- INSTRUCTION FORMAT */
    LIT,            /* LIT 0 A -- LOAD CONTANT A */
    OPR,            /* OPR 0 A -- EXECUTE OPR A */
    LOD,            /* LOD L A -- LOAD VARIABLE L FROM A */
    STO,            /* STO L A -- STORE VARIABLE L TO A */
    CAL,            /* CAL L A -- CALL PROCEDURE A AT LEVEL L */
    INI,            /* INI 0 A -- INCREMENT T-REGISTER BY A */
    JMP,            /* JMP 0 A -- JUMP TO A */
    JPC             /* JPC 0 A -- (CONDITIONAL) JUMP TO A */
} FUNCTION_TYPE;

#define INST_COUNT (JPC + 1)

typedef struct {
    FUNCTION_TYPE F;
    int L, A;
} INSTRUCTION;
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------
char CH;                        /* last read character */
SYMBOL SYM;                     /* last read symbol */
ALFA ID;                        /* last read identity */
int NUM;                        /* last read number */

// input buffer state
int CC;                         /* line buffer index */
int LL;                         /* line buffer length */
int LINENO;                     /* current line number */
char LINE[LINEMAX];             /* current line buffer */

int CX;                         /* code storage index */
INSTRUCTION CODE[CXMAX];        /* code storage */

ALFA KW_ALFA[NORW + 1];         /* keywords table, used for ident matching */
SYMBOL KW_SYMBOL[NORW + 1];     /* keyword symbols table, used for ident matching */
SYMBOL ASCII_SYMBOL[128];       /* ascii character symbol table */
ALFA INST_ALFA[INST_COUNT];     /* machine instruction table */

// symbols table
TABLE_ITEM TABLE[TXMAX];


FILE *FIN, *FOUT, *UIN;               /* STDIN/STDOUT/USER STDIN file object */
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Utilities
//------------------------------------------------------------------------

// Write a line to OUTPUT
//
// Default destination is FOUT,
// If CPP_BUILDER is defined, also write to the FORM.
void _writeln(const char *fmt, va_list args)
{
    vfprintf(FOUT, fmt, args);
    fprintf(FOUT, "\n");

#ifdef CPP_BUILDER
    Form1->vprintfs(fmt, args);
#endif /* #ifdef CPP_BUILDER */
}

// Write to OUTPUT
//
// Default destination is FOUT,
// If CPP_BUILDER is defined, also write to the FORM.
void _writeln(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    _writeln(fmt, args);
    va_end(args);
}

// Read from user input.
void _scanf(const char *fmt, ...)
{
    va_list args;

#ifdef CPP_BUILDER
    String input;
    
    input = InputBox("输入", "请键盘输入：", 0);
    va_start(args, fmt);
    vsscanf(input.c_str(), fmt, args);
    va_end(args);
#else

    _writeln("Please input:");
    va_start(args, fmt);
    vfscanf(UIN, fmt, args);
    va_end(args);
#endif /* #ifdef CPP_BUILDER */
}

// Don't panic!
void panic(int errorcode, const char *fmt, ...)
{
    va_list args;

    _writeln("error: %d", errorcode);

    va_start(args, fmt);
    _writeln(fmt, args);
    va_end(args);

#ifndef CPP_BUILDER
    exit(errorcode);
#endif  /* #ifdef CPP_BUILDER */
}

const std::string current_date_time()
{
    time_t now;
    struct tm datetime;
    char buf[80];

    now = time(0);
    datetime = *localtime(&now);
    strftime(buf, sizeof(buf), "%x %X", &datetime);

    return buf;
}

// Print something.
void log(const char *content)
{
    _writeln("//------------------------------------------------------------------------");
    _writeln("// %s", content);
    _writeln("// %s", current_date_time().c_str());
    _writeln("//------------------------------------------------------------------------");
}

// List generated instructions start from CX0.
void ListCode(int CX0)
{
    int i;
    String s;
    INSTRUCTION inst;

    for (i = CX0; i < CX; i++) {
        inst = CODE[i];

        s = IntToStr(i);
        while (GET_STRING_LENGTH(s) < 3)
            s = " " + s;
        s = s + " " + INST_ALFA[inst.F] + " " + IntToStr(inst.L) + " " + IntToStr(inst.A);
        _writeln(s.c_str());
    }
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Lexer
//------------------------------------------------------------------------
void ResetLineBuffer()
{
    LL = 0;
    CC = 0;
    CH = ' ';
}

void ResetLexer()
{
    ResetLineBuffer();

    LINENO = 0;
}

void GetCh()
{
    String s;

    if (CC == LL) {
        if (feof(FIN))
            panic(0, "unexpected EOF, maybe program is incomplete");

        ResetLineBuffer();
        LINENO = LINENO + 1;

        // read a line
        while (!feof(FIN) && CH != '\n') {
            CH = fgetc(FIN);
            LINE[LL++] = CH;
        }
        LINE[LL - 1] = ' '; LINE[LL] = 0;

        // list program.
        s = IntToStr(LINENO);
        while (GET_STRING_LENGTH(s) < 3)
            s = " " + s;
        s = s + " " + LINE;

        _writeln(s.c_str());
    }

    CH = LINE[CC++];
}

void GetSym()
{
    int i;
    ALFA ident;

    // skip whitespaces
    while (isspace(CH))
        GetCh();

    if (isalpha(CH)) {  /* ident/keyword */
        i = 0;
        do {
            if (i < IDMAX)
                ident[i++] = CH;
            GetCh();
        } while (isalnum(CH));
        ident[i] = 0;
        strcpy(ID, ident);
        SYM = SYM_IDENT;

        // check if the ident is a keyword
        for (i = 0; i < NORW; i++)
            if (strcasecmp(ID, KW_ALFA[i]) == 0) {
                SYM = KW_SYMBOL[i];
                break;
            }
    } /* ident/keyword */

    else if (isdigit(CH)) {   /* decimal number */
        SYM = SYM_NUMBER;
        i = 0; NUM = 0;
        do {
            NUM = 10 * NUM + (CH - '0');
            i++;
            GetCh();
        } while (isdigit(CH));

        if (i > NMAX)
            panic(30, "integer to large");
    } /* decimal number */

    else if (CH == ':') {   /* assignment */
        SYM = SYM_NUL;
        
        GetCh();
        if (CH == '=') {
            GetCh();
            SYM = SYM_ASSIGN;
        }
    } /* assignment */

    else if (CH == '+') {   /* plus/add assignment */
        SYM = SYM_PLUS;

        GetCh();
        if (CH == '=') {
            GetCh();
            SYM = SYM_ADD_ASSIGN;
        }
    } /* plus/add assignment */

    else if (CH == '-') {   /* minus/sub assignment */
        SYM = SYM_MINUS;

        GetCh();
        if (CH == '=') {
            GetCh();
            SYM = SYM_SUB_ASSIGN;
        }
    } /* minus/sub assignment */

    else if (CH == '*') {   /* times/multi assignment */
        SYM = SYM_TIMES;

        GetCh();
        if (CH == '=') {
            GetCh();
            SYM = SYM_MUL_ASSIGN;
        }
    } /* times/multi assignment */

    else if (CH == '/') {   /* over/div assignment/comment */
        SYM = SYM_OVER;

        GetCh();
        if (CH == '=') {
            GetCh();
            SYM = SYM_DIV_ASSIGN;
        } else if (CH == '*') {
            GetCh();

            // skip comments
            while (1) {
                if (CH == '*') {
                    GetCh();
                    if (CH == '/') {
                        GetCh();
                        break;  /* while (1) */
                    }
                }

                GetCh();
            }

            // Restart tokenizing.
            GetSym();
        }
    } /* over/div assignment */

    else if (CH == '>') {   /* >/>= */
        SYM = SYM_GTR;

        GetCh();
        if (CH == '=') {
            GetCh();
            SYM = SYM_GEQ;
        }
    } /* >/>= */

    else if (CH == '<') {   /* </<=/<> */
        SYM = SYM_LSS;

        GetCh();
        if (CH == '=') {
            GetCh();
            SYM = SYM_LEQ;
        } else if (CH == '>') {
            GetCh();
            SYM = SYM_NEQ;
        }
    } /* </<= */

    else if (CH == '&') {   /* && */
        GetCh();

        if (CH == '&') {
            GetCh();
            SYM = SYM_AND;
        } else {
            SYM = SYM_NUL;
        }
    } /* && */

    else if (CH == '|') {   /* || */
        GetCh();

        if (CH == '|') {
            GetCh();
            SYM = SYM_OR;
        } else {
            SYM = SYM_NUL;
        }
    } /* || */

    else {  /* ascii character symbols */
        SYM = ASCII_SYMBOL[(int) CH];
        GetCh();
    }
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Machine
//------------------------------------------------------------------------
// Generate instruction.
// Returns new instruction filled address.
int GEN(FUNCTION_TYPE F, int L, int A)
{
    int filled_cx;

    if (CX > CXMAX)
        panic(0, "program too long");
    filled_cx = CX;

    CODE[CX].F = F;
    CODE[CX].L = L;
    CODE[CX].A = A;
    CX = CX + 1;

    return filled_cx;
}

// Calculate base address for B with level L.
int BASE(int L, int B, int S[])
{
    int B1 = B;

    while (L > 0) {
        B1 = S[B1];
        L = L - 1;
    }

    return B1;
}

void Interpret()
{
    const int STACKSIZE = 500;
    int P, B, T;                                /* program registers */
    INSTRUCTION I;
    int S[STACKSIZE];                           /* data storage */

    T = 0; B = 1; P = 0;
    S[1] = 0; S[2] = 0; S[3] = 0;

    do {
        I = CODE[P++];
        switch (I.F) {
            case LIT:                           /* load constant */
                T = T + 1;
                S[T] = I.A;
                break; /* case LIT */
            
            case OPR:                           /* execute operation */
                switch (I.A) {
                    case 0:                     /* return */
                        T = B - 1;
                        P = S[T + 3];
                        B = S[T + 2];
                        break;
                    case 1:                     /* -A */
                        S[T] = -S[T];
                        break;
                    case 2:                     /* A + B */
                        T = T - 1;
                        S[T] = S[T] + S[T + 1];
                        break;
                    case 3:                     /* A - B */
                        T = T - 1;
                        S[T] = S[T] - S[T + 1];
                        break;
                    case 4:                     /* A * B */
                        T = T - 1;
                        S[T] = S[T] * S[T + 1];
                        break;
                    case 5:                     /* A / B */
                        T = T - 1;
                        S[T] = S[T] / S[T + 1];
                        break;
                    case 6:                     /* ODD A */
                        S[T] = S[T] % 2 != 0;
                        break;
                    case 7:                     /* !A */
                        S[T] = ! S[T];
                        break;
                    case 8:                     /* A == B */
                        T = T - 1;
                        S[T] = S[T] == S[T + 1];
                        break;
                    case 9:                     /* A != B */
                        T = T - 1;
                        S[T] = S[T] != S[T + 1];
                        break;
                    case 10:                    /* A < B */
                        T = T - 1;
                        S[T] = S[T] < S[T + 1];
                        break;
                    case 11:                    /* >= */
                        T = T - 1;
                        S[T] = S[T] >= S[T + 1];
                        break;
                    case 12:                    /* > */
                        T = T - 1;
                        S[T] = S[T] > S[T + 1];
                        break;
                    case 13:                    /* <= */
                        T = T - 1;
                        S[T] = S[T] <= S[T + 1];
                        break;
                    case 14:                    /* write to stdout */
                        _writeln("%d", S[T--]);
                        break;
                    case 15:                    /* write '\n' to stdout */
                        _writeln("");
                        break;
                    case 16:                    /* read from stdin */
                        T = T + 1;
                        _scanf("%d", &S[T]);
                        break;
                    case 17:                    /* A && B */
                        T = T - 1;
                        S[T] = S[T] && S[T + 1];
                        break;
                    case 18:                    /* A || B */
                        T = T - 1;
                        S[T] = S[T] || S[T + 1];
                        break;
                    default:
                        panic(0, "Interpret: unknown op code: %d", I.A);
                } /* switch I.A */
                break; /*case OPR */

            case LOD:                           /* load variable */
                T = T + 1;
                S[T] = S[BASE(I.L, B, S) + I.A];
                break; /* case LOD */

            case STO:                           /* store variable */
                S[BASE(I.L, B, S) + I.A] = S[T];
                T = T - 1;
                break; /* case STO */

            case CAL:                           /* call procedure */
                S[T + 1] = BASE(I.L, B, S);
                S[T + 2] = B;
                S[T + 3] = P;
                B = T + 1;
                P = I.A;
                break; /* case CAL */

            case INI:                           /* increment */
                T = T + I.A;
                break; /* cae INI */

            case JMP:                           /* unconditional jump */
                P = I.A;
                break; /* case JMP */

            case JPC:                           /* false jump */
                if (S[T] == 0)
                    P = I.A;
                T = T - 1;
                break; /* case JPC */
        }
    } while (P != 0);
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Symbol Table
//------------------------------------------------------------------------
// Record an entity into symbol table.
// TODO DX?
// TODO clean ID.
void ENTER(OBJECT_KIND kind, int level, int &TX, int &DX)
{
    TX = TX + 1;

    strcpy(TABLE[TX].NAME, ID);
    TABLE[TX].KIND = kind;

    switch (kind) {
        case KIND_CONSTANT:
            TABLE[TX].VAL = NUM;
            break;
        case KIND_VARIABLE:
            TABLE[TX].vp.LEVEL = level;
            TABLE[TX].vp.ADDRESS = DX;
            DX = DX + 1;
            break;
        case KIND_PROCEDURE:
            TABLE[TX].vp.LEVEL = level;
            break;
    }
}

// Find identity's position.
// Return 0 if not found.
int POSITION(ALFA ID, int TX)
{
    int i;

    for (i = TX; i > 0; i--)
        if (strcmp(TABLE[i].NAME, ID) == 0)
            return i;

    return 0;
}

// Get an identity.
// Panic if not found.
void GET_IDENT(ALFA id, int TX, TABLE_ITEM *item)
{
    int pos;

    pos = POSITION(id, TX);
    if (pos == 0)
        panic(0, "unable to find identity: %s", id);

    *item = TABLE[pos];
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Parser
//------------------------------------------------------------------------
void parse_program(int, int &);
void parse_block(int, int &);
void parse_const(int, int &, int &);
void parse_var(int, int &, int &);
void parse_procedure(int, int &, int &);
void parse_statement(int, int &);
void parse_assignment(int, int &);
void parse_if(int, int &);
void parse_while(int, int &);
// TODO make it as expression.
void parse_call(int, int &);
void parse_read(int, int &);
void parse_write(int, int &);

// expression groups
void parse_expression(int, int &);
void parse_or_cond(int, int &);
void parse_and_cond(int, int &);
void parse_relational(int, int &);
void parse_additive(int, int &);
void parse_multive(int, int &);
void parse_unary(int, int &);
void parse_factor(int, int &);


/*
 * Grammar:
 *
 *  PROGRAM-BLOCK ::= PROGRAM IDENT; BLOCK "."
 */
void parse_program(int level, int &TX)
{
    if (SYM != SYM_PROG)
        panic(0, "PROGRAM-BLOCK: expect PROGRAM, got: %s", SYMOUT[SYM]);
    GetSym();

    if (SYM != SYM_IDENT)
        panic(0, "PROGRAM-BLOCK: expect program name, got: %s", SYMOUT[SYM]);
    GetSym();

    if (SYM != SYM_SEMICOLON)
        panic(5, "PROGRAM-BLOCK: expect ';', got: %s", SYMOUT[SYM]);
    GetSym();

    parse_block(level, TX);

    if (SYM != SYM_PERIOD)
        panic(9, "PROGRAM-BLOCK: expect '.', got: %s", SYMOUT[SYM]);
}

/*
 * Grammar:
 *
 *   BLOCK ::= {CONST-BLOCK} {VAR-BLOCK} [PROCEDURE-BLOCK] STATEMENT
 *
 * Instructions Layout:
 *
 * TODO
 * +----------------------------------------------------+
 * |                                                    |
 * |                block instructions                  |
 * |                                                    |
 * +----------------------------------------------------+
 */
void parse_block(int level, int &TX)
{
    int DX, TX0, CX0;

    DX = 3;                                 /* data storage index */
    TX0 = TX;                               /* initial table index */
    CX0 = CX;                               /* initial code index */
    TABLE[TX].vp.ADDRESS = CX;              /* body entry address */
    GEN(JMP, 0, 0);

    if (level > LEVMAX)
        panic(32, "BLOCK: level too deep: %d", level);

    if (SYM == SYM_CONST)
        parse_const(level, TX, DX);
    if (SYM == SYM_VAR)
        parse_var(level, TX, DX);
    while (SYM == SYM_PROC)
        parse_procedure(level, TX, DX);

    CODE[TABLE[TX0].vp.ADDRESS].A = CX;
    TABLE[TX0].vp.ADDRESS = CX;                 /* start address of body (?) */
    TABLE[TX0].vp.SIZE = DX;                    /* size of data segment */
    GEN(INI, 0, DX);

    parse_statement(level, TX);
    GEN(OPR, 0, 0);                             /* return */
}

/*
 * Grammar:
 *
 *  CONST-BLOCK ::= CONST IDENT "=" NUMBER ["," IDENT "=" NUMBER] ";"
 */
void parse_const(int level, int &TX, int &DX)
{
    if (SYM != SYM_CONST)
        panic(0, "CONST-BLOCK: expect CONST, got: %s", SYMOUT[SYM]);
    GetSym();

    do {
        if (SYM != SYM_IDENT)
            panic(4, "CONST-BLOCK: expect IDENT, got: %s", SYMOUT[SYM]);
        GetSym();

        if (SYM != SYM_EQL)
            panic(4, "CONST-BLOCK: expect '=', got: %s", SYMOUT[SYM]);
        GetSym();

        if (SYM != SYM_NUMBER)
            panic(3, "CONST-BLOCK: expect NUMBER, got: %s", SYMOUT[SYM]);
        ENTER(KIND_CONSTANT, level, TX, DX);
        GetSym();

        if (SYM != SYM_COMMA)
            break;
        GetSym();
    } while (SYM != SYM_SEMICOLON);

    if (SYM != SYM_SEMICOLON)
        panic(0, "CONST-BLOCK: expect ';', got: %s", SYMOUT[SYM]);
    GetSym();
}

/*
 * Grammar:
 *
 *  VAR-BLOCK ::= VAR IDENT ["," IDENT] ";"
 */
void parse_var(int level, int &TX, int &DX)
{
    if (SYM != SYM_VAR)
        panic(0, "VAR-BLOCK: expect VAR, got: %s", SYMOUT[SYM]);
    GetSym();

    do {
        if (SYM != SYM_IDENT)
            panic(4, "VAR-BLOCK: expect IDENT, got: %s", SYMOUT[SYM]);
        ENTER(KIND_VARIABLE, level, TX, DX);
        GetSym();

        if (SYM != SYM_COMMA)
            break;
        GetSym();
    } while (SYM != SYM_SEMICOLON);

    if (SYM != SYM_SEMICOLON)
        panic(0, "VAR-BLOCK: expect ';', got: %s", SYMOUT[SYM]);
    GetSym();
}

/*
 * Grammar:
 *
 *  PROCEDURE-BLOCK ::= PROCEDURE IDENT ";" BLOCK ";"
 */
void parse_procedure(int level, int &TX, int &DX)
{
    if (SYM != SYM_PROC)
        panic(0, "PROCEDURE-BLOCK: expect PROCEDURE, got: %s", SYMOUT[SYM]);
    GetSym();

    if (SYM != SYM_IDENT)
        panic(4, "PROCEDURE-BLOCK: expect identity, got: %s", SYMOUT[SYM]);
    ENTER(KIND_PROCEDURE, level, TX, DX);
    GetSym();

    if (SYM != SYM_SEMICOLON)
        panic(5, "PROCEDURE-BLOCK: expect ';', got: %s", SYMOUT[SYM]);
    GetSym();

    parse_block(level + 1, TX);

    if (SYM != SYM_SEMICOLON)
        panic(5, "PROCEDURE-BLOCK: expect ';', got: %s", SYMOUT[SYM]);
    GetSym();
}

/*
 * Grammar:
 *
 *  STATEMENT ::= BEGIN STATEMENT [";" STATEMENT] END
 *              | ASSIGN-STMT
 *              | CALL-STMT
 *              | IF-STMT
 *              | WHILE-STMT
 *              | CALL-STMT
 *              | READ-STMT
 *              | WRITE-STMT
 */
void parse_statement(int level, int &TX)
{
    switch (SYM) {
        case SYM_IDENT:
            parse_assignment(level, TX);
            break;
        case SYM_IF:
            parse_if(level, TX);
            break;
        case SYM_WHILE:
            parse_while(level, TX);
            break;
        case SYM_CALL:
            parse_call(level, TX);
            break;
        case SYM_READ:
            parse_read(level, TX);
            break;
        case SYM_WRITE:
            parse_write(level, TX);
            break;
        case SYM_BEGIN:
            GetSym();

            parse_statement(level, TX);

            while (SYM == SYM_SEMICOLON) {
                GetSym();
                parse_statement(level, TX);
            }

            if (SYM != SYM_END)
                panic(17, "STATEMENT: expect END, got: %s", SYMOUT[SYM]);
            GetSym();

            break;
        default:
            panic(0, "STATEMENT: unexpected token: %s", SYMOUT[SYM]);
    }
}

/*
 * Grammar:
 *
 *  ASSIGNMENT ::= IDENT ASSIGNOP EXPRESSION
 *  ASSIGNOP ::= ":=" | "+=" | "-=" | "*=" | "/="
 */
void parse_assignment(int level, int &TX)
{
    TABLE_ITEM ident;
    SYMBOL assign_op;
    int op_code;

    GET_IDENT(ID, TX, &ident);
    if (ident.KIND != KIND_VARIABLE)
        panic(12, "ASSIGNMENT: cannot assign to non-variable %s", ID);
    GetSym();

    if (SYM != SYM_ASSIGN && SYM != SYM_ADD_ASSIGN && SYM != SYM_SUB_ASSIGN
        && SYM != SYM_MUL_ASSIGN && SYM != SYM_DIV_ASSIGN)
        panic(13, "ASSIGNMENT: unexpected token: %s", SYMOUT[SYM]);
    assign_op = SYM;
    GetSym();

    if (assign_op == SYM_ASSIGN) {
        // calculate right side value
        parse_expression(level, TX);
    } else {
        // load variable
        GEN(LOD, level - ident.vp.LEVEL, ident.vp.ADDRESS);

        // calculate right side value
        parse_expression(level, TX);

        // calculate new value
        switch (assign_op) {
            case SYM_ADD_ASSIGN: op_code = 2; break;
            case SYM_SUB_ASSIGN: op_code = 3; break;
            case SYM_MUL_ASSIGN: op_code = 4; break;
            case SYM_DIV_ASSIGN: op_code = 5; break;
            default:
                panic(0, "ASSIGNMENT: unsupported operator: %s", SYMOUT[assign_op]);
        }
        GEN(OPR, 0, op_code);
    }

    // store value
    GEN(STO, level - ident.vp.LEVEL, ident.vp.ADDRESS);
}

/*
 * Grammar:
 *
 *  IF-STMT ::= IF EXPRESSION THEN STATEMENT
 *            | IF EXPRESSION THEN STATEMENT ELSE STATEMENT
 *
 * Instructions Layout:
 * +----------------------------------------------------+
 * |                                                    |
 * |                    conditions                      |
 * |                                                    |
 * +----------------------------------------------------+
 * |                JPC 0 THEN_PC                       |
 * +----------------------------------------------------+
 * |                                                    |
 * |                then-stmt                           |
 * |                                                    |
 * +----------------------------------------------------+ <- THEN_PC
 * |                JMP 0 ELSE_PC (if ELSE exists)      |
 * +----------------------------------------------------+
 * |                                                    |
 * |                else-stmt (if ELSE exists)          |
 * |                                                    |
 * +----------------------------------------------------+ <- ELSE_PC (*)
 *
 * * If ELSE is not presented, THEN_PC should be exactly ELSE_PC.
 */
void parse_if(int level, int &TX)
{
    int cond_jmp_cx, then_jmp_cx;

    GetSym();

    // parse condition
    parse_expression(level, TX);
    cond_jmp_cx = GEN(JPC, 0, 0);

    // parse then part
    if (SYM != SYM_THEN)
        panic(16, "IF-STMT: expected THEN, got: %s", SYMOUT[SYM]);
    GetSym();
    parse_statement(level, TX);

    // parse else part if exists
    if (SYM == SYM_ELSE) {
        GetSym();

        then_jmp_cx = GEN(JMP, 0, 0);
        CODE[cond_jmp_cx].A = CX;
        parse_statement(level, TX);
        CODE[then_jmp_cx].A = CX;
    } else {
        CODE[cond_jmp_cx].A = CX;
    }
}

/*
 * Grammar:
 *
 *  WHILE-STMT ::= WHILE EXPRESSION DO STATEMENT
 *
 * Instructions Layout:
 * +----------------------------------------------------+ <- WHILE_CX
 * |                                                    |
 * |                    conditions                      |
 * |                                                    |
 * +----------------------------------------------------+
 * |                    JPC 0 OUT_CX                    |
 * +----------------------------------------------------+
 * |                                                    |
 * |                    loop body                       |
 * |                                                    |
 * +----------------------------------------------------+
 * |                    JMP WHILE_CX                    |
 * +----------------------------------------------------+ <- OUT_CX
 */
void parse_while(int level, int &TX)
{
    int while_cx, cond_jmp_cx;

    GetSym();

    while_cx = CX;

    // parse expression
    parse_expression(level, TX);
    cond_jmp_cx = GEN(JPC, 0, 0);
    
    if (SYM != SYM_DO)
        panic(18, "WHILE-STMT: expect DO, got: %s", SYMOUT[SYM]);
    GetSym();

    // parse body
    parse_statement(level, TX);
    GEN(JMP, 0, while_cx);
    
    // back patch
    CODE[cond_jmp_cx].A = CX;
}

/*
 * Grammar:
 *
 *  CALL-STMT ::= CALL IDENT
 */
void parse_call(int level, int &TX)
{
    TABLE_ITEM ident;

    GetSym();

    if (SYM != SYM_IDENT)
        panic(14, "CALL-STMT: expected procedure name, got: %s", SYMOUT[SYM]);
    
    GET_IDENT(ID, TX, &ident);
    if (ident.KIND != KIND_PROCEDURE)
        panic(15, "CALL-STMT: %s should be a procedure", ID);

    GEN(CAL, level - ident.vp.LEVEL, ident.vp.ADDRESS);
    GetSym();
}

/*
 * Grammar:
 *
 *  READ-STMT ::= READ "(" IDENT, ["," IDENT] ")"
 */
void parse_read(int level, int &TX)
{
    TABLE_ITEM ident;

    GetSym();

    if (SYM != SYM_LPAREN)
        panic(34, "READ-STMT: expect '(', got: %s", SYMOUT[SYM]);

    do {
        GetSym();
        if (SYM != SYM_IDENT)
            panic(35, "READ-STMT: expect identity, got: %s", SYMOUT[SYM]);

        GET_IDENT(ID, TX, &ident);
        if (ident.KIND != KIND_VARIABLE)
            panic(35, "READ-STMT: identity %s should be variable", ID);
        GEN(OPR, 0, 16);
        GEN(STO, level - ident.vp.LEVEL, ident.vp.ADDRESS);
        
        GetSym();
    } while (SYM == SYM_COMMA);

    if (SYM != SYM_RPAREN)
        panic(33, "READ-STMT: expected ')', got: %s", SYMOUT[SYM]);
    GetSym();
}

/*
 * Grammar:
 *
 *  WRITE-STMT ::= WRITE "(" EXPRESSION,  ["," EXPRESSION] ")"
 *               | WRITE
 */
void parse_write(int level, int &TX)
{
    GetSym();
    if (SYM == SYM_LPAREN) {
        GetSym();

        parse_expression(level, TX);
        GEN(OPR, 0, 14);
        while (SYM == SYM_COMMA) {
            GetSym();

            parse_expression(level, TX);
            GEN(OPR, 0, 14);
        }

        if (SYM != SYM_RPAREN)
            panic(33, "WEITE-STMT: expected ')', got: %s", SYMOUT[SYM]);
        GetSym();
    } /* SYM == SYM_LPAREN */
    
    else {
        GEN(OPR, 0, 15);
    }
}

void parse_expression(int level, int &TX)
{
    parse_or_cond(level, TX);
}

/*
 * Grammar:
 *
 *  OR_COND ::= AND_COND ["||" OR_COND]
 */
void parse_or_cond(int level, int &TX)
{
    parse_and_cond(level, TX);

    while (SYM == SYM_OR) {
        GetSym();

        parse_and_cond(level, TX);
        GEN(OPR, 0, 18);
    }
}

/*
 * Grammar:
 *
 *  AND_COND ::= RELATIONAL ["&&" RELATIONAL]
 */
void parse_and_cond(int level, int &TX)
{
    parse_relational(level, TX);

    while (SYM == SYM_AND) {
        GetSym();

        parse_relational(level, TX);
        GEN(OPR, 0, 17);
    }
}

/*
 * Grammar:
 *
 *  RELATIONAL ::= ADDITIVE [RELOP ADDITIVE]
 *               | ODD ADDITIVE
 *  RELOP ::= "=" / "<" / "<=" / ">" / ">=" / "<>"
 */
void parse_relational(int level, int &TX)
{
    SYMBOL rel_symbol;
    int op_code;

    if (SYM == SYM_ODD) {
        GetSym();

        parse_additive(level, TX);
        GEN(OPR, 0, 6);
    } /* SYM == SYM_ODD */

    else {
        parse_additive(level, TX);
        while (SYM == SYM_EQL || SYM == SYM_NEQ
               || SYM == SYM_LSS || SYM == SYM_LEQ
               || SYM == SYM_GTR || SYM == SYM_GEQ) {
            rel_symbol = SYM;
            GetSym();
            parse_additive(level, TX);

            switch (rel_symbol) {
                case SYM_EQL: op_code = 8;  break;
                case SYM_NEQ: op_code = 9;  break;
                case SYM_LSS: op_code = 10; break;
                case SYM_GEQ: op_code = 11; break;
                case SYM_GTR: op_code = 12; break;
                case SYM_LEQ: op_code = 13; break;
                default:
                    panic(0, "RELATIONAL: unknown operator: %s", SYMOUT[SYM]);
            }
            GEN(OPR, 0, op_code);
        }
    }
}

/*
 * Grammar:
 *
 *  ADDITIVE ::= MULTIVE ["+" / "-" MULTIVE]
 */
void parse_additive(int level, int &TX)
{
    SYMBOL op_symbol;

    parse_multive(level, TX);
    while (SYM == SYM_PLUS || SYM == SYM_MINUS) {
        op_symbol = SYM;
        GetSym();

        parse_multive(level, TX);

        if (op_symbol == SYM_PLUS)
            GEN(OPR, 0, 2);
        else
            GEN(OPR, 0, 3);
    }
}

/*
 * Grammar:
 *
 *  MULTIVE ::= UNARY ["*" / "/" UNARY]
 */
void parse_multive(int level, int &TX)
{
    SYMBOL op_symbol;

    parse_unary(level, TX);
    while (SYM == SYM_TIMES || SYM == SYM_OVER) {
        op_symbol = SYM;
        GetSym();

        parse_unary(level, TX);

        if (op_symbol == SYM_TIMES)
            GEN(OPR, 0, 4);
        else
            GEN(OPR, 0, 5);
    }
}

/*
 * Grammar:
 *
 *  UNARY ::= ["-" / "+" / "!"] UNARY
 *          | FACTOR
 */
void parse_unary(int level, int &TX)
{
    if (SYM == SYM_MINUS) {
        GetSym();
        parse_unary(level, TX);
        GEN(OPR, 0, 1);
    } /* SYM == SYM_MINUS */
    
    else if (SYM == SYM_PLUS) {
        GetSym();
        parse_unary(level, TX);
    } /* SYM == SYM_PLUS */

    else if (SYM == SYM_NOT) {
        GetSym();
        parse_unary(level, TX);
        GEN(OPR, 0, 7);
    } /* SYM == SYM_NOT */

    else {
        parse_factor(level, TX);
    }
}

/*
 * Grammar:
 *
 *  FACTOR ::= IDENT
 *           | NUMBER
 *           | "(" EXPRESSION ")"
 */
void parse_factor(int level, int &TX)
{
    TABLE_ITEM ident;

    if (SYM == SYM_IDENT) {
        GET_IDENT(ID, TX, &ident);
        switch (ident.KIND) {
            case KIND_CONSTANT:
                GEN(LIT, 0, ident.VAL);
                break;
            case KIND_VARIABLE:
                // TODO address calculating
                GEN(LOD, level - ident.vp.LEVEL, ident.vp.ADDRESS);
                break;
            default:
                panic(21, "FACTOR: identity %s type should be CONST or VARIABLE", ID);
        }
        GetSym();
    } /* SYM == SYM_IDENT */

    else if (SYM == SYM_NUMBER) {
        // FIXME why this check?
        if (NUM > AMAX) {
            panic(31, "FACTOR: number too large: %d", NUM);
            NUM = 0;
        }

        GEN(LIT, 0, NUM);
        GetSym();
    } /* SYM == SYM_NUMBER */

    else if (SYM == SYM_LPAREN) {
        GetSym();

        parse_expression(level, TX);

        if (SYM != SYM_RPAREN)
            panic(22, "missing `)`");
        GetSym();
    } /* SYM == SYM_LPAREN */

    else {
        panic(0, "FACTOR: unexpected symbol: %s", SYMOUT[SYM]);
    }
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Main Program
//------------------------------------------------------------------------

// Setup language components.
void SetupLanguage()
{
    int i;

    for (i = 0; i < 128; i++)
        ASCII_SYMBOL[i] = SYM_NUL;
    ASCII_SYMBOL['+'] = SYM_PLUS;       ASCII_SYMBOL['-'] = SYM_MINUS;
    ASCII_SYMBOL['*'] = SYM_TIMES;      ASCII_SYMBOL['/'] = SYM_OVER;
    ASCII_SYMBOL['('] = SYM_LPAREN;     ASCII_SYMBOL[')'] = SYM_RPAREN;
    ASCII_SYMBOL['='] = SYM_EQL;        ASCII_SYMBOL[','] = SYM_COMMA;
    ASCII_SYMBOL['.'] = SYM_PERIOD;     ASCII_SYMBOL[';'] = SYM_SEMICOLON;
    ASCII_SYMBOL['!'] = SYM_NOT;

    i = -1;
    strcpy(KW_ALFA[++i], "BEGIN");
    strcpy(KW_ALFA[++i], "CALL");
    strcpy(KW_ALFA[++i], "CONST");
    strcpy(KW_ALFA[++i], "DO");
    strcpy(KW_ALFA[++i], "ELSE");
    strcpy(KW_ALFA[++i], "END");
    strcpy(KW_ALFA[++i], "FOR");
    strcpy(KW_ALFA[++i], "IF");
    strcpy(KW_ALFA[++i], "ODD");
    strcpy(KW_ALFA[++i], "PROCEDURE");
    strcpy(KW_ALFA[++i], "PROGRAM");
    strcpy(KW_ALFA[++i], "READ");
    strcpy(KW_ALFA[++i], "RETURN");
    strcpy(KW_ALFA[++i], "STEP");
    strcpy(KW_ALFA[++i], "THEN");
    strcpy(KW_ALFA[++i], "UNTIL");
    strcpy(KW_ALFA[++i], "VAR");
    strcpy(KW_ALFA[++i], "WHILE");
    strcpy(KW_ALFA[++i], "WRITE");

    i = -1;
    KW_SYMBOL[++i] = SYM_BEGIN;
    KW_SYMBOL[++i] = SYM_CALL;
    KW_SYMBOL[++i] = SYM_CONST;
    KW_SYMBOL[++i] = SYM_DO;
    KW_SYMBOL[++i] = SYM_ELSE;
    KW_SYMBOL[++i] = SYM_END;
    KW_SYMBOL[++i] = SYM_FOR;
    KW_SYMBOL[++i] = SYM_IF;
    KW_SYMBOL[++i] = SYM_ODD;
    KW_SYMBOL[++i] = SYM_PROC;
    KW_SYMBOL[++i] = SYM_PROG;
    KW_SYMBOL[++i] = SYM_READ;
    KW_SYMBOL[++i] = SYM_RETURN;
    KW_SYMBOL[++i] = SYM_STEP;
    KW_SYMBOL[++i] = SYM_THEN;
    KW_SYMBOL[++i] = SYM_UNTIL;
    KW_SYMBOL[++i] = SYM_VAR;
    KW_SYMBOL[++i] = SYM_WHILE;
    KW_SYMBOL[++i] = SYM_WRITE;
  
    strcpy(INST_ALFA[LIT], "LIT");   strcpy(INST_ALFA[OPR], "OPR");
    strcpy(INST_ALFA[LOD], "LOD");   strcpy(INST_ALFA[STO], "STO");
    strcpy(INST_ALFA[CAL], "CAL");   strcpy(INST_ALFA[INI], "INI");
    strcpy(INST_ALFA[JMP], "JMP");   strcpy(INST_ALFA[JPC], "JPC");
}

// Initialize program.
void Init()
{
    SetupLanguage();
    ResetLexer();
}

void Main()
{
    int TX;

    Init();

    log("Start compiling program.");
    GetSym();
    TX = 0;
    parse_program(0, TX);
    ListCode(0);
    log("Compile finish.");

    log("Start executing program.");
    Interpret();
    log("Execute finish.");
}

#ifdef CPP_BUILDER
#else

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "./main input.pl0");
        exit(1);
    }

    FOUT = stderr; UIN = stdin;
    if ((FIN = fopen(argv[1], "r")) == NULL)
        panic(0, "cannot open source file: %s", argv[1]);

    Main();

    return 0;
}

#endif /* #ifdef CPP_BUILDER */
//------------------------------------------------------------------------
