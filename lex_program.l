%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char name[40];
int name_len = 0;
%}

%%

[0-9a-zA-Z]+ {
    int contains = 0;
    char forbidden[5] = "";  // store forbidden letters found
    int idx = 0;

    for (int j = 0; yytext[j] != '\0'; j++) {
        for (int i = 0; i < name_len; i++) {
            if (tolower(yytext[j]) == tolower(name[i])) {
                contains = 1;
                // store forbidden letter if not already added
                int already = 0;
                for (int k = 0; k < idx; k++) {
                    if (tolower(forbidden[k]) == tolower(name[i])) {
                        already = 1;
                        break;
                    }
                }
                if (!already) {
                    forbidden[idx++] = name[i];
                    forbidden[idx] = '\0';
                }
                break;
            }
        }
    }

    if (!contains)
        printf("%-10s accepted\n", yytext);
    else
        printf("%-10s rejected (contains: %s)\n", yytext, forbidden);
}

[ \t\n]+ {}  // ignore whitespace

%%

int yywrap(void) {
    return 1;
}

int main() {
    printf("Enter your name: ");
    scanf("%39s", name);

    // Use only first 4 letters of name
    name_len = strlen(name) < 4 ? strlen(name) : 4;

    printf("Enter input text (Ctrl+D to end):\n");
    yylex();

    return 0;
}

