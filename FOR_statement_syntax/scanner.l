%{
    #include "parser.tab.h"
    #include<stdlib.h>
%}

%% 
"for"   {return FOR;}
"++"    {return INCREMENT;}
[a-zA-Z_][a-zA-Z0-9_]*  {return ID;}
[0-9]+ {return NUM;}
"==" {return OP;}
"<=" {return OP;}
">=" {return OP;}
"!=" {return OP;}
"=" {return EQ;}
"(" {return LP;}
")" {return RP;}
";" {return SC;}
"{" {return LPP;}
"}" {return RPP;}
[<] {return LT;}
[>] {return GT;}
[-+/*] {return OP;}
[ \t\n] {}
. {}
%%

int yywrap(void){
    return 1;
}
