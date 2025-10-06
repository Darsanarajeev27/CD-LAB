%{
#include <stdio.h>
#include <stdlib.h>
int fval=0;
int yylex(void);
int yyerror(char *s);

struct node 
{
    struct node * left;
    struct node * right;
    char value;
    
}*head;

int strength(struct node *NODE)
{
    if(NODE==NULL)
    {
        return 0;
    }
    return 1+strength(NODE->left)+strength(NODE->right);
}


struct qnode
{
    int nvalue;
    int start;
    int end;
    struct node * tnode;
}q[100];

int front=0;

%}

%union {
     struct node *tnode;
     char cval;    
}


%token <tnode> LETTER
%token <tnode> PLUS MINUS MULTIPLICATION DIVISION LBRACKET RBRACKET EQ
%type  <tnode> A B C E
%%
E: LETTER EQ A {$$=malloc(sizeof(struct node));$$->left=$1;$$->right=$3;$$->value='=';head=$$;}
 | A {$$=$1;head=$$;}
 ;
A: A PLUS B {$$=malloc(sizeof(struct node));$$->left=$1;$$->right=$3;$$->value='+';}
 | B        {$$=$1;}
 | A MINUS B {$$=malloc(sizeof(struct node));$$->left=$1;$$->right=$3;$$->value='-';}
 ;

B: B MULTIPLICATION C {$$=malloc(sizeof(struct node));$$->left=$1;$$->right=$3;$$->value='*';}
 | B DIVISION C {$$=malloc(sizeof(struct node));$$->left=$1;$$->right=$3;$$->value='/';}
 | C {$$=$1;}
 ;

C: LETTER {$$=$1;}
 | LBRACKET A RBRACKET {$$=$2;}
 ;
%%


int main() {
    printf("Enter expression: ");
    if (yyparse() == 0) 
    {
	printf("\n\nAbstract parse tree****:\n\n");
	int n=60;
    int screen=0;
    int level=0;
    q[0].nvalue=2;
    q[0].start=n;
    q[0].tnode=head;
    
    q[1].nvalue=0;
    
	int k=0;
int rear=1;
    
    while(front<rear)
    {
        if(q[front].nvalue==0)
        {
            printf("\n");
            screen=0;
            rear++;
	    q[rear].nvalue=0;
	    front++;
            if(front<rear && level%2==0)
            {
            n/=2;
            }
            level++;
        }
        else if(q[front].nvalue==1)
        {   
            for(screen;screen<q[front].start;screen++)
		{printf(" ");
		}
            for(screen;screen<=q[front].end;screen++)
		{printf("-");
		}
            if(q[front].tnode->left)
            {
                rear++;
                q[rear].nvalue=2;
                q[rear].tnode=q[front].tnode->left;
                q[rear].start=q[front].start;
            }
            if(q[front].tnode->right)
            {
                rear++;
                q[rear].nvalue=2;
                q[rear].tnode=q[front].tnode->right;
                q[rear].start=q[front].end;
                
            }
            front++;
        }
        else
        {
		
            for(screen;screen<q[front].start;screen++)
		{printf(" ");
		}
            printf("%c",q[front].tnode->value);
	    screen++;
            if(q[front].tnode->left||q[front].tnode->right)
            {
                rear++;
                q[rear].tnode=q[front].tnode;
                q[rear].nvalue=1;
                q[rear].start=(q[front].tnode->left)?q[front].start-4*(strength(q[front].tnode->left->right)+1):q[front].start;
                q[rear].end=(q[front].tnode->right)?q[front].start+4*(strength(q[front].tnode->right->left)+1):q[front].start;
                
            }
	    front++;
        }
	k++;
	//if(k==2)return 0;
        
    }
    

        
    }
    printf("\n\n");
    return 0;
}

int yywrap(void) {
    return 1;
}

int yyerror(char *s) {
    printf("Error: %s\n", s);
    return 0;
}