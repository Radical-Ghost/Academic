#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *kw[] = {"int", "float", "if", "else", "while", "for", "return"};

int is_kw(char *w) {
    for (int i = 0; i < 7; i++)
        if (strcmp(w, kw[i]) == 0) return 1;
    return 0;
}

void analyze(const char *fn) {
    FILE *f = fopen(fn, "r");
    char line[256], word[64];
    int i, j;
    if (!f) {
        printf("Error: File not found!\n");
        return;
    }
    while (fgets(line, sizeof(line), f)) {
        i = 0;
        while (line[i]) {
            if (isalnum(line[i]) || line[i] == '_') {
                j = 0;
                while (isalnum(line[i]) || line[i] == '_')
                    word[j++] = line[i++];
                word[j] = '\0';
                if (is_kw(word))
                    printf("Keyword: %s\n", word);
                else
                    printf("Identifier: %s\n", word);
            } else if (strchr("+-*/=<>", line[i])) {
                printf("Operator: %c\n", line[i]);
                i++;
            } else {
                i++;
            }
        }
    }
    fclose(f);
}

int main() {
    analyze("input.txt");
    return 0;
}