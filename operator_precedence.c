#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char input[100];
char stack[100];
int top = -1;

int oper(char a) {
    if (a == '+' || a == '-') return 0;
    else if (a == '*' || a == '/') return 1;
    return 4;
}

int precedence(char s, char i) {
    if (s == '$' && i == '$') return 2;  // accept
    if (s == '(' && i == ')') return 1;  // reduce
    if (i == '$') return 1;              // reduce on end
    if (s == '$') return 0;              // shift from empty stack
    if (s == '(' || i == '(') return 0;  // shift on '('
    if (i == ')') return 1;              // reduce on ')'

    // operators
    int ps = oper(s), pi = oper(i);
    if (ps < pi) return 0;   // shift
    else return 1;           // reduce
}

int reduce() {
    if (stack[top] == 'i') {
        stack[top] = 'e';
        return 1;
    }
    if (top >= 2 && 
        ((stack[top] == 'e' && stack[top-2] == 'e' && 
         (stack[top-1] == '+' || stack[top-1] == '-' || 
          stack[top-1] == '*' || stack[top-1] == '/')) ||
         (stack[top-1] == 'e' && stack[top] == ')' && stack[top-2] == '('))) {
        top -= 2;
        stack[top] = 'e';
        return 1;
    }
    return 0;
}

int main() {
    printf("Enter Input Expression: ");
    scanf("%s", input);

    // Add end markers
    int len = 0;
    while (input[len] != '\0') len++;
    input[len++] = '$';
    input[len] = '\0';

    stack[++top] = '$';

    printf("\nSTACK\t\t\tINPUT\n");

    int i = 0;
    while (1) {
        char curr = isalnum(input[i]) ? 'i' : input[i];
        int j = top;
        while (stack[j] == 'e') j--;

        int sol = precedence(stack[j], curr);
        if (sol == 0) { // shift
            stack[++top] = curr;
            i++;
        } else if (sol == 1) { // reduce
            if (!reduce()) {
                printf("\nINVALID STRING!\n");
                return 0;
            }
        } else if (sol == 2) { // accept
            printf("\nSTRING ACCEPTED!\n");
            return 0;
        } else {
            printf("\nINVALID STRING!\n");
            return 0;
        }

        // Print step
        for (int k = 0; k <= top; k++) printf("%c ", stack[k]);
        printf("\t\t");
        for (int j = i; input[j] != '\0'; j++) printf("%c ", input[j]);
        printf("\n");
    }
}
