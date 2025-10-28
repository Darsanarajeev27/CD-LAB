#include <stdio.h>
#include <string.h>

int main() {
    char icode[20][30];  // Stores intermediate code
    char str[30], opr[5];
    int i = 0;

    printf("Enter the intermediate code (one per line, type 'exit' to finish):\n");
    
    // Read intermediate code until "exit"
    while (1) {
        scanf("%s", icode[i]);
        if (strcmp(icode[i], "exit") == 0) break;
        i++;
    }

    printf("\nTarget 8086 Assembly Code:\n");
    printf("************************\n");

    i = 0;
    while (strcmp(icode[i], "exit") != 0) {
        strcpy(str, icode[i]);

        // Determine the operator in TAC
        switch (str[3]) {
            case '+': strcpy(opr, "ADD"); break;
            case '-': strcpy(opr, "SUB"); break;
            case '*': strcpy(opr, "MUL"); break;
            case '/': strcpy(opr, "DIV"); break;
            default: strcpy(opr, ""); break; // For assignments
        }

        // Generate assembly instructions
        // str format: x=y op z  (TAC)
        printf("MOV AX, %c\n", str[2]);       // Load operand1 into AX
        if (opr[0] != '\0')                   // If operator exists
            printf("%s AX, %c\n", opr, str[4]); // Perform operation with operand2
        printf("MOV %c, AX\n\n", str[0]);    // Store result into destination

        i++;
    }

    return 0;
}
