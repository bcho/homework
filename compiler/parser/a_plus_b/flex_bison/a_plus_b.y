/* a_plus_b */

/* C Declarations */
%{
#include "a_plus_b.h"

int yylex();
void yyerror(char const *);
%}
/* Bision Declarations */

%union {
    int int_val;
    char op_val;
}

%start line

%token <int_val> NUM
%type <int_val> formula
%left PLUS
%left MINUS

%%

/* Grammar */

line:

|   formula            { printf("%d\n", $1); }
;

formula:
    NUM                     { $$ = $1; }
|   formula PLUS formula    { $$ = $1 + $3; }
|   formula MINUS formula   { $$ = $1 - $3; }
;

%%

void yyerror(char const *s)
{
    extern int yylineno;
    extern char *yytext;

    printf("error: %d %s:%s", yylineno, yytext, s);
}

int main()
{
    yyparse();

    return 0;
}
