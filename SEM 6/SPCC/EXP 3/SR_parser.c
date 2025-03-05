#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_RULES 50
#define MAX_SYMBOLS 20

// Structure to represent a production rule
typedef struct {
    char lhs; // Left-hand side of the production
    char rhs[MAX_SYMBOLS]; // Right-hand side of the production
} Production;

Production grammar[MAX_RULES];
int numProductions = 0;

char input[MAX];
int ip_ptr = 0, len;

typedef struct {
    char items[MAX];
    int top;
} Stack;

Stack stack;

// Function to initialize the stack
void initStack() {
    stack.top = -1;
    stack.items[0] = '\0';
}

// Function to check if the stack is empty
int isStackEmpty() {
    return stack.top == -1;
}

// Function to push a symbol onto the stack
void push(char symbol) {
    if (stack.top < MAX - 1) {
        stack.items[++stack.top] = symbol;
        stack.items[stack.top + 1] = '\0';
    } else {
        printf("Stack overflow\n");
    }
}

// Function to pop a symbol from the stack
char pop() {
    if (!isStackEmpty()) {
        char symbol = stack.items[stack.top--];
        stack.items[stack.top + 1] = '\0';
        return symbol;
    } else {
        printf("Stack underflow\n");
        return '\0';
    }
}

// Function to peek the top symbol of the stack
char peek() {
    if (!isStackEmpty()) {
        return stack.items[stack.top];
    } else {
        return '\0';
    }
}

// Function to check and reduce the stack using the grammar rules
int checkAndReduce(char *action) {
    for (int i = 0; i < numProductions; i++) {
        int lenRHS = strlen(grammar[i].rhs);
        if (stack.top + 1 >= lenRHS &&
            strncmp(stack.items + stack.top - lenRHS + 1, grammar[i].rhs, lenRHS) == 0) {
            stack.top -= lenRHS;
            push(grammar[i].lhs);
            sprintf(action, "Reduce using %c -> %s", grammar[i].lhs, grammar[i].rhs);
            return 1;
        }
    }
    return 0;
}

// Function to print the current state of the stack, input string, and action
void printState(const char *action) {
    printf("%-20s %-20s %-20s\n", stack.items, input + ip_ptr, action);
}

// Function to parse the input string using the grammar rules
void parse() {
    push('$');

    printf("%-20s %-20s %-20s\n", "Stack", "Input String", "Action");
    printf("------------------------------------------------------------\n");

    char action[MAX];
    while (input[ip_ptr] != '$') {
        if (!checkAndReduce(action)) {
            char symbol = input[ip_ptr++];
            push(symbol);
            sprintf(action, "Shift %c", symbol);
            printState(action);
        } else {
            printState(action);
        }
    }

    while (checkAndReduce(action)) {
        printState(action);
    }

    if (stack.top == 1 && stack.items[0] == '$' && stack.items[1] == grammar[0].lhs) {
        printf("\nInput string is accepted.\n");
    } else {
        printf("\nInput string is rejected.\n");
    }
}

// Function to load the grammar from a file
void loadGrammar(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening grammar file");
        return;
    }

    numProductions = 0;
    char line[MAX];
    while (fgets(line, MAX, file) && line[0] != '\n') {
        line[strcspn(line, "\n")] = 0;

        char *token = strtok(line, " ");
        grammar[numProductions].lhs = token[0];

        int i = 0;
        while ((token = strtok(NULL, " ")) != NULL) {
            if (strcmp(token, "|") == 0 || strcmp(token, "->") == 0) continue;
            else grammar[numProductions].rhs[i++] = token[0];
        }
        grammar[numProductions].rhs[i] = '\0';
        numProductions++;
    }
    fclose(file);
}

// Function to load the input string from a file
void loadInputString(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening input string file");
        return;
    }

    fscanf(file, "%s", input);
    len = strlen(input);
    input[len++] = '$';
    input[len] = '\0';

    fclose(file);
}

int main() {
    loadGrammar("Grammar.txt");
    loadInputString("String.txt");
    initStack();
    parse();
    return 0;
}