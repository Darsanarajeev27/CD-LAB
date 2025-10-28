%{
#include <stdio.h>
int yylex(void);
int yyerror(char *s);
%}

%token DO WHILE ID NUM
%token OP EQ
%token SC LP RP LPP RPP

%%

stmt   : dowhilestmt
       ;

dowhilestmt : DO LPP stmts RPP WHILE LP cond RP SC
            ;

cond   : expr OP expr
       ;

expr   : ID
       | NUM
       | ID EQ expr
       | LP expr RP
       ;

stmts  : /* empty */
       | stmts stmt
       | stmts expr SC
       ;

%%

int yyerror(char *s) {
    printf("Error: %s\n", s);
    return 0;
}

int main() {
    printf("Enter your code (end with EOF):\n");
    if (yyparse() == 0)
        printf("Syntax correct\n");
    else
        printf("Invalid Syntax\n");
    return 0;
}
