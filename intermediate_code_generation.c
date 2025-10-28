#include <stdio.h>
#include <string.h>

void gen_code_for_operator(char *inp, char operator, char *reg)
{
    int i = 0, j = 0;
    char temp[100];
    
    while (inp[i] != '\0')
    {
        if (inp[i] == operator)
        {
            // Print three-address code line
            printf("%c\t%c\t%c\t%c\n", operator, *reg, inp[i - 1], inp[i + 1]);

            // Replace the subexpression with the result register
            temp[j - 1] = *reg;

            i += 2;       // Skip next operand since it's consumed
            (*reg)--;     // Move to next register (Z → Y → X ...)
            continue;
        }
        temp[j++] = inp[i++];
    }

    temp[j] = '\0';
    strcpy(inp, temp);
}

void gen_code(char *inp)
{
    char reg = 'Z'; // Start from register Z
    // Operator precedence: /, *, +, -, =
    gen_code_for_operator(inp, '/', &reg);
    gen_code_for_operator(inp, '*', &reg);
    gen_code_for_operator(inp, '+', &reg);
    gen_code_for_operator(inp, '-', &reg);
    gen_code_for_operator(inp, '=', &reg);
}

int main()
{
    char inp[100];
    printf("Enter expression:\n\n");
    scanf("%s", inp);
    printf("Oprtr\tDestn\tOp1\tOp2\n");
    gen_code(inp);
    return 0;
}
