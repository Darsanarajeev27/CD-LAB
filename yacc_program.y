%{
#include <stdio.h>
#include <ctype.h>

int yylex(void);
int yyerror(char *s);
int yywrap(void) { return 1; }
%}

%token LETTER NUMBER INVALID

%%

variable: LETTER rest
        ;

rest: LETTER rest
    | NUMBER rest
    | /* epsilon: empty */
    ;

%%

int yylex() {
    int c = getchar();

    if (isalpha(c)) return LETTER;
    if (isdigit(c)) return NUMBER;
    if (c == '\n' || c == EOF) return 0;  // end of input
    return INVALID;  // any other character
}

int yyerror(char *s) {
    printf("Invalid variable\n");
    return 0;
}

int main() {
    printf("Enter variable: ");
    if (yyparse() == 0) {
        printf("Valid variable\n");
    }
    return 0;
}





