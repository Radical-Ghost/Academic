#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INSTRUCTIONS 100

// Structure to represent a TAC (Three Address Code) instruction
typedef struct {
    char op[10];
    char arg1[10];
    char arg2[10];
    char result[10]; 
} TACInstruction;

TACInstruction tac[MAX_INSTRUCTIONS];
int tacIndex = 0;

// Function to print the TAC instructions
void printTAC() {
    for (int i = 0; i < tacIndex; i++) {
        if(strcmp(tac[i].op, "None") != 0) {
            if(strcmp(tac[i].arg2, "None") == 0) 
                printf("%s = %s\n", tac[i].result, tac[i].arg1);
            else 
                printf("%s = %s %s %s\n", tac[i].result, tac[i].arg1, tac[i].op, tac[i].arg2);
        }
    }
}

// Function to remove redundant assignments
void removeRedundant() {
    for (int i = 0; i < tacIndex; i++)
        if (strcmp(tac[i].op, "None") != 0)
            for (int j = 0; j < tacIndex; j++)
                if (i != j && strcmp(tac[i].result, tac[j].arg1) == 0 && strcmp(tac[j].op, "=") == 0) {
                    strcpy(tac[j].op, "None");
                    for (int k = 0; k < tacIndex; k++) {
                        if (k != j) {  
                            if (strcmp(tac[k].arg1, tac[j].result) == 0) strcpy(tac[k].arg1, tac[i].result);
                            if (strcmp(tac[k].arg2, tac[j].result) == 0) strcpy(tac[k].arg2, tac[i].result);
                            if (strcmp(tac[k].result, tac[j].result) == 0) strcpy(tac[k].result, tac[i].result);
                        }
                    }
                }
}

// Function to remove common sub-expressions
void removeCommonSubExpressions() {
    for (int i = 0; i < tacIndex; i++)
        if (strcmp(tac[i].op, "None") != 0)
            for (int j = 0; j < tacIndex; j++)
                if (i != j && strcmp(tac[i].arg1, tac[j].arg1) == 0 && strcmp(tac[i].arg2, tac[j].arg2) == 0 && strcmp(tac[i].op, tac[j].op) == 0) {
                    strcpy(tac[j].op, "None");
                    for (int k = 0; k < tacIndex; k++) {
                        if (k != j) {  
                            if (strcmp(tac[k].arg1, tac[j].result) == 0) strcpy(tac[k].arg1, tac[i].result);
                            if (strcmp(tac[k].arg2, tac[j].result) == 0) strcpy(tac[k].arg2, tac[i].result);
                            if (strcmp(tac[k].result, tac[j].result) == 0) strcpy(tac[k].result, tac[i].result);
                        }
                    }
                }
}

// Function to perform constant folding
void constantFolding() {
    for (int i = 0; i < tacIndex; i++) {
        if (strcmp(tac[i].op, "None") != 0)
            if (isdigit(tac[i].arg1[0]) && isdigit(tac[i].arg2[0])) {
                int val1 = strtol(tac[i].arg1, NULL, 10);
                int val2 = strtol(tac[i].arg2, NULL, 10);
                int result;
                
                if (strcmp(tac[i].op, "+") == 0) result = val1 + val2;
                else if (strcmp(tac[i].op, "-") == 0) result = val1 - val2;
                else if (strcmp(tac[i].op, "*") == 0) result = val1 * val2;
                else if (strcmp(tac[i].op, "/") == 0) result = val1 / val2;
                
                sprintf(tac[i].arg1, "%d", result);
                strcpy(tac[i].arg2, "None");
            }             
    }
}

// Function to check if a result is used later in the TAC
int isUsedLater(int ptr) {
    for (int i = 0; i < tacIndex; i++)
        if (ptr != i)
            if (strcmp(tac[ptr].result, tac[i].arg1) == 0 || strcmp(tac[ptr].result, tac[i].arg2) == 0)
                return 1;   
    return 0;
}

// Function to remove dead code
void removeDeadCode() {
    for (int i = 0; i < tacIndex - 1; i++)
        if (strcmp(tac[i].op, "None") != 0)
            if(!isUsedLater(i)) 
                strcpy(tac[i].op, "None");
}

// Function to input TAC instructions from the user
void inputTAC() {
    int n;
    printf("Enter the number of instructions: ");
    scanf("%d", &n);
    
    getchar();

    for (int i = 0; i < n; i++) {
        printf("Enter instruction %d (operation arg1 arg2 result): ", i + 1);
        scanf("%s %s %s %s", tac[i].op, tac[i].arg1, tac[i].arg2, tac[i].result);
        tacIndex++;
    }
}

// Function to input predefined TAC instructions
void Input() {
    strcpy(tac[tacIndex].op, "+");
    strcpy(tac[tacIndex].arg1, "3");
    strcpy(tac[tacIndex].arg2, "4");
    strcpy(tac[tacIndex].result, "t1");
    tacIndex++;
    
    strcpy(tac[tacIndex].op, "+");
    strcpy(tac[tacIndex].arg1, "3");
    strcpy(tac[tacIndex].arg2, "4");
    strcpy(tac[tacIndex].result, "t6");
    tacIndex++;

    strcpy(tac[tacIndex].op, "-");
    strcpy(tac[tacIndex].arg1, "3");
    strcpy(tac[tacIndex].arg2, "t6");
    strcpy(tac[tacIndex].result, "t7");
    tacIndex++;

    strcpy(tac[tacIndex].op, "-");
    strcpy(tac[tacIndex].arg1, "5");
    strcpy(tac[tacIndex].arg2, "t6");
    strcpy(tac[tacIndex].result, "t2");
    tacIndex++;

    strcpy(tac[tacIndex].op, "*");
    strcpy(tac[tacIndex].arg1, "t6");
    strcpy(tac[tacIndex].arg2, "t2");
    strcpy(tac[tacIndex].result, "t3");
    tacIndex++;
    
    strcpy(tac[tacIndex].op, "=");
    strcpy(tac[tacIndex].arg1, "t3");
    strcpy(tac[tacIndex].arg2, "None");
    strcpy(tac[tacIndex].result, "t4");
    tacIndex++;
    
    strcpy(tac[tacIndex].op, "*");
    strcpy(tac[tacIndex].arg1, "t3");
    strcpy(tac[tacIndex].arg2, "t4");
    strcpy(tac[tacIndex].result, "t5");
    tacIndex++;
}

void Input2() {
    tacIndex = 0;

    strcpy(tac[tacIndex].op, "+");
    strcpy(tac[tacIndex].arg1, "3");
    strcpy(tac[tacIndex].arg2, "4");
    strcpy(tac[tacIndex].result, "t0");
    tacIndex++;

    strcpy(tac[tacIndex].op, "+");
    strcpy(tac[tacIndex].arg1, "a");
    strcpy(tac[tacIndex].arg2, "b");
    strcpy(tac[tacIndex].result, "t1");
    tacIndex++;

    strcpy(tac[tacIndex].op, "=");
    strcpy(tac[tacIndex].arg1, "t1");
    strcpy(tac[tacIndex].arg2, "None");
    strcpy(tac[tacIndex].result, "t2");
    tacIndex++;

    strcpy(tac[tacIndex].op, "+");
    strcpy(tac[tacIndex].arg1, "t2");
    strcpy(tac[tacIndex].arg2, "1");
    strcpy(tac[tacIndex].result, "t8");
    tacIndex++;

    strcpy(tac[tacIndex].op, "*");
    strcpy(tac[tacIndex].arg1, "t2");
    strcpy(tac[tacIndex].arg2, "c");
    strcpy(tac[tacIndex].result, "t3");
    tacIndex++;

    strcpy(tac[tacIndex].op, "+");
    strcpy(tac[tacIndex].arg1, "a");
    strcpy(tac[tacIndex].arg2, "b");
    strcpy(tac[tacIndex].result, "t4");
    tacIndex++;

    strcpy(tac[tacIndex].op, "-");
    strcpy(tac[tacIndex].arg1, "t4");
    strcpy(tac[tacIndex].arg2, "d");
    strcpy(tac[tacIndex].result, "t5");
    tacIndex++;

    strcpy(tac[tacIndex].op, "/");
    strcpy(tac[tacIndex].arg1, "t3");
    strcpy(tac[tacIndex].arg2, "t5");
    strcpy(tac[tacIndex].result, "t6");
    tacIndex++;
}

void Input3() {
    tacIndex = 0;

    strcpy(tac[tacIndex].op, "*");
    strcpy(tac[tacIndex].arg1, "2");
    strcpy(tac[tacIndex].arg2, "3");
    strcpy(tac[tacIndex].result, "t1");
    tacIndex++;

    strcpy(tac[tacIndex].op, "+");
    strcpy(tac[tacIndex].arg1, "t1");
    strcpy(tac[tacIndex].arg2, "4");
    strcpy(tac[tacIndex].result, "t2");
    tacIndex++;

    strcpy(tac[tacIndex].op, "-");
    strcpy(tac[tacIndex].arg1, "5");
    strcpy(tac[tacIndex].arg2, "1");
    strcpy(tac[tacIndex].result, "t3");
    tacIndex++;

    strcpy(tac[tacIndex].op, "/");
    strcpy(tac[tacIndex].arg1, "t2");
    strcpy(tac[tacIndex].arg2, "t3");
    strcpy(tac[tacIndex].result, "t4");
    tacIndex++;

    strcpy(tac[tacIndex].op, "*");
    strcpy(tac[tacIndex].arg1, "t4");
    strcpy(tac[tacIndex].arg2, "t4");
    strcpy(tac[tacIndex].result, "t5");
    tacIndex++;

    strcpy(tac[tacIndex].op, "=");
    strcpy(tac[tacIndex].arg1, "t5");
    strcpy(tac[tacIndex].arg2, "None");
    strcpy(tac[tacIndex].result, "t9");
    tacIndex++;

    strcpy(tac[tacIndex].op, "-");
    strcpy(tac[tacIndex].arg1, "t5");
    strcpy(tac[tacIndex].arg2, "t4");
    strcpy(tac[tacIndex].result, "t6");
    tacIndex++;

    strcpy(tac[tacIndex].op, "*");
    strcpy(tac[tacIndex].arg1, "2");
    strcpy(tac[tacIndex].arg2, "3");
    strcpy(tac[tacIndex].result, "t8");
    tacIndex++;

    strcpy(tac[tacIndex].op, "*");
    strcpy(tac[tacIndex].arg1, "t9");
    strcpy(tac[tacIndex].arg2, "2");
    strcpy(tac[tacIndex].result, "t7");
    tacIndex++;
}

void main() {
    // Uncomment the following line to input TAC instructions from the user
    // inputTAC();
    
    // Input predefined TAC instructions
    Input();

    // Print the initial TAC
    printf("Initial TAC:\n");
    printTAC();
    
    // Perform optimizations
    printf("\nOptimized TAC:\n");
    removeRedundant();
    removeCommonSubExpressions();
    constantFolding();
    removeDeadCode();
    
    // Print the optimized TAC
    printTAC();

    printf("\n\n\n");

    Input2();

    // Print the initial TAC
    printf("Initial TAC:\n");
    printTAC();
    
    // Perform optimizations
    printf("\nOptimized TAC:\n");
    removeRedundant();
    removeCommonSubExpressions();
    constantFolding();
    removeDeadCode();
    
    // Print the optimized TAC
    printTAC();
    
    printf("\n\n\n");
    Input3();

    // Print the initial TAC
    printf("Initial TAC:\n");
    printTAC();
    
    // Perform optimizations
    printf("\nOptimized TAC:\n");
    removeRedundant();
    removeCommonSubExpressions();
    constantFolding();
    removeDeadCode();
    
    // Print the optimized TAC
    printTAC();

}