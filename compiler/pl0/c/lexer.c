#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "token.h"
#include "lexer.h"


/* TODO recalculate the cols position base on the token type. */
#define MAKE_TOKEN(type, value) token_create((type), (value), cur_lines, cur_cols - 1)
#define MAKE_SIMPLE_TOKEN(type) MAKE_TOKEN((type), NULL)
#define MAKE_IDENT_TOKEN(value) token_create_from_ident((value), cur_lines, cur_cols - 1)


/* source code */
static FILE *src_stream = NULL;
static char line_buf[LEXER_LINE_MAX_LENGTH];
static int line_length = 0;
static int cur_lines = 0;
static int cur_cols = 0;

/* lexer DFA states */
enum lexer_state {
    START,
    IN_ASSIGNMENT,
    IN_COMMENT,
    IN_NUM,
    IN_IDENT,
    DONE
};


/* Get a character from input. */
static char
get_char()
{
    if (src_stream == NULL)
        panic("lexer: cannot read source file.");

    /* Reach end of line, open a new line. */
    if (cur_cols >= line_length) {
        cur_lines += 1;
        if (fgets(line_buf, LEXER_LINE_MAX_LENGTH - 1, src_stream)) {
            line_length = strlen(line_buf);
            cur_cols = 0;
        } else {
            return EOF;
        }
    }

    return line_buf[cur_cols++];
}

/* Unget a character to input. */
static void
unget_char()
{
    /* Because pl0's statment cannot cross line,
     * so it's ok to subtract 1 to unget. */
    cur_cols--;
}


void
lexer_set_src_stream(FILE *stream)
{
    src_stream = stream;
}


struct token *
token_get()
{
    char c;
    struct token *cur_token;
    enum lexer_state state;
    char cur_value[TOKEN_IDENT_MAX_LENGTH];
    int cur_value_idx;

    state = START;

    memset(cur_value, 0, TOKEN_IDENT_MAX_LENGTH);
    cur_value_idx = 0;

    while (state != DONE) {
        c = get_char();

        switch (state) {
            case START:
                /* test against multi-characters states */
                if (isdigit(c)) {
                    state = IN_NUM;
                    
                    cur_value[cur_value_idx++] = c;
                } else if (isalpha(c)) {
                    state = IN_IDENT;

                    cur_value[cur_value_idx++] = c;
                } else if (c == ':') {
                    state = IN_ASSIGNMENT;
                } else if (isspace(c)) {
                    /* skip whitespaces */ ;

                /* single character token */
                } else {
                    state = DONE;
                    switch (c) {
                        case EOF:
                            cur_token = MAKE_SIMPLE_TOKEN(END_OF_FILE);
                            break;
                        case '+':
                            cur_token = MAKE_SIMPLE_TOKEN(PLUS);
                            break;
                        case '-':
                            cur_token = MAKE_SIMPLE_TOKEN(MINUS);
                            break;
                        case '*':
                            cur_token = MAKE_SIMPLE_TOKEN(TIMES);
                            break;
                        case '/':
                            cur_token = MAKE_SIMPLE_TOKEN(OVER);
                            break;
                        case '=':
                            cur_token = MAKE_SIMPLE_TOKEN(EQ);
                            break;
                        case '#':
                            cur_token = MAKE_SIMPLE_TOKEN(NEQ);
                            break;
                        case '<':
                            /* peek for `<=` */
                            if (get_char() == '=') {
                                cur_token = MAKE_SIMPLE_TOKEN(LEQ);
                            } else {
                                cur_token = MAKE_SIMPLE_TOKEN(LT);
                                unget_char();
                            }
                            break;
                        case '>':
                            /* peek for `>=` */
                            if (get_char() == '=') {
                                cur_token = MAKE_SIMPLE_TOKEN(GEQ);
                            } else {
                                cur_token = MAKE_SIMPLE_TOKEN(GT);
                                unget_char();
                            }
                            break;
                        case '(':
                            /* peek for `(*` */
                            if (get_char() == '*') {
                                state = IN_COMMENT;
                            } else {
                                cur_token = MAKE_SIMPLE_TOKEN(LPAREN);
                                unget_char();
                            }
                            break;
                        case ')':
                            cur_token = MAKE_SIMPLE_TOKEN(RPAREN);
                            break;
                        case ';':
                            cur_token = MAKE_SIMPLE_TOKEN(SEMI);
                            break;
                        default:
                            cur_token = MAKE_TOKEN(ERROR, "unknown lex error");
                            break;
                    }
                }
                break;  /* START */
            case IN_ASSIGNMENT:
                state = DONE;
                if (c == '=') {
                    cur_token = MAKE_SIMPLE_TOKEN(ASSIGN);
                } else {
                    cur_token = MAKE_TOKEN(ERROR, "missing `=` for assignment");
                    
                    /* restore from error */
                    unget_char();
                }
                break;  /* IN_ASSIGNMENT */
            case IN_NUM:
                if (isdigit(c)) {
                    cur_value[cur_value_idx++] = c;
                } else {
                    state = DONE;
                    
                    cur_token = MAKE_TOKEN(NUM, cur_value);

                    /* restore state */
                    unget_char();
                }
                break;  /* IN_NUM */
            case IN_IDENT:
                if (isalpha(c)) {
                    cur_value[cur_value_idx++] = c;
                } else {
                    state = DONE;

                    cur_token = MAKE_IDENT_TOKEN(cur_value);

                    /* restore state */
                    unget_char();
                }
                break;  /* IN_IDENT */
            case IN_COMMENT:
                /* skip over the comments */
                if (c == '*' && get_char() == ')') {
                    state = START;
                } else if (c == EOF) {
                    state = DONE;
                    cur_token = MAKE_TOKEN(ERROR, "unexpected EOF, maybe missing `*)`");
                }
                break; /* IN_COMMENT */
            case DONE:
            default:
                panic("token_get: should not reach here.");
                break;  /* DEFAULT */
        }   /* switch */
    }   /* while */

    return cur_token;
}
