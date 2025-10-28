%{
    #include<stdio.h>
    int yylex(void);
    int yyerror(char *s);
%}

%token FOR ID NUM
%token EQ INCREMENT
%token LT GT 
%token OP
%token SC LP RP LPP RPP

%%
forstmt    : FOR LP exprs SC exprs SC exprs RP LPP stmts RPP
            | FOR LP exprs SC exprs SC exprs RP exprs SC
            ;
exprs : ID EQ expr
      | ID INCREMENT
      | ID LT NUM
      | ID GT NUM
      | expr
      ;
expr : expra
     | expr OP expra
     ;
expra : ID
      | NUM
      | LP expr RP
      ;
stmts : 
      | stmts stmt
      ;
stmt : exprs SC
     | forstmt
     ;
%%

int yyerror(char *s){
    printf("Error: %s\n",s);
    return 0;
}
int main(){
    printf("Enter your statement with EOF: ");
    if(yyparse()==0){
        printf("Valid syntax\n");
    } else{
        printf("Invalid syntax\n");
    }
    return 0;
}
