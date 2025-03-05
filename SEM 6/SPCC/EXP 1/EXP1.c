#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *kw[] = {"int", "float", "if", "else", "while", "for", "return"};

int is_kw(char *w) {
    for (int i = 0; i < 7; i++) {
        if (strcmp(w, kw[i]) == 0) return 1;
    }
    return 0;
}

void analyze(const char *fn) {
    FILE *f = NULL;
    char ch = '\0', w[20] = {0};
    int i = 0;

    f = fopen(fn, "r");
    if (!f) {
        printf("Error: File not found!\n");
        return;
    }

    while ((ch = fgetc(f)) != EOF) {
        if (isalnum(ch)) {
            w[i++] = ch;
        } else {
            w[i] = '\0';
            i = 0;

            if (strlen(w) > 0) {
                if (is_kw(w)) {
                    printf("Keyword: %s\n", w);
                } else {
                    printf("Identifier: %s\n", w);
                }
            }

            if (strchr("+-*/=<>", ch)) {
                printf("Operator: %c\n", ch);
            }
        }
    }

    fclose(f);
}

int main() {
    char fn[50] = {0};

    printf("Enter filename: ");
    scanf("%s", fn);

    analyze(fn);

    return 0;
}