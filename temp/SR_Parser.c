#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_RULES 50

typedef struct {
    char items[MAX];
    int top;
} Stack;

Stack stack;
typedef struct {
    char lhs;
    char rhs[MAX];
} Production;

Production grammar[MAX_RULES];
int numProductions = 0;
char input[MAX], action[100];
int ip_ptr = 0, len;

void initStack() { stack.top = -1; stack.items[0] = '\0'; }
void push(char symbol) { stack.items[++stack.top] = symbol; stack.items[stack.top + 1] = '\0'; }

int checkAndReduce() {
    for (int i = 0; i < numProductions; i++) {
        int lenRHS = strlen(grammar[i].rhs);
        if (stack.top + 1 >= lenRHS &&
            strncmp(stack.items + stack.top - lenRHS + 1, grammar[i].rhs, lenRHS) == 0) {
            stack.top -= lenRHS;
            push(grammar[i].lhs);
            sprintf(action, "Reduce: %c->%s", grammar[i].lhs, grammar[i].rhs);
            return 1;
        }
    }
    return 0;
}

void printState() {
    printf("%-20s %-20s %-20s\n", stack.items, input + ip_ptr, action);
}

void parse() {
    push('$');
    printf("%-20s %-20s %-20s\n", "Stack", "Input", "Action");
    printf("------------------------------------------------------------\n");
    while (input[ip_ptr] != '$') {
        if (!checkAndReduce()) {
            char symbol = input[ip_ptr++];
            push(symbol);
            sprintf(action, "Shift %c", symbol);
            printState();
        } else {
            printState();
        }
    }
    while (checkAndReduce()) printState();
    if (stack.top == 1 && stack.items[0] == '$' && stack.items[1] == grammar[0].lhs)
        printf("\nAccepted.\n");
    else
        printf("\nRejected.\n");
}

void loadGrammar() {
    FILE *file = fopen("Grammar.txt", "r");
    if (!file) return;
    numProductions = 0;
    char line[MAX];

    while (fgets(line, MAX, file) && line[0] != '\n') {
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, " ");
        grammar[numProductions].lhs = token[0];
        int i = 0;
        while ((token = strtok(NULL, " ")) != NULL) {
            if (!strcmp(token, "|") || !strcmp(token, "->")) continue;
            grammar[numProductions].rhs[i++] = token[0];
        }
        grammar[numProductions++].rhs[i] = '\0';
    }
    fclose(file);
}

void loadInputString() {
    FILE *file = fopen("String.txt", "r");
    if (!file) return;
    fscanf(file, "%s", input);
    len = strlen(input);
    input[len++] = '$';
    input[len] = '\0';
    fclose(file);
}

int main() {
    loadGrammar();
    loadInputString();
    initStack();
    parse();
    return 0;
}