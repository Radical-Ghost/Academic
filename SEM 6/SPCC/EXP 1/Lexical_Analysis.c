#include <stdio.h>
#include <string.h>
#include <ctype.h>

// List of keywords
char *kw[] = {"int", "float", "if", "else", "while", "for", "return"};

// Function to check if a word is a keyword
int is_kw(char *w) {
    for (int i = 0; i < 7; i++) {
        if (strcmp(w, kw[i]) == 0) return 1;
    }
    return 0;
}

// Function to analyze the contents of a file
void analyze(const char *fn) {
    FILE *f = NULL;
    char ch = '\0', w[20] = {0};
    int i = 0;

    // Open the file for reading
    f = fopen(fn, "r");
    if (!f) {
        printf("Error: File not found!\n");
        return;
    }

    // Read the file character by character
    while ((ch = fgetc(f)) != EOF) {
        if (isalnum(ch)) {
            // If the character is alphanumeric, add it to the current word
            w[i++] = ch;
        } else {
            // Null-terminate the current word and reset the index
            w[i] = '\0';
            i = 0;

            // If the word is not empty, check if it is a keyword or identifier
            if (strlen(w) > 0) {
                if (is_kw(w)) {
                    printf("Keyword: %s\n", w);
                } else {
                    printf("Identifier: %s\n", w);
                }
            }

            // If the character is an operator, print it
            if (strchr("+-*/=<>", ch)) {
                printf("Operator: %c\n", ch);
            }
        }
    }

    // Close the file
    fclose(f);
}

int main() {
    char fn[50] = {0};

    // Prompt the user to enter the filename
    printf("Enter filename: ");
    scanf("%s", fn);

    // Analyze the contents of the file
    analyze(fn);

    return 0;
}