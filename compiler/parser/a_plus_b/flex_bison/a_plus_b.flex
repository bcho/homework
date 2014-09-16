/* a_plus_b */

/* C Declarations */
%{
#include "a_plus_b.h"
#include "tokens.h"
int yyerror(char const *s);
%}

DIGIT       [0-9]
NUM         {DIGIT}+
PLUS        +
MINUS       -

%%

{NUM}       { yylval.int_val = atoi(yytext); return NUM; }
"+"         { yylval.op_val = '+'; return PLUS; }
"-"         { yylval.op_val = '-'; return MINUS; }
[ \t]*      {}
[\n]        { yylineno++; }
.           { yyerror("unknown token!"); }

%%
