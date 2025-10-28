%{
#include "parser.tab.h"
#include <stdlib.h>
%}

%%
"do"        { return DO; }
"while"     { return WHILE; }
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }
[0-9]+      { return NUM; }
"=="        {return OP;}
"<="        {return OP;}
">="        {return OP;}
"!="        {return OP;}
"="         { return EQ; }
"("         { return LP; }
")"         { return RP; }
"{"         { return LPP; }
"}"         { return RPP; }
[-+*/><]   { return OP; }
";"         { return SC; }
[ \t\n]     { /* ignore whitespace */ }
.           { /* ignore other chars */ }
%%

int yywrap(void) {
    return 1;
}
