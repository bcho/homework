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
#define NORW        20          /* Counts of reserviced keywords. */
#define IDMAX       10          /* Maximum length of identitys. */
#define TXMAX       100         /* Size of symbol table. */
#define LINEMAX     81          /* Maximum length of program line. */
#define AMAX        2047        /* Maximum address. */
#define LEVMAX      3           /* Maximum nesting procedure level. */
#define CXMAX       200         /* Size of code storage. */
#define STACK_MAX   500         /* Size of interpreter stack. */

#define NMAX                10          /* Maximum number of integer digits. */
#define EXIT_FRAMES_SIZE    100         /* Exit frame maxium size. */
#define CONSTANT_TABLE_SIZE 100         /* Maximum size of constant taable. */
#define INTEGER_MAX         2147483647  /* Maximum integer. */
#define STATIC_LINK_OFFSET  3           /* Basic offset from static link. */
#define PARAMETER_COUNT     10          /* Maximum count of parameter. */
#define ARRAY_SIZE_MAX      200         /* Maximum size of array type */
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Language Components
//------------------------------------------------------------------------
typedef enum {
    // basic symbols
    SYM_NUL, SYM_IDENT, SYM_INTEGER, SYM_CHAR, SYM_FLOAT,

    // operators
    SYM_PLUS, SYM_MINUS, SYM_TIMES, SYM_OVER,
    SYM_ODD, SYM_EQL, SYM_NEQ, SYM_LSS, SYM_LEQ, SYM_GTR, SYM_GEQ,
    SYM_LPAREN, SYM_RPAREN, SYM_LBRACKET, SYM_RBRACKET,
    SYM_COMMA, SYM_SEMICOLON, SYM_PERIOD,
    SYM_ASSIGN, SYM_ADD_ASSIGN, SYM_SUB_ASSIGN, SYM_MUL_ASSIGN, SYM_DIV_ASSIGN,
    SYM_AND, SYM_OR, SYM_NOT,

    // keywords
    SYM_CONST, SYM_VAR, SYM_PROG, SYM_PROC, SYM_FUNC,
    SYM_BEGIN, SYM_END, SYM_RETURN,
    SYM_IF, SYM_THEN, SYM_ELSE,
    SYM_WHILE, SYM_DO, SYM_UNTIL, SYM_FOR, SYM_STEP,
    SYM_WRITE, SYM_READ, SYM_CALL
} SYMBOL;

// symbols in string form.
const char *SYMOUT[] = {
    "NUL", "IDENT", "INTEGER", "CHAR", "FLOAT",

    "PLUS", "MINUS", "TIMES", "OVER",
    "ODD", "EQ", "NEQ", "LSS", "LEQ", "GTR", "GEQ",
    "LPAREN", "RPAREN", "LBRACKET", "RBRACKET",
    "COMMA", "SEMICOLON", "PERIOD",
    "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN",
    "AND", "OR", "NOT",

    "CONST", "VAR", "PROGRAM", "PROCEDURE", "FUNCTION",
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
    KIND_ARRAY,
    KIND_PROCEDURE,
    KIND_FUNCTION
} OBJECT_KIND;

typedef enum {
    STATE_RUNNING,
    STATE_STOP
} MACHINE_STATE;

// machine data type
typedef enum {
    TYPE_ADDRESS,
    TYPE_INT,
    TYPE_CHAR,
    TYPE_FLOAT
} DATA_TYPE;


typedef char ALFA[IDMAX+1];         /* identity container */

typedef struct {
    ALFA NAME;
    OBJECT_KIND KIND;
    struct {
        int LEVEL, ADDRESS, SIZE;
    } vp;
} TABLE_ITEM;                       /* symbol table item */

typedef struct {
    DATA_TYPE type;
    union {
        int ival;                    /* address / int / bool */
        char cval;                   /* char */
        float fval;                  /* float */
    };
} DATUM;                            /* machine datum */
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Machine
//------------------------------------------------------------------------
// instruction function type
typedef enum {      /* TYP L A -- INSTRUCTION FORMAT */
    LIT,            /* LIT 0 A -- LOAD CONTANT FROM ADDRESS A */
    OPR,            /* OPR L A -- EXECUTE OPR A WITH OPTIONS L */
    LOD,            /* LOD L A -- LOAD DATA FROM LEVEL L WITH OFFSET A */
    LDA,            /* LDA L A -- LOAD DATA ADDRESS FROM LEVEL L WITH OFFSET A */
    LID,            /* LID 0 0 -- LOAD FROM ADDRESS */
    IXA,            /* IXA 0 0 -- CALCULATE INDEXED ADDRESS */
    STO,            /* STO L A -- STORE VARIABLE L TO A */
    STI,            /* STI 0 0 -- STORE TO ADDRESS */
    STR,            /* STR 0 0 -- STORE RETURN VALUE TODO: review? */
    MST,            /* MST L 0 -- MARK STACK FRAME */
    CAL,            /* CAL L A -- CALL PROCEDURE A WITH ARGSIZE L */
    INI,            /* INI L A -- SET SP WITH MP + A WITH LOCAL OBJECT COUNT L */
    JMP,            /* JMP 0 A -- JUMP TO A */
    JPC,            /* JPC 0 A -- (CONDITIONAL) JUMP TO A */
    HLT,            /* HLT 0 0 -- HALT MACHINE */
    NO_OP           /* MARKER */
} FUNCTION_TYPE;

#define INST_COUNT (NO_OP)

typedef struct {
    FUNCTION_TYPE F;
    int L, A;
    char comment[100];
} INSTRUCTION;


// Stack Frame
//                                                          (high address)
// +----------------------------------------------------+ <- sp
// |                variables (0 or more)               |
// +----------------------------------------------------+
// |                args (0 or more)                    |
// +----------------------------------------------------+
// |                return address                      |
// +----------------------------------------------------+
// |            dynamic link (to caller's frame)        |
// +----------------------------------------------------+
// |          static link (to parent block's frame)     |
// +----------------------------------------------------+
// |                return value (optional)             |
// +----------------------------------------------------+ <- mp
//                                                          (low address)
#define STACK_FRAME_SIZE 4
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------
char CH;                        /* last read character */
SYMBOL SYM;                     /* last read symbol */
ALFA ID;                        /* last read identity */
int INTEGER;                    /* last read integer */
char CHAR;                      /* last read char */
float FLOAT;                    /* last read float */

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

TABLE_ITEM TABLE[TXMAX];        /* symbols table */
DATUM INTER_STACK[STACK_MAX];   /* interpreter stack */

DATUM CONSTANT_TABLE[TXMAX];    /* constant values table */
int CONSTANT_TABLE_INDEX;       /* constant table index */

// TODO exit frame structure doc
int *EXIT_FRAMES[EXIT_FRAMES_SIZE]; /* exit frames list */
int CURRENT_EXIT_FRAME;             /* current exit frame index */


FILE *FIN, *FOUT, *UIN;         /* STDIN/STDOUT/USER STDIN file object */
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
        s = s + "\t" + inst.comment;
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
    float base;
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

    else if (isdigit(CH)) {   /* decimal integer / float */
        SYM = SYM_INTEGER;
        i = 0; INTEGER = 0;
        do {
            INTEGER = 10 * INTEGER + (CH - '0');
            i++;
            GetCh();
            if (i > NMAX)
                panic(30, "GetSym: integer too large: %d", INTEGER);
        } while (isdigit(CH));

        if (CH == '.') {
            GetCh();
            if (!isdigit(CH)) {
                panic(0, "GetSym: malform fixed-point float representation");
            }
            FLOAT = INTEGER;
            INTEGER = 0;
            SYM = SYM_FLOAT;
            base = 0.1;
            do {
                FLOAT = FLOAT + base * (CH - '0');
                base = base / 10;
                GetCh();
            } while (isdigit(CH));
        }
    } /* decimal integer */

    else if (CH == '\'') {  /* char */
        GetCh();
        SYM = SYM_CHAR;
        CHAR = CH;
        GetCh();
        if (CH != '\'')
            panic(0, "GetSym: expected ', got: %c", CH);
        GetCh();
    } /* char */

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
// Datum
//------------------------------------------------------------------------
inline void datum_set_value(DATUM &d, float fval)
{
    d.type = TYPE_FLOAT;
    d.fval = fval;
}

inline void datum_set_value(DATUM &d, int ival)
{
    d.type = TYPE_INT;
    d.ival = ival;
}

inline void datum_set_value(DATUM &d, char cval)
{
    d.type = TYPE_CHAR;
    d.cval = cval;
}

inline float datum_cast_float(DATUM d)
{
    switch (d.type) {
        case TYPE_FLOAT:
            return d.fval;
        case TYPE_ADDRESS:
        case TYPE_INT:
            return (float) d.ival;
        case TYPE_CHAR:
            return (float) d.cval;
        default:
            panic(0, "datum_cast_float: unable to cast type: %d to float", d.type);
    }
}

inline int datum_cast_int(DATUM d)
{
    switch (d.type) {
        case TYPE_FLOAT:
            return (int) d.fval;
        case TYPE_ADDRESS:
        case TYPE_INT:
            return d.ival;
        case TYPE_CHAR:
            return (int) d.cval;
        default:
            panic(0, "datum_cast_int: unable to cast type: %d to int", d.type);
    }
}

inline char datum_cast_char(DATUM d)
{
    switch (d.type) {
        case TYPE_FLOAT:
            return (char) d.fval;
        case TYPE_ADDRESS:
        case TYPE_INT:
            return (char) d.ival;
        case TYPE_CHAR:
            return d.cval;
        default:
            panic(0, "datum_cast_char: unable to cast type: %d to char", d.type);
    }
}

inline int datum_cast_address(DATUM d)
{
    switch (d.type) {
        case TYPE_FLOAT:
            return (int) d.fval;
        case TYPE_ADDRESS:
        case TYPE_INT:
            return d.ival;
        case TYPE_CHAR:
            return (int) d.cval;
        default:
            panic(0, "datum_cast_address: unable to cast type: %d to int", d.type);
    }
}

inline void datum_copy(DATUM from, DATUM &to)
{
    to.type = from.type;
    switch (to.type) {
        case TYPE_FLOAT:
            to.fval = from.fval;
            break;
        case TYPE_INT:
        case TYPE_ADDRESS:
            to.ival = from.ival;
            break;
        case TYPE_CHAR:
            to.cval = from.cval;
            break;
        default:
            panic(0, "datum_copy: unknown datum type: %d", to.type);
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

// ... also add comment to the generated instruction.
int GEN(FUNCTION_TYPE F, int L, int A, const char *fmt, ...)
{
    int filled_cx;
    va_list args;

    filled_cx = GEN(F, L, A);

    va_start(args, fmt);
    vsprintf(CODE[filled_cx].comment, fmt, args);
    va_end(args);

    return filled_cx;
}

// Calculate static link with mp in specify level.
int get_static_link(int level, int mp, DATUM dstore[])
{
    int sl = mp + 1;

    while (level > 0) {
        if (dstore[sl].type != TYPE_ADDRESS)
            panic(0, "get_static_link: datum should be address type");
        sl = dstore[sl].ival;
        level = level - 1;
    }

    return sl;
}

//------------------------------------------------------------------------
// Arithmetic Operations
//
// Promotion Rules:
// 
// 1. If either operand is float, the other is converted to float,
//    target operand is converted to float.
// 2. Otherwise, both operands have type int, target operand
//    is converted to int.
//------------------------------------------------------------------------
// OPR 1 (- A)
inline void inst_inverse(DATUM src, DATUM &dest)
{
    dest.type = src.type;
    switch (src.type) {
        case TYPE_FLOAT:
            dest.type = TYPE_FLOAT;
            datum_set_value(dest, - src.fval);
            break;
        default:
            dest.type = TYPE_INT;
            datum_set_value(dest, - src.ival);
            break;
    }
}

// OPR 2 (A + B)
inline void inst_add(DATUM a, DATUM b, DATUM &c)
{
    if (a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        c.type = TYPE_FLOAT;
        datum_set_value(c, datum_cast_float(a) + datum_cast_float(b));
    } else {
        c.type = TYPE_INT;
        datum_set_value(c, datum_cast_int(a) + datum_cast_int(b));
    }
}

// OPR 3 (A - B)
inline void inst_sub(DATUM a, DATUM b, DATUM &c)
{
    if (a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        c.type = TYPE_FLOAT;
        datum_set_value(c, datum_cast_float(a) - datum_cast_float(b));
    } else {
        c.type = TYPE_INT;
        datum_set_value(c, datum_cast_int(a) - datum_cast_int(b));
    }
}

// OPR 4 (A * B)
inline void inst_mul(DATUM a, DATUM b, DATUM &c)
{
    if (a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        c.type = TYPE_FLOAT;
        datum_set_value(c, datum_cast_float(a) * datum_cast_float(b));
    } else {
        c.type = TYPE_INT;
        datum_set_value(c, datum_cast_int(a) * datum_cast_int(b));
    }
}

// OPR 5 (A / B)
inline void inst_div(DATUM a, DATUM b, DATUM &c)
{
    if (a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        c.type = TYPE_FLOAT;
        datum_set_value(c, datum_cast_float(a) / datum_cast_float(b));
    } else {
        c.type = TYPE_INT;
        datum_set_value(c, datum_cast_int(a) / datum_cast_int(b));
    }
}

// OPR 6 (ODD A)
inline void inst_odd(DATUM src, DATUM &dest)
{
    if (src.type != TYPE_INT)
        panic(0, "inst_odd: opreand should have type int, got: %d", src.type);
    dest.type = TYPE_INT;
    datum_set_value(dest, datum_cast_int(src) % 2 == 1);
}

// OPR 7 (!A)
inline void inst_not(DATUM src, DATUM &dest)
{
    int value;

    dest.type = TYPE_INT;
    switch (src.type) {
        case TYPE_FLOAT:
            value = !src.fval;
            break;
        default:
            value = !src.ival;
    }
    datum_set_value(dest, value);
}

// OPR 8 (A == B)
inline void inst_equ(DATUM a, DATUM b, DATUM &c)
{
    c.type = TYPE_INT;
    if (a.type == TYPE_FLOAT || b.type == TYPE_FLOAT)
        datum_set_value(c, datum_cast_float(a) == datum_cast_float(b));
    else
        datum_set_value(c, datum_cast_int(a) == datum_cast_int(b));
}

// OPR 9 (A != B)
inline void inst_neq(DATUM a, DATUM b, DATUM &c)
{
    c.type = TYPE_INT;
    if (a.type == TYPE_FLOAT || b.type == TYPE_FLOAT)
        datum_set_value(c, datum_cast_float(a) != datum_cast_float(b));
    else
        datum_set_value(c, datum_cast_int(a) != datum_cast_int(b));
}

// OPR 10 (A < B)
inline void inst_lss(DATUM a, DATUM b, DATUM &c)
{
    c.type = TYPE_INT;
    if (a.type == TYPE_FLOAT || b.type == TYPE_FLOAT)
        datum_set_value(c, datum_cast_float(a) < datum_cast_float(b));
    else
        datum_set_value(c, datum_cast_int(a) < datum_cast_int(b));
}

// OPR 11 (A >= B)
inline void inst_geq(DATUM a, DATUM b, DATUM &c)
{
    c.type = TYPE_INT;
    if (a.type == TYPE_FLOAT || b.type == TYPE_FLOAT)
        datum_set_value(c, datum_cast_float(a) >= datum_cast_float(b));
    else
        datum_set_value(c, datum_cast_int(a) >= datum_cast_int(b));
}

// OPR 12 (A <= B)
inline void inst_leq(DATUM a, DATUM b, DATUM &c)
{
    c.type = TYPE_INT;
    if (a.type == TYPE_FLOAT || b.type == TYPE_FLOAT)
        datum_set_value(c, datum_cast_float(a) <= datum_cast_float(b));
    else
        datum_set_value(c, datum_cast_int(a) <= datum_cast_int(b));
}

// OPR 13 (A > B)
inline void inst_gtr(DATUM a, DATUM b, DATUM &c)
{
    c.type = TYPE_INT;
    if (a.type == TYPE_FLOAT || b.type == TYPE_FLOAT)
        datum_set_value(c, datum_cast_float(a) > datum_cast_float(b));
    else
        datum_set_value(c, datum_cast_int(a) > datum_cast_int(b));
}

// OPR 14 (write to stdout with line break)
inline void inst_write_stdout(DATUM a)
{
    switch (a.type) {
        case TYPE_FLOAT:
            _writeln("%f", datum_cast_float(a));
            break;
        case TYPE_INT:
            _writeln("%d", datum_cast_int(a));
            break;
        case TYPE_CHAR:
            _writeln("%c", datum_cast_char(a));
            break;
        default:
            panic(0, "inst_write_stdout: unknown data type: %d", a.type);
    }
}

// OPR 16 (scan input from stdin)
// TODO support float / char...
inline void inst_read_stdin(DATUM &a)
{
    int input;

    _scanf("%d", &input);
    datum_set_value(a, input);
}

// OPR 17 (A && B)
inline void inst_cond_and(DATUM a, DATUM b, DATUM &c)
{
    c.type = TYPE_INT;
    datum_set_value(c, datum_cast_int(a) && datum_cast_int(b));
}

// OPR 18 (A || B)
inline void inst_cond_or(DATUM a, DATUM b, DATUM &c)
{
    c.type = TYPE_INT;
    datum_set_value(c, datum_cast_int(a) || datum_cast_int(b));
}

void Interpret(int pc)
{
    int mp, sp;                             /* program registers */
    int callee_mp, sl, i;
    INSTRUCTION I;
    MACHINE_STATE state;

    state = STATE_RUNNING;
    sp = -1; mp = 0;

    do {
        I = CODE[pc++];
        switch (I.F) {
            case LIT:                           /* load constant */
                sp = sp + 1;
                datum_copy(CONSTANT_TABLE[I.A], INTER_STACK[sp]);
                break; /* case LIT */
            
            case OPR:                           /* execute operation */
                switch (I.A) {
                    case 0:                     /* return */
                        callee_mp = mp;
                        pc = datum_cast_address(INTER_STACK[callee_mp + 3]);
                        mp = datum_cast_address(INTER_STACK[callee_mp + 2]);
                        if (I.L == 0) {
                            // callee is procedure, discard return value
                            sp = callee_mp - 1;
                        } else {
                            // callee is function, store return value
                            sp = callee_mp;
                        }
                        break;
                    case 1:                     /* -A */
                        inst_inverse(INTER_STACK[sp], INTER_STACK[sp]);
                        break;
                    case 2:                     /* A + B */
                        sp = sp - 1;
                        inst_add(INTER_STACK[sp], INTER_STACK[sp + 1], INTER_STACK[sp]);
                        break;
                    case 3:                     /* A - B */
                        sp = sp - 1;
                        inst_sub(INTER_STACK[sp], INTER_STACK[sp + 1], INTER_STACK[sp]);
                        break;
                    case 4:                     /* A * B */
                        sp = sp - 1;
                        inst_mul(INTER_STACK[sp], INTER_STACK[sp + 1], INTER_STACK[sp]);
                        break;
                    case 5:                     /* A / B */
                        sp = sp - 1;
                        inst_div(INTER_STACK[sp], INTER_STACK[sp + 1], INTER_STACK[sp]);
                        break;
                    case 6:                     /* ODD A */
                        inst_odd(INTER_STACK[sp], INTER_STACK[sp]);
                        break;
                    case 7:                     /* !A */
                        inst_not(INTER_STACK[sp], INTER_STACK[sp]);
                        break;
                    case 8:                     /* A == B */
                        sp = sp - 1;
                        inst_equ(INTER_STACK[sp], INTER_STACK[sp + 1], INTER_STACK[sp]);
                        break;
                    case 9:                     /* A != B */
                        sp = sp - 1;
                        inst_neq(INTER_STACK[sp], INTER_STACK[sp + 1], INTER_STACK[sp]);
                        break;
                    case 10:                    /* A < B */
                        sp = sp - 1;
                        inst_lss(INTER_STACK[sp], INTER_STACK[sp + 1], INTER_STACK[sp]);
                        break;
                    case 11:                    /* >= */
                        sp = sp - 1;
                        inst_geq(INTER_STACK[sp], INTER_STACK[sp + 1], INTER_STACK[sp]);
                        break;
                    case 12:                    /* > */
                        sp = sp - 1;
                        inst_gtr(INTER_STACK[sp], INTER_STACK[sp + 1], INTER_STACK[sp]);
                        break;
                    case 13:                    /* <= */
                        sp = sp - 1;
                        inst_leq(INTER_STACK[sp], INTER_STACK[sp + 1], INTER_STACK[sp]);
                        break;
                    case 14:                    /* write to stdout */
                        inst_write_stdout(INTER_STACK[sp--]);
                        break;
                    case 15:                    /* write '\n' to stdout */
                        _writeln("");
                        break;
                    case 16:                    /* read from stdin */
                        inst_read_stdin(INTER_STACK[++sp]);
                        break;
                    case 17:                    /* A && B */
                        sp = sp - 1;
                        inst_cond_and(INTER_STACK[sp], INTER_STACK[sp + 1], INTER_STACK[sp]);
                        break;
                    case 18:                    /* A || B */
                        sp = sp - 1;
                        inst_cond_or(INTER_STACK[sp], INTER_STACK[sp + 1], INTER_STACK[sp]);
                        break;
                    default:
                        panic(0, "Interpret: unknown op code: %d", I.A);
                } /* switch I.A */
                break; /* case OPR */

            case LOD:                           /* load object */
                sp = sp + 1;
                sl = get_static_link(I.L, mp, INTER_STACK);
                datum_copy(INTER_STACK[sl + STATIC_LINK_OFFSET + I.A], INTER_STACK[sp]);
                break; /* case LOD */

            case LDA:                           /* load object's address */
                sl = get_static_link(I.L, mp, INTER_STACK);
                sp = sp + 1;
                datum_set_value(INTER_STACK[sp], sl + STATIC_LINK_OFFSET + I.A);
                INTER_STACK[sp].type = TYPE_ADDRESS;
                break; /* case LDA */

            case LID:                           /* load from address */
                datum_copy(INTER_STACK[datum_cast_address(INTER_STACK[sp])],
                           INTER_STACK[sp]);
                break; /* case LID */

            case IXA:                           /* calculate indexed address */
                sp = sp - 1;
                datum_set_value(INTER_STACK[sp],
                                datum_cast_address(INTER_STACK[sp]) + datum_cast_int(INTER_STACK[sp + 1]));
                INTER_STACK[sp].type = TYPE_ADDRESS;
                break; /* case IXA */

            case STO:                           /* store variable */
                sl = get_static_link(I.L, mp, INTER_STACK);
                datum_copy(INTER_STACK[sp], INTER_STACK[sl + STATIC_LINK_OFFSET + I.A]);
                sp = sp - 1;
                break; /* case STO */

            case STI:                           /* store to address */
                sp = sp - 1;
                datum_copy(INTER_STACK[sp + 1],
                           INTER_STACK[datum_cast_address(INTER_STACK[sp])]);
                break; /* case STI */

            case STR:                           /* store return value */
                datum_copy(INTER_STACK[sp], INTER_STACK[mp]);
                break; /* case STR */

            case MST:                           /* mark stack frame */
                // return value, set by callee
                // default return value is int:0
                datum_set_value(INTER_STACK[++sp], 0);

                // static link
                sl = get_static_link(I.L, mp, INTER_STACK);
                datum_set_value(INTER_STACK[++sp], sl);
                INTER_STACK[sp].type = TYPE_ADDRESS;

                // dynamic link
                datum_set_value(INTER_STACK[++sp], mp);
                INTER_STACK[sp].type = TYPE_ADDRESS;

                // return address, set by CAL
                datum_set_value(INTER_STACK[++sp], 0);
                INTER_STACK[sp].type = TYPE_ADDRESS;
                break; /* case MST */

            case CAL:                           /* call procedure */
                mp = sp - STACK_FRAME_SIZE - I.L + 1;
                datum_set_value(INTER_STACK[mp + 3], pc);
                INTER_STACK[mp + 3].type = TYPE_ADDRESS;
                pc = I.A;
                break; /* case CAL */

            case INI:                           /* increment */
                sp = mp + I.A - 1;
                // initialize local variabls with int:0
                for (i = 0; i < I.L; i++)
                    datum_set_value(INTER_STACK[sp - i], 0);
                break; /* case INI */

            case JMP:                           /* unconditional jump */
                pc = I.A;
                break; /* case JMP */

            case JPC:                           /* false jump */
                if (! datum_cast_int(INTER_STACK[sp]))
                    pc = I.A;
                sp = sp - 1;
                break; /* case JPC */

            case HLT:                           /* halt machine */
                state = STATE_STOP;
                break; /* case HLT */

            default:
                panic(0, "Interpret: unknown instruction type: %d", I.F);
        }
    } while (state == STATE_RUNNING);
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Constant Table
//------------------------------------------------------------------------
// Record a integer value into constant table.
int constant_enter(int val)
{
    if (CONSTANT_TABLE_INDEX >= CONSTANT_TABLE_SIZE)
        panic(0, "CONSTANT_ENTER: table overflow");
    CONSTANT_TABLE[++CONSTANT_TABLE_INDEX].type = TYPE_INT;
    CONSTANT_TABLE[CONSTANT_TABLE_INDEX].ival = val;

    return CONSTANT_TABLE_INDEX;
}

int constant_enter(float val)
{
    if (CONSTANT_TABLE_INDEX >= CONSTANT_TABLE_SIZE)
        panic(0, "CONSTANT_ENTER: table overflow");
    CONSTANT_TABLE[++CONSTANT_TABLE_INDEX].type = TYPE_FLOAT;
    CONSTANT_TABLE[CONSTANT_TABLE_INDEX].fval = val;

    return CONSTANT_TABLE_INDEX;
}

int constant_enter(char val)
{
    if (CONSTANT_TABLE_INDEX >= CONSTANT_TABLE_SIZE)
        panic(0, "CONSTANT_ENTER: table overflow");
    CONSTANT_TABLE[++CONSTANT_TABLE_INDEX].type = TYPE_CHAR;
    CONSTANT_TABLE[CONSTANT_TABLE_INDEX].cval = val;

    return CONSTANT_TABLE_INDEX;
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Symbol Table
//------------------------------------------------------------------------
// Record an entity into symbol table.
int ENTER(const char *name, OBJECT_KIND kind, int level, int &TX, int &offset,
          int size)
{
    TX = TX + 1;

    strcpy(TABLE[TX].NAME, name);
    TABLE[TX].KIND = kind;

    switch (kind) {
        case KIND_CONSTANT:
            TABLE[TX].vp.ADDRESS = CONSTANT_TABLE_INDEX;
            break;
        case KIND_VARIABLE:
            TABLE[TX].vp.LEVEL = level;
            TABLE[TX].vp.ADDRESS = offset;
            offset = offset + 1;
            break;
        case KIND_ARRAY:
            TABLE[TX].vp.LEVEL = level;
            TABLE[TX].vp.ADDRESS = offset;
            TABLE[TX].vp.SIZE = size;
            offset = offset + size;
            break;
        case KIND_PROCEDURE:
        case KIND_FUNCTION:
            TABLE[TX].vp.LEVEL = level;
            break;
        default:
            panic(0, "ENTER: unknown object kind: %d", kind);
    }

    return TX;
}

int ENTER(OBJECT_KIND kind, int level, int &TX, int &offset)
{
    return ENTER(ID, kind, level, TX, offset, 0);
}

int ENTER_VARIABLE(const char *name, int level, int &TX, int &offset)
{
    return ENTER(name, KIND_VARIABLE, level, TX, offset, 1);
}

int ENTER_ARRAY(const char *name, int level, int &TX, int &offset, int size)
{
    return ENTER(name, KIND_ARRAY, level, TX, offset, size);
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
        panic(0, "GET_IDENT: unable to find identity: %s", id);

    *item = TABLE[pos];
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Parser
//------------------------------------------------------------------------
int parse_program(int &);
int parse_block(int, int &, int &, OBJECT_KIND);
void parse_const(int, int &, int &);
void parse_var(int, int &, int &);
void parse_procedure(int, int &, int &);
void parse_function(int, int &, int &);
int parse_parameter(int, int &, int &);
int parse_argument(int, int &);
void parse_statement(int, int &);
void parse_assignment(int, int &);
void parse_if(int, int &);
void parse_while(int, int &);
void parse_for(int, int &);
void parse_call(int, int &);
void parse_read(int, int &);
void parse_write(int, int &);
void parse_return(int, int &);

// expression groups
void parse_expression(int, int &);
void parse_or_cond(int, int &);
void parse_and_cond(int, int &);
void parse_relational(int, int &);
void parse_additive(int, int &);
void parse_multive(int, int &);
void parse_unary(int, int &);
void parse_function_call_expression(int, int &);
void parse_factor(int, int &);
void parse_array_dereference(int, int &);


// exit frame utilites
void exit_frame_begin();
void exit_frame_add(int);
void exit_frame_end(int);


/*
 * Grammar:
 *
 *  PROGRAM-BLOCK ::= PROGRAM IDENT; BLOCK "."
 *
 * Instructions Layout:
 * +----------------------------------------------------+ <- program_body_start
 * |                                                    |
 * |                    program body                    |
 * |                                                    |
 * +----------------------------------------------------+ <- program_start (execute starts here)
 * |                    MST 0 0                         |
 * +----------------------------------------------------+
 * |                CALL program_body_start             |
 * +----------------------------------------------------+
 * |                        HLT                         |
 * +----------------------------------------------------+
 */
int parse_program(int &TX)
{
    int program_block_start_cx, program_start_cx;
    int sl_offset;

    if (SYM != SYM_PROG)
        panic(0, "PROGRAM-BLOCK: expect PROGRAM, got: %s", SYMOUT[SYM]);
    GetSym();

    if (SYM != SYM_IDENT)
        panic(0, "PROGRAM-BLOCK: expect program name, got: %s", SYMOUT[SYM]);
    GetSym();

    if (SYM != SYM_SEMICOLON)
        panic(5, "PROGRAM-BLOCK: expect ';', got: %s", SYMOUT[SYM]);
    GetSym();

    sl_offset = 0;
    program_block_start_cx = parse_block(0, TX, sl_offset, KIND_PROCEDURE);

    if (SYM != SYM_PERIOD)
        panic(9, "PROGRAM-BLOCK: expect '.', got: %s", SYMOUT[SYM]);

    program_start_cx = GEN(MST, 0, 0, "-----program starts here-----");
    GEN(CAL, 0, program_block_start_cx, "call main block");
    GEN(HLT, 0, 0, "-----program terminate-----");

    return program_start_cx;
}

/*
 * Grammar:
 *
 *   BLOCK ::= {CONST-BLOCK} {VAR-BLOCK} [PROCEDURE-OR-FUNCTION-BLOCK] STATEMENT
 *
 * Instructions Layout:
 * +----------------------------------------------------+
 * |                constant declarations               | (optional)
 * +----------------------------------------------------+
 * |                variable declarations               | (optional)
 * +----------------------------------------------------+
 * |                proc/func declarations              | (optional)
 * +----------------------------------------------------+ <- body_start
 * |                                                    |
 * |                    block body                      |
 * |                                                    |
 * +----------------------------------------------------+
 * |        return statement (JMP body_end)             | (optional)
 * +----------------------------------------------------+
 * |        return statement (JMP body_end)             | (optional)
 * +----------------------------------------------------+ <- body_end
 * |                    body return                     |
 * +----------------------------------------------------+
 */
int parse_block(int level, int &TX, int &offset, OBJECT_KIND kind)
{
    int body_start_cx, body_end_cx;
    int init_offset;

    if (level > LEVMAX)
        panic(32, "BLOCK: level too deep: %d", level);

    exit_frame_begin();

    init_offset = offset;
    if (SYM == SYM_CONST)
        parse_const(level, TX, offset);
    if (SYM == SYM_VAR)
        parse_var(level, TX, offset);
    while (SYM == SYM_PROC || SYM == SYM_FUNC) {
        if (SYM == SYM_PROC)
            parse_procedure(level, TX, offset);
        if (SYM == SYM_FUNC)
            parse_function(level, TX, offset);
    }

    body_start_cx = GEN(INI, offset - init_offset, offset + STACK_FRAME_SIZE,
                        "-----start of %s-----",
                        kind == KIND_PROCEDURE ? "procedure" : "function");

    parse_statement(level, TX);                 /* block body */

    // return
    if (kind == KIND_PROCEDURE)
        body_end_cx = GEN(OPR, 0, 0, "-----end of procedure------");
    else
        body_end_cx = GEN(OPR, 1, 0, "-----end of function-----");
    exit_frame_end(body_end_cx);

    return body_start_cx;
}

/*
 * Grammar:
 *
 *  CONST-BLOCK ::= CONST IDENT "=" INTEGER ["," IDENT "=" INTEGER] ";"
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

        if (SYM != SYM_INTEGER)
            panic(3, "CONST-BLOCK: expect INTEGER , got: %s", SYMOUT[SYM]);
        constant_enter(INTEGER);
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
 *  VAR-BLOCK ::= VAR IDENT-DECLAR ["," IDENT-DECLAR] ";"
 *  IDENT-DECLAR ::= IDENT {"[" POSITIVE-INTEGER "]"}
 */
void parse_var(int level, int &TX, int &DX)
{
    ALFA ident;

    if (SYM != SYM_VAR)
        panic(0, "VAR-BLOCK: expect VAR, got: %s", SYMOUT[SYM]);
    GetSym();

    do {
        if (SYM != SYM_IDENT)
            panic(4, "VAR-BLOCK: expect IDENT, got: %s", SYMOUT[SYM]);
        strcpy(ident, ID);
        GetSym();

        if (SYM == SYM_LBRACKET) {                  /* it's an array */
            GetSym();

            if (SYM != SYM_INTEGER)
                panic(0, "VAR-BLOCK: expect integer, got: %s", SYMOUT[SYM]);
            if (INTEGER <= 0)
                panic(0, "VAR-BLOCK: expect positive size, got: %d", INTEGER);
            if (INTEGER > ARRAY_SIZE_MAX)
                panic(0, "VAR-BLOCK: array size too large, got: %d", INTEGER);
            ENTER_ARRAY(ident, level, TX, DX, INTEGER);
            GetSym();

            if (SYM != SYM_RBRACKET)
                panic(0, "VAR-BLOCK: expect ']', got: %s", SYMOUT[SYM]);
            GetSym();
        } else {                                    /* it's a variable */
            ENTER_VARIABLE(ident, level, TX, DX);
        }

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
 *  PROCEDURE-BLOCK ::= PROCEDURE IDENT {"(" PARAMETERS ")"} ";" BLOCK ";"
 */
void parse_procedure(int level, int &TX, int &DX)
{
    int table_pos, sl_offset;

    if (SYM != SYM_PROC)
        panic(0, "PROCEDURE-BLOCK: expect PROCEDURE, got: %s", SYMOUT[SYM]);
    GetSym();

    if (SYM != SYM_IDENT)
        panic(4, "PROCEDURE-BLOCK: expect identity, got: %s", SYMOUT[SYM]);
    // TODO naming conflict?
    table_pos = ENTER(KIND_PROCEDURE, level, TX, DX);
    TABLE[table_pos].vp.ADDRESS = CX;
    GetSym();
    
    sl_offset = 0;
    if (SYM == SYM_LPAREN)
        parse_parameter(level + 1, TX, sl_offset);

    if (SYM != SYM_SEMICOLON)
        panic(5, "PROCEDURE-BLOCK: expect ';', got: %s", SYMOUT[SYM]);
    GetSym();

    parse_block(level + 1, TX, sl_offset, KIND_PROCEDURE);

    if (SYM != SYM_SEMICOLON)
        panic(5, "PROCEDURE-BLOCK: expect ';', got: %s", SYMOUT[SYM]);
    GetSym();
}

/*
 * Grammar:
 *
 *  FUNCTION-BLOCK ::= FUNCTION IDENT {"(" PARAMETERS ")"} ";" BLOCK ";"
 */
void parse_function(int level, int &TX, int &DX)
{
    int table_pos, sl_offset;

    if (SYM != SYM_FUNC)
        panic(0, "FUNCTION-BLOCK: expect FUNCTION, got: %s", SYMOUT[SYM]);
    GetSym();

    if (SYM != SYM_IDENT)
        panic(4, "FUNCTION-BLOCK: expect identity, got: %s", SYMOUT[SYM]);
    // TODO naming conflict?
    table_pos = ENTER(KIND_FUNCTION, level, TX, DX);
    TABLE[table_pos].vp.ADDRESS = CX;
    GetSym();

    sl_offset = 0;
    if (SYM == SYM_LPAREN)
        parse_parameter(level + 1, TX, sl_offset);

    if (SYM != SYM_SEMICOLON)
        panic(5, "FUNCTION-BLOCK: expect ';', got: %s", SYMOUT[SYM]);
    GetSym();

    parse_block(level + 1, TX, sl_offset, KIND_FUNCTION);

    if (SYM != SYM_SEMICOLON)
        panic(5, "FUNCTION-BLOCK: expect ';', got: %s", SYMOUT[SYM]);
    GetSym();
}

/*
 * Grammar:
 *
 *  PARAMETERS ::= "(" IDENT ["," IDENT] ")"
 *               | "(" ")"
 */
int parse_parameter(int level, int &TX, int &offset)
{
    int start_cx, has_ident;
    int para_pos[PARAMETER_COUNT], para_count;

    start_cx = CX;
    if (SYM != SYM_LPAREN)
        panic(0, "parse_parameter: expect '(', got: %s", SYMOUT[SYM]);
    GetSym();

    // TODO review this parsing process
    has_ident = 0;
    para_count = 0;
    if (SYM == SYM_IDENT) {
        has_ident = 1;
        para_pos[para_count++] = ENTER(KIND_VARIABLE, level, TX, offset);
        GetSym();
    }
    while (has_ident && SYM == SYM_COMMA) {
        GetSym();
        if (SYM != SYM_IDENT)
            panic(0, "parse_parameter: expect identity, got: %s", SYMOUT[SYM]);
        para_pos[para_count++] = ENTER(KIND_VARIABLE, level, TX, offset);
        GetSym();
    }

    if (SYM != SYM_RPAREN)
        panic(0, "parse_parameter: expect ')', got: %s", SYMOUT[SYM]);
    GetSym();

    for (para_count--; para_count >= 0; para_count--)
        GEN(STO, 0, TABLE[para_pos[para_count]].vp.ADDRESS,
            "load parameter %s", TABLE[para_pos[para_count]].NAME);

    return start_cx;
}

/*
 * Grammar:
 *
 *  ARGUMENT ::= "(" EXPRESSION ["," EXPRESSION] ")"
 *             | "(" ")"
 */
int parse_argument(int level, int &TX)
{
    int arg_count, has_exp;

    if (SYM != SYM_LPAREN)
        panic(0, "parse_argument: expect '(', got: %s", SYMOUT[SYM]);
    GetSym();

    // TODO review this parsing process
    arg_count = 0;
    has_exp = 0;
    if (SYM != SYM_RPAREN) {
        has_exp = 1;
        arg_count = arg_count + 1;
        parse_expression(level, TX);
    }
    while (has_exp && SYM == SYM_COMMA) {
        GetSym();
        arg_count = arg_count + 1;
        parse_expression(level, TX);
    }

    if (SYM != SYM_RPAREN)
        panic(0, "parse_argument: expect ')', got: %s", SYMOUT[SYM]);
    GetSym();

    return arg_count;
}

/*
 * Grammar:
 *
 *  STATEMENT ::= BEGIN STATEMENT [";" STATEMENT] END
 *              | ASSIGN-STMT
 *              | CALL-STMT
 *              | IF-STMT
 *              | WHILE-STMT
 *              | FOR-STMT
 *              | CALL-STMT
 *              | READ-STMT
 *              | WRITE-STMT
 *              | RETURN-STMT
 *              | NULL-STMT
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
        case SYM_FOR:
            parse_for(level, TX);
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
        case SYM_RETURN:
            parse_return(level, TX);
            break;
        case SYM_BEGIN:
            GetSym();

            parse_statement(level, TX);

            while (SYM == SYM_SEMICOLON) {
                GetSym();
                if (SYM != SYM_END)     /* null statement */
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
 *  ASSIGNMENT ::= ASSIGNABLE ASSIGNOP EXPRESSION
 *  ASSIGNABLE ::= IDENT
 *               | ARRAY-ITEM
 *  ARRAY-ITEM ::= IDENT "[" EXPRESSION "]"
 *  ASSIGNOP ::= ":=" | "+=" | "-=" | "*=" | "/="
 */
void parse_assignment(int level, int &TX)
{
    TABLE_ITEM ident;
    SYMBOL assign_op;
    int array_index, op_code;
    
    if (SYM != SYM_IDENT)
        panic(0, "ASSIGNMENT: expected IDENT, got: %s", SYMOUT[SYM]);
    GET_IDENT(ID, TX, &ident);
    if (ident.KIND == KIND_VARIABLE) {
        GetSym();
    } else if (ident.KIND == KIND_ARRAY) {
        parse_array_dereference(level, TX);
    } else {
        panic(12, "ASSIGNMENT: cannot assign to non-variable %s", ID);
    }

    if (SYM != SYM_ASSIGN && SYM != SYM_ADD_ASSIGN && SYM != SYM_SUB_ASSIGN
        && SYM != SYM_MUL_ASSIGN && SYM != SYM_DIV_ASSIGN)
        panic(13, "ASSIGNMENT: unexpected token: %s", SYMOUT[SYM]);
    assign_op = SYM;
    GetSym();

    if (assign_op == SYM_ASSIGN) {
        // calculate right side value
        parse_expression(level, TX);
    } else {
        // FIXME
        if (ident.KIND == KIND_ARRAY)
            panic(0, "ASSIGNMENT: not support self assignment for array type,"
                  "try use a[i] := a[i] + 1");
        // load variable
        GEN(LOD, level - ident.vp.LEVEL, ident.vp.ADDRESS,
            "load variable %s", ident.NAME);

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
        GEN(OPR, 0, op_code, "binary operation");
    }

    // store value
    if (ident.KIND == KIND_VARIABLE)
        GEN(STO, level - ident.vp.LEVEL, ident.vp.ADDRESS,
            "store to variable %s", ident.NAME);
    else
        GEN(STI, 0, 0, "store to array item");
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

    if (SYM != SYM_IF)
        panic(0, "IF-STMT: expected IF, got: %s", SYMOUT[SYM]);
    GetSym();

    // parse condition
    parse_expression(level, TX);
    cond_jmp_cx = GEN(JPC, 0, 0, "false jump to skip then part");

    // parse then part
    if (SYM != SYM_THEN)
        panic(16, "IF-STMT: expected THEN, got: %s", SYMOUT[SYM]);
    GetSym();
    parse_statement(level, TX);

    // parse else part if exists
    if (SYM == SYM_ELSE) {
        GetSym();

        then_jmp_cx = GEN(JMP, 0, 0, "skip else part");
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

    if (SYM != SYM_WHILE)
        panic(0, "WHILE-STMT: expect WHILE, got: %s", SYMOUT[SYM]);
    GetSym();

    while_cx = CX;

    // parse expression
    parse_expression(level, TX);
    cond_jmp_cx = GEN(JPC, 0, 0, "false jump to skip while body");
    
    if (SYM != SYM_DO)
        panic(18, "WHILE-STMT: expect DO, got: %s", SYMOUT[SYM]);
    GetSym();

    // parse body
    parse_statement(level, TX);
    GEN(JMP, 0, while_cx, "jmp to while begin");
    
    // back patch
    CODE[cond_jmp_cx].A = CX;
}

/*
 * Description:
 *
 *  FOR-STMT in PL/0:
 *  
 *      FOR I := 0 STEP 1 UNTIL 5 DO WRITE(I)
 *
 *  is equal to this C form:
 *
 *      for (i = 0; i <= 5; i++)
 *          write(i);
 *
 * Grammar:
 *
 *  FOR-STMT ::= FOR IDENT ":=" EXPRESSION
 *                  STEP EXPRESSION
 *                  UNTIL EXPRESSION
 *                  DO STATEMENT
 *
 * Instructions Layout:
 * +----------------------------------------------------+
 * |                                                    |
 * |                ident := expression                 |
 * |                                                    |
 * +----------------------------------------------------+
 * |                    JMP UNTIL_CX                    |
 * +----------------------------------------------------+ <- FOR_CX
 * |                                                    |
 * |                    step part                       |
 * |                                                    |
 * +----------------------------------------------------+ <- UNTIL_CX
 * |                                                    |
 * |                    until part                      |
 * |                                                    |
 * +----------------------------------------------------+
 * |                    JPC 0 OUT_CX                    |
 * +----------------------------------------------------+
 * |                                                    |
 * |                      do part                       |
 * |                                                    |
 * +----------------------------------------------------+
 * |                    JMP FOR_CX                      |
 * +----------------------------------------------------+ <- OUT_CX
 */
void parse_for(int level, int &TX)
{
    int for_cx, until_cx, jmp_until_cx, jmp_out_cx;
    TABLE_ITEM ident;

    if (SYM != SYM_FOR)
        panic(0, "FOR-STMT: expect FOR, got: %s", SYMOUT[SYM]);
    GetSym();

    // parse assign expression
    if (SYM != SYM_IDENT)
        panic(0, "FOR-STMT: expect IDENT, got: %s", SYMOUT[SYM]);
    GET_IDENT(ID, TX, &ident);
    if (ident.KIND != KIND_VARIABLE)
        panic(12, "FOR-STMT: cannot assign to non-variable %s", ID);
    GetSym();

    if (SYM != SYM_ASSIGN)
        panic(0, "FOR-STMT: expect ':=', got: %s", SYMOUT[SYM]);
    GetSym();

    // store initial value to loop variable
    parse_expression(level, TX);
    GEN(STO, level - ident.vp.LEVEL, ident.vp.ADDRESS,
        "load loop variable %s", ident.NAME);
    jmp_until_cx = GEN(JMP, 0, 0, "jump to until part");

    // parse step part
    for_cx = CX;
    if (SYM != SYM_STEP)
        panic(0, "FOR-STMT: expect STEP, got: %s", SYMOUT[SYM]);
    GetSym();

    // update loop variable
    GEN(LOD, level - ident.vp.LEVEL, ident.vp.ADDRESS,
        "load loop variable %s", ident.NAME);
    parse_expression(level, TX);
    GEN(OPR, 0, 2, "increase step");
    GEN(STO, level - ident.vp.LEVEL, ident.vp.ADDRESS,
        "update loop variable %s", ident.NAME);
    
    // parse until part
    until_cx = CX;
    if (SYM != SYM_UNTIL)
        panic(0, "FOR-STMT: expect UNTIL, got: %s", SYMOUT[SYM]);
    GetSym();

    // compare loop variable with upper bound
    GEN(LOD, level - ident.vp.LEVEL, ident.vp.ADDRESS,
        "load loop variable %s", ident.NAME);
    parse_expression(level, TX);
    GEN(OPR, 0, 13, "compare loop variable with upper bound");
    jmp_out_cx = GEN(JPC, 0, 0, "false jump to skip for body");

    // parse do part
    if (SYM != SYM_DO)
        panic(0, "FOR-STMT: expect DO, got: %s", SYMOUT[SYM]);
    GetSym();
    parse_statement(level, TX);
    GEN(JMP, 0, for_cx, "jump to for start");


    // back patch address
    CODE[jmp_until_cx].A = until_cx;
    CODE[jmp_out_cx].A = CX;
}

/*
 * Grammar:
 *
 *  CALL-STMT ::= CALL IDENT
 */
void parse_call(int level, int &TX)
{
    int arg_count;
    TABLE_ITEM ident;

    if (SYM != SYM_CALL)
        panic(0, "CALL: expected CALL, got: %s", SYMOUT[SYM]);
    GetSym();

    if (SYM != SYM_IDENT)
        panic(14, "CALL-STMT: expected procedure name, got: %s", SYMOUT[SYM]);
    
    GET_IDENT(ID, TX, &ident);
    if (ident.KIND != KIND_PROCEDURE && ident.KIND != KIND_FUNCTION)
        panic(15, "CALL-STMT: %s should be a procedure or function", ID);
    GetSym();

    GEN(MST, level - ident.vp.LEVEL, 0, "build stack frame for %s", ident.NAME);
    arg_count = 0;
    if (SYM == SYM_LPAREN)
        // TODO validate arguments count
        arg_count = parse_argument(level, TX);
    GEN(CAL, arg_count, ident.vp.ADDRESS, "call %s", ident.NAME);
}

/*
 * Grammar:
 *
 *  READ-STMT ::= READ "(" ASSIGNABLE , ["," ASSIGNABLE] ")"
 *  ASSIGNABLE ::= IDENT
 *               | ARRAY-ITEM
 */
void parse_read(int level, int &TX)
{
    TABLE_ITEM ident;

    if (SYM != SYM_READ)
        panic(0, "READ: expected READ, got: %s", SYMOUT[SYM]);
    GetSym();

    if (SYM != SYM_LPAREN)
        panic(34, "READ-STMT: expect '(', got: %s", SYMOUT[SYM]);

    do {
        GetSym();
        if (SYM != SYM_IDENT)
            panic(35, "READ-STMT: expect identity, got: %s", SYMOUT[SYM]);

        GET_IDENT(ID, TX, &ident);
        if (ident.KIND == KIND_VARIABLE)
            GetSym();
        else if (ident.KIND == KIND_ARRAY)
            parse_array_dereference(level, TX);
        else
            panic(35, "READ-STMT: identity %s should be variable or array item", ID);
        GEN(OPR, 0, 16, "read from stdin");
        if (ident.KIND == KIND_VARIABLE)
            GEN(STO, level - ident.vp.LEVEL, ident.vp.ADDRESS,
                "store to variable %s", ident.NAME);
        else if (ident.KIND == KIND_ARRAY)
            GEN(STI, 0, 0, "store to array item");
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
    if (SYM != SYM_WRITE)
        panic(0, "WRITE-STMT: expected WRITE, got: %s", SYMOUT[SYM]);
    GetSym();

    if (SYM == SYM_LPAREN) {
        GetSym();

        parse_expression(level, TX);
        GEN(OPR, 0, 14, "write to stdout");
        while (SYM == SYM_COMMA) {
            GetSym();

            parse_expression(level, TX);
            GEN(OPR, 0, 14, "write to stdout");
        }

        if (SYM != SYM_RPAREN)
            panic(33, "WEITE-STMT: expected ')', got: %s", SYMOUT[SYM]);
        GetSym();
    } /* SYM == SYM_LPAREN */
    
    else {
        GEN(OPR, 0, 15, "write line break");
    }
}

/*
 * Grammar:
 *
 *  RETURN-STMT ::= RETURN
 *                | RETURN EXPRESSION(*)
 *
 * (*) By now, procedure can also return value.
 */
void parse_return(int level, int &TX)
{
    int jmp_out_cx;

    if (SYM != SYM_RETURN)
        panic(0, "RETURN-STMT: expected RETURN, got: %s", SYMOUT[SYM]);
    GetSym();

    // must be expression
    // TODO need to check body type?
    if (SYM != SYM_SEMICOLON && SYM != SYM_END) {
        parse_expression(level, TX);
        GEN(STR, 0, 0, "store return value");
    }

    jmp_out_cx = GEN(JMP, 0, 0, "exit block");
    exit_frame_add(jmp_out_cx);
}

void parse_expression(int level, int &TX)
{
    parse_or_cond(level, TX);
}

/*
 * Grammar:
 *
 *  OR_COND ::= AND_COND ["||" AND_COND]
 */
void parse_or_cond(int level, int &TX)
{
    parse_and_cond(level, TX);

    while (SYM == SYM_OR) {
        GetSym();

        parse_and_cond(level, TX);
        GEN(OPR, 0, 18, "calculate ||");
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
        GEN(OPR, 0, 17, "calculate &&");
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
        GEN(OPR, 0, 6, "calculate odd");
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
            GEN(OPR, 0, op_code, "calculate bool");
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
            GEN(OPR, 0, 2, "calculate +");
        else
            GEN(OPR, 0, 3, "calculate -");
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
            GEN(OPR, 0, 4, "calculate *");
        else
            GEN(OPR, 0, 5, "calculate /");
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
        GEN(OPR, 0, 1, "calculate -");
    } /* SYM == SYM_MINUS */
    
    else if (SYM == SYM_PLUS) {
        GetSym();
        parse_unary(level, TX);
    } /* SYM == SYM_PLUS */

    else if (SYM == SYM_NOT) {
        GetSym();
        parse_unary(level, TX);
        GEN(OPR, 0, 7, "calculate not");
    } /* SYM == SYM_NOT */

    else {
        parse_factor(level, TX);
    }
}

/*
 * Grammar:
 *
 *  FUNCTION-CALL ::= CALL IDENT {"(" ARGUMENTS ")"}
 */
void parse_function_call_expression(int level, int &TX)
{
    int arg_count;
    TABLE_ITEM ident;

    if (SYM != SYM_CALL)
        panic(0, "FUNCTION-CALL: expected CALL, got: %s", SYMOUT[SYM]);
    GetSym();

    if (SYM != SYM_IDENT)
        panic(0, "FUNCTION-CALL: expected function name, got: %s", SYMOUT[SYM]);

    GET_IDENT(ID, TX, &ident);
    if (ident.KIND != KIND_FUNCTION)
        panic(0, "FUNCTION-CALL: %s should be a function", ID);
    GetSym();

    GEN(MST, level - ident.vp.LEVEL, 0, "build stack frame for %s", ident.NAME);
    arg_count = 0;
    if (SYM == SYM_LPAREN)
        // TODO validate arguments count
        arg_count = parse_argument(level, TX);
    GEN(CAL, arg_count, ident.vp.ADDRESS, "call function %s", ident.NAME);
}

/*
 * Grammar:
 *
 *  FACTOR ::= IDENT
 *           | ARRAY-DEREFRENCE
 *           | INTEGER
 *           | FLOAT
 *           | CHAR
 *           | CALL IDENT
 *           | "(" EXPRESSION ")"
 *
 *  INTEGER ::= [0-9]+  range: [-2147483648, 2147483647]
 *  FLOAT ::= [0-9]+"."[0-9]+
 *  CHAR ::= "'" [a-zA-Z] "'"
 */
void parse_factor(int level, int &TX)
{
    TABLE_ITEM ident;

    if (SYM == SYM_IDENT) {
        GET_IDENT(ID, TX, &ident);

        switch (ident.KIND) {
            case KIND_CONSTANT:
                GEN(LIT, 0, ident.vp.ADDRESS, "load constant %s", ident.NAME);
                GetSym();
                break;
            case KIND_VARIABLE:
                GEN(LOD, level - ident.vp.LEVEL, ident.vp.ADDRESS,
                    "load variable %s", ident.NAME);
                GetSym();
                break;
            case KIND_ARRAY:
                parse_array_dereference(level, TX);
                GEN(LID, 0, 0, "load array item");
                break;
            default:
                panic(21, "FACTOR: identity %s type should be CONST, VARIABLE or ARRAY", ID);
        }
    } /* SYM == SYM_IDENT */

    else if (SYM == SYM_INTEGER) {
        if (INTEGER > INTEGER_MAX) {
            panic(31, "FACTOR: integer too large: %d", INTEGER);
            INTEGER = 0;
        }

        GEN(LIT, 0, constant_enter(INTEGER), "load integer constant %d", INTEGER);
        GetSym();
    } /* SYM == SYM_INTEGER */

    else if (SYM == SYM_CHAR) {
        GEN(LIT, 0, constant_enter(CHAR), "load char constant %c", CHAR);
        GetSym();
    } /* SYM == SYM_CHAR */

    else if (SYM == SYM_FLOAT) {
        GEN(LIT, 0, constant_enter(FLOAT), "load float constant %f", FLOAT);
        GetSym();
    } /* SYM == SYM_FLOAT */

    else if (SYM == SYM_CALL) {
        parse_function_call_expression(level, TX);
    } /* SYM == SYM_CALL */

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

/*
 * Grammar:
 *
 *  ARRAY-DEREFRENCE ::= IDENT "[" EXPRESSION "]"
 */
void parse_array_dereference(int level, int &TX)
{
    TABLE_ITEM ident;

    if (SYM != SYM_IDENT)
        panic(0, "ARRAY-DEREFRENCE: expect identity, got: %s", SYMOUT[SYM]);
    GET_IDENT(ID, TX, &ident);
    GetSym();
    GEN(LDA, level - ident.vp.LEVEL, ident.vp.ADDRESS,
        "load array %s base address", ident.NAME);

    if (SYM != SYM_LBRACKET)
        panic(0, "ARRAY-DEREFRENCE: expect '[', got: %s", SYMOUT[SYM]);
    GetSym();

    // TODO check index range.
    parse_expression(level, TX);
    GEN(IXA, 0, 0, "calculate item address from index");

    if (SYM != SYM_RBRACKET)
        panic(0, "ARRAY-DEREFRENCE: expect ']', got: %s", SYMOUT[SYM]);
    GetSym();
}

// Start a new exit frame.
void exit_frame_begin()
{
    int i;

    CURRENT_EXIT_FRAME = CURRENT_EXIT_FRAME + 1;
    EXIT_FRAMES[CURRENT_EXIT_FRAME] = (int *) malloc(sizeof(int) * EXIT_FRAMES_SIZE);
    if (EXIT_FRAMES[CURRENT_EXIT_FRAME] == NULL)
        panic(0, "exit_frame_begin: unable to alloc memory for exit frame");
    for (i = 0; i < EXIT_FRAMES_SIZE; i++)
        EXIT_FRAMES[CURRENT_EXIT_FRAME][i] = 0;
}

// Add a return jump statement to exit frame.
void exit_frame_add(int return_stmt_cx)
{
    int len;

    if (CURRENT_EXIT_FRAME < 0)
        panic(0, "exit_frame_add: should start a new exit frame first");
    len = EXIT_FRAMES[CURRENT_EXIT_FRAME][0];
    if (len >= EXIT_FRAMES_SIZE)
        panic(0, "exit_frame_add: exit frame too large");
    EXIT_FRAMES[CURRENT_EXIT_FRAME][++len] = return_stmt_cx;
    EXIT_FRAMES[CURRENT_EXIT_FRAME][0] = len;
}

// End an exit frame & back patch return address.
void exit_frame_end(int body_end_cx)
{
    int i, len, return_stmt_cx;

    if (CURRENT_EXIT_FRAME < 0)
        panic(0, "exit_frame_end: no active exit frame");

    // back patch return address
    len = EXIT_FRAMES[CURRENT_EXIT_FRAME][0];
    for (i = 1; i <= len; i++) {
        return_stmt_cx = EXIT_FRAMES[CURRENT_EXIT_FRAME][i];
        CODE[return_stmt_cx].A = body_end_cx;
    }

    free(EXIT_FRAMES[CURRENT_EXIT_FRAME]);
    CURRENT_EXIT_FRAME = CURRENT_EXIT_FRAME - 1;
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
    ASCII_SYMBOL['['] = SYM_LBRACKET;   ASCII_SYMBOL[']'] = SYM_RBRACKET;

    i = -1;
    strcpy(KW_ALFA[++i], "BEGIN");
    strcpy(KW_ALFA[++i], "CALL");
    strcpy(KW_ALFA[++i], "CONST");
    strcpy(KW_ALFA[++i], "DO");
    strcpy(KW_ALFA[++i], "ELSE");
    strcpy(KW_ALFA[++i], "END");
    strcpy(KW_ALFA[++i], "FOR");
    strcpy(KW_ALFA[++i], "FUNCTION");
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
    KW_SYMBOL[++i] = SYM_FUNC;
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
    strcpy(INST_ALFA[HLT], "HLT");   strcpy(INST_ALFA[MST], "MST");
    strcpy(INST_ALFA[STR], "STR");   strcpy(INST_ALFA[LDA], "LDA");
    strcpy(INST_ALFA[IXA], "IXA");   strcpy(INST_ALFA[LID], "LID");
    strcpy(INST_ALFA[STI], "STI");

    // Setup constant table.
    CONSTANT_TABLE_INDEX = -1;           /* current constant address */

    // Setup exit frames list.
    CURRENT_EXIT_FRAME = -1;
}

// Initialize program.
void Init()
{
    SetupLanguage();
    ResetLexer();
}

void Main()
{
    int TX, pc;

    Init();

    log("Start compiling program.");
    GetSym();
    TX = 0;
    pc = parse_program(TX);
    ListCode(0);
    log("Compile finish.");

    log("Start executing program.");
    Interpret(pc);
    log("Execute finish.");
}

#ifdef CPP_BUILDER
void __fastcall TForm1::ButtonRunClick(TObject *Sender)
{
    if ((FIN = fopen((Form1->EditName->Text + ".PL0").c_str(), "r"))) {
        FOUT = fopen((Form1->EditName->Text + ".COD").c_str(), "w");
    }

    Main();

    fclose(FIN);
    fclose(FOUT);
}

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
