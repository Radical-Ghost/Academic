#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

// Structure to represent a Three-Address Code (TAC) instruction
typedef struct {
    char op[3];    // Operator
    char opr1[10]; // Operand 1
    char opr2[10]; // Operand 2
    char res[10];  // Result
} TAC;

TAC tac[MAX];
int tacCounter = 0;
int tempVarCount = 1;

// Function to generate a TAC instruction
void generateTAC(const char op[], const char opr1[], const char opr2[], const char res[]) {
    strcpy(tac[tacCounter].op, op);
    strcpy(tac[tacCounter].opr1, opr1);
    strcpy(tac[tacCounter].opr2, opr2);
    strcpy(tac[tacCounter].res, res);
    tacCounter++;
}

// Function to print the TAC instructions
void printTAC() {
    printf("\n*** Three-Address Code (TAC) ***\n");
    for (int i = 0; i < tacCounter; i++) {
        if (strcmp(tac[i].op, "=") != 0) printf("%s = %s %s %s\n", tac[i].res, tac[i].opr1, tac[i].op, tac[i].opr2);
        else printf("%s = %s \n", tac[i].res, tac[i].opr1);
    }
}

// Function to print the Quadruple table
void printQuadruple() {
    printf("\n*** Quadruple Table ***\n");
    printf("Operator\tOperand1\tOperand2\tResult\n");
    for (int i = 0; i < tacCounter; i++) {
        printf("%s\t\t%s\t\t%s\t\t%s\n", tac[i].op, tac[i].opr1, tac[i].opr2, tac[i].res);
    }
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Function to parse an arithmetic expression and generate TAC
void parseExpression(char expr[]) {
    char temp[10], opr1[10], opr2[10], result[10], lastTemp[10];
    char currentOpStr[2] = "";  
    int i = 0, j = 0;

    // Extract the result variable from the expression
    while (expr[i] != '=' && expr[i] != '\0') {
        result[j++] = expr[i++];
    }
    result[j] = '\0';
    if (expr[i] == '=') i++; 

    j = 0;
    char currentOp = '\0';
    lastTemp[0] = '\0';

    // Parse the rest of the expression
    while (expr[i] != '\0') {
        if (isspace(expr[i])) {
            i++;
            continue;
        }
        if (isOperator(expr[i])) {
            currentOp = expr[i];
            currentOpStr[0] = currentOp;
            currentOpStr[1] = '\0';
            i++;
            continue;
        }

        j = 0;
        while (isalnum(expr[i])) {
            opr1[j++] = expr[i++];
        }
        opr1[j] = '\0';

        if (currentOp) {
            sprintf(temp, "t%d", tempVarCount++);
            generateTAC(currentOpStr, lastTemp, opr1, temp);
            strcpy(lastTemp, temp);
            currentOp = '\0';
        } else {
            strcpy(lastTemp, opr1);
        }
    }
    
    // Generate the final assignment TAC
    generateTAC("=", lastTemp, "", result);
}

int main() {
    char expr[50];

    // Prompt the user to enter an arithmetic expression
    printf("Enter an arithmetic expression: ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = '\0'; // Remove the newline character

    // Parse the expression and generate TAC
    parseExpression(expr);
    // Print the TAC instructions
    printTAC();
    // Print the Quadruple table
    printQuadruple();

    return 0;
}