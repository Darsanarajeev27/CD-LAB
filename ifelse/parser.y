%{
#include <stdio.h>
int yylex(void);
int yyerror(char *s);
%}

%token IF ELSE ID NUM
%token OP EQ EQEQ NE LT GT LE GE
%token SC LP RP LPP RPP

%%

stmt   : ifstmt
       | expr SC
       ;

ifstmt : IF LP cond RP LPP stmts RPP
       | IF LP cond RP LPP stmts RPP ELSE LPP stmts RPP
       | IF LP cond RP stmt
       | IF LP cond RP stmt ELSE stmt
       ;

cond   : expr LT expr
       | expr GT expr
       | expr LE expr
       | expr GE expr
       | expr EQEQ expr
       | expr NE expr
       ;

expr   : ID
       | NUM
       | ID EQ expr
       | LP expr RP
       ;

stmts  : /* empty */
       | stmts stmt
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
