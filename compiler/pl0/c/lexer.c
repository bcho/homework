#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "token.h"
#include "lexer.h"


#define MAKE_TOKEN(type, value) token_create((type), (value), cur_lines, cur_cols)
#define MAKE_SIMPLE_TOKEN(type) MAKE_TOKEN((type), NULL)


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
    /* TODO */
    // IN_COMMENT,
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

    state = START;

    while (state != DONE) {
        c = get_char();

        switch (state) {
            case START:
                /* test against multi-characters states */
                if (isdigit(c)) {
                    state = IN_NUM;
                    
                    // store character
                    printf("%c", c);
                } else if (isalpha(c)) {
                    state = IN_IDENT;

                    // store character
                    printf("%c", c);
                } else if (c == ':') {
                    state = IN_ASSIGNMENT;
                } else if (isspace(c)) {
                    /* skip whitespaces */
                    ;

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
                            cur_token = MAKE_SIMPLE_TOKEN(LPAREN);
                            break;
                        case ')':
                            cur_token = MAKE_SIMPLE_TOKEN(RPAREN);
                            break;
                        case ';':
                            cur_token = MAKE_SIMPLE_TOKEN(SEMI);
                            break;
                        default:
                            cur_token = MAKE_SIMPLE_TOKEN(ERROR);
                            break;
                    }
                }
                break;  /* START */
            case IN_ASSIGNMENT:
                state = DONE;
                if (c == '=') {
                    cur_token = MAKE_SIMPLE_TOKEN(ASSIGN);
                } else {
                    cur_token = MAKE_SIMPLE_TOKEN(ERROR);
                    
                    /* restore from error */
                    unget_char();
                }
                break;
            case IN_NUM:
                if (isdigit(c)) {
                    // store character
                    printf("%c", c);
                } else {
                    state = DONE;
                    
                    cur_token = MAKE_TOKEN(NUM, "number");

                    /* restore state */
                    unget_char();
                }
                break;
            case IN_IDENT:
                if (isalpha(c)) {
                    // store character
                    printf("%c", c);
                } else {
                    state = DONE;

                    cur_token = MAKE_TOKEN(IDENT, "ident");

                    /* restore state */
                    unget_char();
                }
                break;
            case DONE:
            default:
                panic("token_get: should not reach here.");
                break;
        }   /* switch */
    }   /* while */

    /* TODO handle reserved keywords */

    return cur_token;
}
