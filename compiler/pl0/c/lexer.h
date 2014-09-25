#ifndef LEXER_H
#define LEXER_H

#define LEXER_LINE_MAX_LENGTH 1024

/* set source file */
void lexer_set_src_stream(FILE *);

struct token *token_get();

#endif /* LEXER_H */
