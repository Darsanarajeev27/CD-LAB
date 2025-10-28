%{
#include "parser.tab.h"
#include <stdlib.h>
%}

%%
"if"        { return IF; }
"else"      { return ELSE; }
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }
[0-9]+      { return NUM; }
"=="        {return EQEQ;}
"!="        {return NE;}
"<="        {return LE;}
">="        {return GE;}
"="         { return EQ; }
"("         { return LP; }
")"         { return RP; }
"{"         { return LPP; }
"}"         { return RPP; }
[-+*/]      { return OP; }
"<"         {return LT;}
">"         {return GT;}
";"         { return SC; }
[ \t\n]     { /* ignore whitespace */ }
.           { /* ignore other chars */ }
%%

int yywrap(void) {
    return 1;
}
