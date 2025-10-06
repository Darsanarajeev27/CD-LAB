%{
#include "parser.tab.h"
#include <stdlib.h>
#include <stdio.h>
struct node 
{
    struct node * left;
    struct node * right;
    char value;
    
};
%}

%%
[a-zA-Z] {yylval.tnode=malloc(sizeof(struct node));yylval.tnode->left=NULL;yylval.tnode->right=NULL;yylval.tnode->value=yytext[0];return LETTER;}
[+] {yylval.tnode=malloc(sizeof(struct node));yylval.tnode->left=NULL;yylval.tnode->right=NULL;yylval.tnode->value=yytext[0];return PLUS;}
[/] {yylval.tnode=malloc(sizeof(struct node));yylval.tnode->left=NULL;yylval.tnode->right=NULL;yylval.tnode->value=yytext[0];return DIVISION;}
[*] {yylval.tnode=malloc(sizeof(struct node));yylval.tnode->left=NULL;yylval.tnode->right=NULL;yylval.tnode->value=yytext[0];return MULTIPLICATION;}
[-] {yylval.tnode=malloc(sizeof(struct node));yylval.tnode->left=NULL;yylval.tnode->right=NULL;yylval.tnode->value=yytext[0];return MINUS;}
[(] {yylval.tnode=malloc(sizeof(struct node));yylval.tnode->left=NULL;yylval.tnode->right=NULL;yylval.tnode->value=yytext[0];return LBRACKET;}
[)] {yylval.tnode=malloc(sizeof(struct node));yylval.tnode->left=NULL;yylval.tnode->right=NULL;yylval.tnode->value=yytext[0];return RBRACKET;}
[=] {yylval.tnode=malloc(sizeof(struct node));yylval.tnode->left=NULL;yylval.tnode->right=NULL;yylval.tnode->value=yytext[0];return EQ;}
[\n] {return 0;}
[ \t]   {};

%%