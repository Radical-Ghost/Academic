#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAX_RULES 10

// Structure to represent a production rule
typedef struct {
    char A; // Non-terminal
    char alpha[MAX][MAX]; // Productions with left recursion
    char beta[MAX][MAX]; // Productions without left recursion
    int alphaCount; // Count of alpha productions
    int betaCount; // Count of beta productions
} Production;

// Function to get input from a file
void getInput(Production productions[], int *productionCount, const char *filename) {
    char line[MAX];
    *productionCount = 0;

    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Read each line from the file
    while (fgets(line, MAX, file) && line[0] != '\n') {
        Production *e = &productions[(*productionCount)++];
        char *token = strtok(line, " ");
        e->A = token[0];
        e->alphaCount = 0;
        e->betaCount = 0;

        // Tokenize the line to separate productions
        while ((token = strtok(NULL, " ")) != NULL) {
            if (strcmp(token, "|") == 0 || strcmp(token, "->") == 0) continue;
            else if (token[0] == e->A) strcpy(e->alpha[e->alphaCount++], token + 1);
            else strcpy(e->beta[e->betaCount++], token);
        }
    }

    // Close the file
    fclose(file);
}

// Function to show the output after removing left recursion
void showOutput(Production productions[], int productionCount) {
    for (int j = 0; j < productionCount; j++) {
        Production *e = &productions[j];
        if (e->alphaCount == 0) {
            // No left recursion detected
            printf("\nNo left recursion detected for %c. No need to remove left recursion.\n", e->A);
            printf("%c -> ", e->A);
            for (int i = 0; i < e->betaCount - 1; i++)
                printf("%s | ", e->beta[i]);
            printf("%s\n", e->beta[e->betaCount - 1]);
            continue;
        }

        // Left recursion detected, show the modified productions
        printf("\nProduction without Left Recursion for %c:\n", e->A);
        int i;

        printf("%c -> ", e->A);
        for (i = 0; i < e->betaCount - 1; i++)
            printf("%s%c' | ", e->beta[i], e->A);
        printf("%s%c'\n", e->beta[i], e->A);

        printf("%c' -> ", e->A);
        for (i = 0; i < e->alphaCount; i++)
            printf("%s%c' | ", e->alpha[i], e->A);
        printf("epsilon\n");
    }
}

int main() {
    Production productions[MAX_RULES];
    int productionCount;

    char filename[MAX];
    printf("Enter the filename: ");
    fgets(filename, MAX, stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove the newline character

    // Get input from the file and show the output
    getInput(productions, &productionCount, filename);
    showOutput(productions, productionCount);

    return 0;
}