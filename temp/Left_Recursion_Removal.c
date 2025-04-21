#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAX_RULES 10

typedef struct {
    char A;
    char alpha[MAX][MAX];
    char beta[MAX][MAX];
    int alphaCount;
    int betaCount;
} Production;

Production productions[MAX_RULES];
int productionCount = 0;

void getInput() {
    char line[MAX];
    FILE *f = fopen("example.txt", "r");

    while (fgets(line, MAX, f)) {
        if (line[0] == '\n' || line[0] == '\0') continue;
        Production *e = &productions[productionCount++];
        char *token = strtok(line, " \n");
        if (!token) continue;
        e->A = token[0];
        e->alphaCount = e->betaCount = 0;
        while ((token = strtok(NULL, " \n")) != NULL) {
            if (!strcmp(token, "|") || !strcmp(token, "->")) continue;
            else if (token[0] == e->A) strcpy(e->alpha[e->alphaCount++], token + 1);
            else strcpy(e->beta[e->betaCount++], token);
        }
    }

    fclose(f);
}

void showOutput() {
    for (int j = 0; j < productionCount; j++) {
        Production *e = &productions[j];
        if (e->alphaCount == 0) {
            printf("\nProduction doesnt have Left Recursion\n");
            printf("%c -> ", e->A);
            for (int i = 0; i < e->betaCount - 1; i++)
                printf("%s | ", e->beta[i]);
            printf("%s\n", e->beta[e->betaCount - 1]);
            continue;
        }
        printf("\nProduction without Left Recursion for %c:\n", e->A);
        printf("%c -> ", e->A);
        for (int i = 0; i < e->betaCount - 1; i++)
            printf("%s%c' | ", e->beta[i], e->A);
        printf("%s%c'\n", e->beta[e->betaCount - 1], e->A);
        printf("%c' -> ", e->A);
        for (int i = 0; i < e->alphaCount; i++)
            printf("%s%c' | ", e->alpha[i], e->A);
        printf("epsilon\n");
    }
}

int main() {
    getInput();
    showOutput();
    return 0;
}