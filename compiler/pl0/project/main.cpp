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
#define IDMAX       10      /* Maximum length of identifiers. */
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



typedef int *SYMSET;                /* symbol set */
typedef char ALFA[IDMAX+1];         /* identifier container */

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
// Global Constants
//------------------------------------------------------------------------
char CH;                        /* last read character */
SYMBOL SYM;                     /* last read symbol */
ALFA ID;                        /* last read identifier */
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

// FIXME
SYMSET DECLBEGSYS, STATBEGSYS, FACBEGSYS;


// symbols table
TABLE_ITEM TABLE[TXMAX];


FILE *FIN, *FOUT, *FERR;            /* STDIN/STDOUT/STDERR file object */
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Utilities
//------------------------------------------------------------------------
// Don't panic!
void panic(int errorcode, const char *fmt, ...)
{
    va_list args;

    // TODO handle GUI
    fprintf(FERR, "error(%d): ", errorcode);
    va_start(args, fmt);
    vfprintf(FERR, fmt, args);
    va_end(args);
    fprintf(FERR, "\n");

#ifdef CPP_BUILDER
#else
    exit(1);
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
void log(FILE *dest, const char *content)
{
    fprintf(dest,
    "//------------------------------------------------------------------------\n");
    fprintf(dest, "// %s\n// %s\n", content, current_date_time().c_str());
    fprintf(dest,
    "//------------------------------------------------------------------------\n");
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
        // TODO handle GUI.
        fprintf(FOUT, "%s\n", s.c_str());
    }
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Symbol Set
//------------------------------------------------------------------------

// Create a new symbol set, mark all field as 0.
// Returns **NULL** if error occurred.
SYMSET SymSetNew(int marked_count, ...)
{
    int i;
    SYMSET s;
    va_list marked_symbols;

    s = (SYMSET) malloc(sizeof(int) * SYMBOLS_COUNT);
    if (s == NULL)
        goto finish;

    for (i = 0; i < SYMBOLS_COUNT; i++)
        s[i] = 0;

    va_start(marked_symbols, marked_count);
    for (i = 0; i < marked_count; i++)
        s[va_arg(marked_symbols, int)] = 1;
    va_end(marked_symbols);

finish:
    return s;
}

// Destory a symbol set.
void SymSetDestory(SYMSET s)
{
    free(s);
}

// Check if a symbol belongs to a set.
int SymIn(SYMBOL symbol, SYMSET set)
{
    return (set[symbol] != 0);
}

// Union two set with a new set.
SYMSET SymSetUnion(SYMSET a, SYMSET b)
{
    int i;
    SYMSET s;

    if ((s = SymSetNew(0)) == NULL)
        panic(0, "SymSetUnion: cannot alloc memory");
    for (i = 0; i < SYMBOLS_COUNT; i++)
        if (a[i] || b[i])
            s[i] = 1;

    return s;
}

// Add a member and return a new set.
SYMSET SymSetAdd(SYMBOL symbol, SYMSET set)
{
    int i;
    SYMSET s;

    if ((s = SymSetNew(0)) == NULL)
        panic(0, "SymSetAdd: cannot alloc memory");
    for (i = 0; i < SYMBOLS_COUNT; i++)
        s[i] = set[i];

    s[symbol] = 1;

    return s;
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

        // TODO handle GUI
        fprintf(FOUT, "%s\n", s.c_str());
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
void GEN(FUNCTION_TYPE F, int L, int A)
{
    if (CX > CXMAX)
        panic(0, "program too long");

    CODE[CX].F = F;
    CODE[CX].L = L;
    CODE[CX].A = A;
    CX = CX + 1;
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
                        // TODO handle GUI
                        fprintf(FOUT, "%d\n", S[T--]);
                        break;
                    case 15:                    /* write '\n' to stdout */
                        // TODO handle GUI
                        fprintf(FOUT, "\n");
                        break;
                    case 16:                    /* read from stdin */
                        // TODO handle GUI
                        T = T + 1;
                        scanf("%d", &S[T]);
                        break;
                    default:
                        panic(0, "unknown op code: %d", I.A);
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
// TODO ?
void TEST(SYMSET a, SYMSET b, int error_code)
{
    SYMSET c;

    if (!SymIn(SYM, a))
        panic(error_code, "TEST: symbol %s not in set a", SYMOUT[SYM]);

    c = SymSetUnion(a, b);
    while (!SymIn(SYM, c))
        GetSym();

    SymSetDestory(c);
}

// Record an entity into symbol table.
// TODO DX?
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

// Find identifier's position.
// Return 0 if not found.
int POSITION(ALFA ID, int TX)
{
    int i;

    for (i = TX; i > 0; i--)
        if (strcmp(TABLE[i].NAME, ID) == 0)
            return i;

    return 0;
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Parser
//------------------------------------------------------------------------
void EXPRESSION(SYMSET, int, int &);
void TERM(SYMSET, int, int &);

void ConstDelcaration(int level, int &TX, int &DX)
{
    if (SYM == SYM_IDENT) {
        GetSym();

        if (SYM == SYM_EQL) {
            GetSym();

            if (SYM == SYM_NUMBER) {
                ENTER(KIND_CONSTANT, level, TX, DX);
                GetSym();
            } else {
                panic(3, "expect NUMBER, got: %s", SYMOUT[SYM]);
            }
        }
    } else {
        panic(4, "expect IDENT, got: %s", SYMOUT[SYM]);
    }
}

void VarDeclaration(int level, int &TX, int &DX)
{
    if (SYM == SYM_IDENT) {
        ENTER(KIND_VARIABLE, level, TX, DX);
        GetSym();
    } else {
        panic(4, "expect IDENT, got: %s", SYMOUT[SYM]);
    }
}


void FACTOR(SYMSET FSYS, int level, int &TX)
{
    int ident_pos;
    TABLE_ITEM ident;
    SYMSET set;

    TEST(FACBEGSYS, FSYS, 24);

    while (SymIn(SYM, FACBEGSYS)) {
        if (SYM == SYM_IDENT) {
            ident_pos = POSITION(ID, TX);
            if (ident_pos == 0) {
                panic(11, "FACTOR: unable to find identify: %s", ID);
            } else {
                ident = TABLE[ident_pos];
                switch (ident.KIND) {
                    case KIND_CONSTANT:
                        GEN(LIT, 0, ident.VAL);
                        break;
                    case KIND_VARIABLE:
                        // TODO address calculating?
                        GEN(LOD, level - ident.vp.LEVEL, ident.vp.ADDRESS);
                        break;
                    default:
                        panic(21, "FACTOR: identify type should be CONST or VARIABLE");
                }
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

            set = SymSetAdd(SYM_RPAREN, FSYS);
            EXPRESSION(set, level, TX);
            SymSetDestory(set);

            if (SYM == SYM_RPAREN)
                GetSym();
            else
                panic(22, "missing `)`");
        } /* SYM == SYM_LPAREN */

        TEST(FSYS, FACBEGSYS, 23);

    } /* while */
}

void TERM(SYMSET FSYS, int level, int &TX)
{
    SYMSET factor_set, op_set;
    SYMBOL MULOP;

    op_set = SymSetNew(2, SYM_TIMES, SYM_OVER);
    factor_set = SymSetUnion(FSYS, op_set);
    SymSetDestory(op_set);

    FACTOR(factor_set, level, TX);
    while (SYM == SYM_TIMES || SYM == SYM_OVER) {
        MULOP = SYM;
        GetSym();

        FACTOR(factor_set, level, TX);

        if (MULOP == SYM_TIMES)
            GEN(OPR, 0, 4);
        else
            GEN(OPR, 0, 5);
    }

    SymSetDestory(factor_set);
}

void EXPRESSION(SYMSET FSYS, int level, int &TX)
{
    SYMSET term_set, op_set;
    SYMBOL ADDOP;

    op_set = SymSetNew(2, SYM_PLUS, SYM_MINUS);
    term_set = SymSetUnion(FSYS, op_set);
    SymSetDestory(op_set);

    if (SYM == SYM_PLUS || SYM == SYM_MINUS) {
        ADDOP = SYM;
        GetSym();

        TERM(term_set, level, TX);

        if (ADDOP == SYM_MINUS)
            GEN(OPR, 0, 1);
    } /* SYM == SYM_PLUS || SYM == SYM_MINUS */
    else {
        TERM(term_set, level, TX);
    }

    while (SYM == SYM_PLUS || SYM == SYM_MINUS) {
        ADDOP = SYM;
        GetSym();

        TERM(term_set, level, TX);

        if (ADDOP == SYM_PLUS)
            GEN(OPR, 0, 2);
        else
            GEN(OPR, 0, 3);
    }

    SymSetDestory(term_set);
}

void CONDITION(SYMSET FSYS, int level, int &TX)
{
    SYMSET set, op_set;
    int op_code;
    SYMBOL RELOP;

    if (SYM == SYM_ODD) {
        GetSym();
        
        EXPRESSION(FSYS, level, TX);
        GEN(OPR, 0, 6);
    } else {
        op_set = SymSetNew(6, SYM_EQL, SYM_NEQ, SYM_LSS, SYM_LEQ, SYM_GTR, SYM_GEQ);
        set = SymSetUnion(FSYS, op_set);
        EXPRESSION(set, level, TX);

        if (!SymIn(SYM, op_set))
            panic(20, "unsupproted compare operator: %s", SYMOUT[SYM]);
        SymSetDestory(set);
        SymSetDestory(op_set);

        RELOP = SYM;
        GetSym();
        EXPRESSION(FSYS, level, TX);

        switch (RELOP) {
            case SYM_EQL:
                op_code = 8;
                break;
            case SYM_NEQ:
                op_code = 9;
                break;
            case SYM_LSS:
                op_code = 10;
                break;
            case SYM_GEQ:
                op_code = 11;
                break;
            case SYM_GTR:
                op_code = 12;
                break;
            case SYM_LEQ:
                op_code = 13;
                break;
            default:
                panic(0, "CONDITION: unknown operator: %s", SYMOUT[SYM]);
        }

        GEN(OPR, 0, op_code);
    }
}

void ASSIGNMENT(SYMSET FSYS, int level, int &TX, TABLE_ITEM inst)
{
    EXPRESSION(FSYS, level, TX);

    GEN(STO, level - inst.vp.LEVEL, inst.vp.ADDRESS);
}

void SELF_ASSIGNMENT(SYMSET FSYS, int level, int &TX, TABLE_ITEM inst, SYMBOL op)
{
    int op_code;

    // load variable for calculating.
    GEN(LOD, level - inst.vp.LEVEL, inst.vp.ADDRESS);

    // calculate right side value.
    EXPRESSION(FSYS, level, TX);

    // calculate new value.
    switch (op) {
        case SYM_ADD_ASSIGN:
            op_code = 2;
            break;
        case SYM_SUB_ASSIGN:
            op_code = 3;
            break;
        case SYM_MUL_ASSIGN:
            op_code = 4;
            break;
        case SYM_DIV_ASSIGN:
            op_code = 5;
            break;
        default:
            panic(0, "SELF_ASSIGNMENT: unsupproted operator: %s", SYMOUT[op]);
    }
    GEN(OPR, 0, op_code);
    
    // Store new value.
    GEN(STO, inst.vp.LEVEL, inst.vp.ADDRESS);
}

void STATEMENT(SYMSET FSYS, int level, int &TX)
{
    SYMSET set, op_set;
    SYMBOL op_sym;
    int ident_pos, CX1, CX2;
    TABLE_ITEM ident;

    switch (SYM) {
        case SYM_IDENT:
            ident_pos = POSITION(ID, TX);
            if (ident_pos == 0)
                panic(11, "STATEMENT: unable to find identify: %s", ID);
            ident = TABLE[ident_pos];
            if (ident.KIND != KIND_VARIABLE)
                panic(12, "STATEMENT: canont assign to non-variable");
            GetSym();

            if (SYM == SYM_ASSIGN) {
                GetSym();
                ASSIGNMENT(FSYS, level, TX, ident);
            } else if (SYM == SYM_ADD_ASSIGN
                       || SYM == SYM_SUB_ASSIGN
                       || SYM == SYM_MUL_ASSIGN
                       || SYM == SYM_DIV_ASSIGN) {
                op_sym = SYM;
                GetSym();
                SELF_ASSIGNMENT(FSYS, level, TX, ident, op_sym);
            } else {
                panic(13, "STATEMENT: unexpected token %s", SYMOUT[SYM]);
            }
            break; /* case SYM_IDENT */

        case SYM_READ:
            GetSym();
            if (SYM != SYM_LPAREN)
                panic(34, "STATEMENT: expect '(', got: %s", SYMOUT[SYM]);
            do {
                GetSym();
                if (SYM == SYM_IDENT) {
                    ident_pos = POSITION(ID, TX);
                    if (ident_pos == 0)
                        panic(35, "unable to find identify: %s", ID);
                    ident = TABLE[ident_pos];
                    if (ident.KIND != KIND_VARIABLE) {
                        panic(35, "READ: identify type should be variable");
                    } else {
                        GEN(OPR, 0, 16);
                        GEN(STO, level - ident.vp.LEVEL, ident.vp.ADDRESS);
                    }
                } else {
                    panic(35, "expected identify, got: %s", SYMOUT[SYM]);
                }

                GetSym();
            } while (SYM == SYM_COMMA);

            if (SYM != SYM_RPAREN)
                panic(33, "READ: expected ')', got: %s", SYMOUT[SYM]);
            
            GetSym();
            break; /* case SYM_READ */

        case SYM_WRITE:
            GetSym();
            if (SYM == SYM_LPAREN) {
                op_set = SymSetNew(2, SYM_RPAREN, SYM_COMMA);
                set = SymSetUnion(FSYS, op_set);
                SymSetDestory(op_set);

                do {
                    GetSym();
                    EXPRESSION(set, level, TX);
                    GEN(OPR, 0, 14);
                } while (SYM == SYM_COMMA);
                SymSetDestory(set);

                if (SYM != SYM_RPAREN)
                    panic(33, "WRITE: expected ')', got: %s", SYMOUT[SYM]);
                GetSym();
            }

            GEN(OPR, 0, 15);
            break; /* case SYM_WRITE */

        case SYM_CALL:
            GetSym();
            if (SYM != SYM_IDENT)
                panic(14, "CALL: expected procedure name, got: %s", SYMOUT[SYM]);

            ident_pos = POSITION(ID, TX);
            if (ident_pos == 0)
                panic(11, "CALL: unable to find procedure: %s", ID);
            
            ident = TABLE[ident_pos];
            if (ident.KIND != KIND_PROCEDURE)
                panic(15, "CALL: %s should be a procedure", ID);
   
            GEN(CAL, level - ident.vp.LEVEL, ident.vp.ADDRESS);
            GetSym();
            break; /* case SYM_CALL */

        case SYM_IF:
            GetSym();
            
            op_set = SymSetNew(2, SYM_THEN, SYM_DO);
            set = SymSetUnion(FSYS, op_set);
            SymSetDestory(op_set);
            
            CONDITION(set, level, TX);
            SymSetDestory(set);

            if (SYM != SYM_THEN)
                panic(16, "IF: expected THEN, got %s", SYMOUT[SYM]);
            GetSym();

            CX1 = CX;
            GEN(JPC, 0, 0);
            STATEMENT(FSYS, level, TX);
            CODE[CX1].A = CX;
            break; /* case SYM_IF */

        case SYM_BEGIN:
            GetSym();

            op_set = SymSetNew(2, SYM_SEMICOLON, SYM_END);
            set = SymSetUnion(FSYS, op_set);
            SymSetDestory(op_set);

            STATEMENT(set, level, TX);

            // TODO ??
            op_set = SymSetAdd(SYM_SEMICOLON, STATBEGSYS);
            while (SymIn(SYM, op_set)) {
                if (SYM != SYM_SEMICOLON)
                    panic(10, "expect ';', got: %s", SYMOUT[SYM]);
                
                GetSym();
                STATEMENT(set, level, TX);
            }
            SymSetDestory(set);
            SymSetDestory(op_set);

            if (SYM != SYM_END)
                panic(17, "expect END, got %s", SYMOUT[SYM]);
            GetSym();
            
            break; /* case SYM_BEGIN */

        case SYM_WHILE:
            CX1 = CX;
            GetSym();

            op_set = SymSetAdd(SYM_DO, FSYS);
            CONDITION(op_set, level, TX);
            SymSetDestory(op_set);
            CX2 = CX;

            GEN(JPC, 0, 0);

            if (SYM != SYM_DO)
                panic(18, "expect DO, got %s", SYMOUT[SYM]);
            GetSym();

            STATEMENT(FSYS, level, TX);
            GEN(JMP, 0, CX1);
            CODE[CX2].A = CX;

            break; /* case SYM_WHILE */

        default:
            ;
    } /* switch SYM */

    set = SymSetNew(0);
    TEST(FSYS, set, 19);
    SymSetDestory(set);
}

void BLOCK(int level, int TX, SYMSET FSYS)
{
    int DX, TX0, CX0;
    SYMSET op_set, set;

    DX = 3;                                 /* data storage index */
    TX0 = TX;                               /* initial table index */
    CX0 = CX;                               /* initial code index */
    TABLE[TX].vp.ADDRESS = CX;
    GEN(JMP, 0, 0);

    if (level > LEVMAX)
        panic(32, "block levels too deep: %d", level);

    do {
        if (SYM == SYM_CONST) {
            GetSym();

            do {
                ConstDelcaration(level, TX, DX);

                while (SYM == SYM_COMMA) {
                    GetSym();
                    ConstDelcaration(level, TX, DX);
                }

                if (SYM != SYM_SEMICOLON)
                    panic(5, "expected ';', got: %s", SYMOUT[SYM]);
                GetSym();
            } while (SYM == SYM_IDENT);
        }

        if (SYM == SYM_VAR) {
            GetSym();

            do {
                VarDeclaration(level, TX, DX);

                while (SYM == SYM_COMMA) {
                    GetSym();
                    VarDeclaration(level, TX, DX);
                }

                if (SYM != SYM_SEMICOLON)
                    panic(5, "expected ';', got: %s", SYMOUT[SYM]);
                GetSym();
            } while (SYM == SYM_IDENT);
        }

        while (SYM == SYM_PROC) {
            GetSym();
            if (SYM != SYM_IDENT)
                panic(4, "expected identify, got: %s", SYMOUT[SYM]);
            GetSym();
            
            ENTER(KIND_PROCEDURE, level, TX, DX);
            
            if (SYM != SYM_SEMICOLON)
                panic(5, "expected ';', got %s", SYMOUT[SYM]);
            GetSym();

            set = SymSetAdd(SYM_SEMICOLON, FSYS);
            BLOCK(level + 1, TX, set);
            SymSetDestory(set);

            if (SYM != SYM_SEMICOLON)
                panic(5, "expected ';', got %s", SYMOUT[SYM]);
            GetSym();

            op_set = SymSetNew(2, SYM_IDENT, SYM_PROC);
            set = SymSetUnion(STATBEGSYS, op_set);
            SymSetDestory(op_set);
            TEST(set, FSYS, 6);
            SymSetDestory(set);
        }

        set = SymSetAdd(SYM_IDENT, STATBEGSYS);
        TEST(set, DECLBEGSYS, 7);
        SymSetDestory(set);
    } while (SymIn(SYM, DECLBEGSYS));

    CODE[TABLE[TX0].vp.ADDRESS].A = CX;
    TABLE[TX0].vp.ADDRESS = CX;                 /* start address of body */
    TABLE[TX0].vp.SIZE = DX;                    /* size of data segment */
    GEN(INI, 0, DX);

    op_set = SymSetNew(2, SYM_SEMICOLON, SYM_END);
    set = SymSetUnion(FSYS, op_set);
    SymSetDestory(op_set);
    STATEMENT(set, level, TX);
    SymSetDestory(set);
    
    GEN(OPR, 0, 0);                             /* return */
    TEST(FSYS, SymSetNew(0), 8);
    ListCode(CX0);
}

void PROGRAM()
{
    SYMSET op_set, set;

    GetSym();
    if (SYM != SYM_PROG)
        panic(0, "expected PROGRAM, got: %s", SYMOUT[SYM]);

    GetSym();
    if (SYM != SYM_IDENT)
        panic(0, "expected program name, got: %s", SYMOUT[SYM]);

    GetSym();
    if (SYM != SYM_SEMICOLON)
        panic(5, "expected ';', got: %s", SYMOUT[SYM]);
    GetSym();

    op_set = SymSetUnion(DECLBEGSYS, STATBEGSYS);
    set = SymSetAdd(SYM_PERIOD, op_set);
    SymSetDestory(op_set);
    BLOCK(0, 0, set);
    SymSetDestory(set);

    if (SYM != SYM_PERIOD)
        panic(9, "expected '.', got: %s", SYMOUT[SYM]);
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

    DECLBEGSYS = SymSetNew(3, SYM_CONST, SYM_VAR, SYM_PROC);
    STATBEGSYS = SymSetNew(5, SYM_BEGIN, SYM_CALL, SYM_IF, SYM_WHILE, SYM_WRITE);
    FACBEGSYS = SymSetNew(3, SYM_IDENT, SYM_NUMBER, SYM_LPAREN);
}

// Initialize program.
void Init()
{
    ResetLexer();
}

void Main()
{
    SetupLanguage();
    ResetLexer();

    log(FOUT, "Start compiling program.");
    PROGRAM();
    log(FOUT, "Compile finish.");

    log(FOUT, "Start executing program.");
    Interpret();
    log(FOUT, "Execute finish.");
}

#ifdef CPP_BUILDER
#else

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "./main input.pl0");
        exit(1);
    }

    FOUT = stdout;
    FERR = stderr;
    if ((FIN = fopen(argv[1], "r")) == NULL)
        panic(0, "cannot open source file: %s", argv[1]);

    Main();

    return 0;
}

#endif /* #ifdef CPP_BUILDER */
//------------------------------------------------------------------------
