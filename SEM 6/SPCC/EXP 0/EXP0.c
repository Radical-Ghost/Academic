#include <stdio.h>
#include <string.h>
#include <ctype.h>

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int find_word(const char *text, const char *word) {
    char lower_text[1000];
    char lower_word[100];

    strcpy(lower_text, text);
    strcpy(lower_word, word);

    to_lowercase(lower_text);
    to_lowercase(lower_word);

    int text_len = strlen(lower_text);
    int word_len = strlen(lower_word);

    for (int i = 0; i <= text_len - word_len; i++) {
        int j;
        for (j = 0; j < word_len; j++) {
            if (lower_text[i + j] != lower_word[j]) {
                break;
            }
        }
        if (j == word_len) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char text[1000];
    char word[100];

    printf("Enter a searchable Text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter a character to search: ");
    scanf("%s", word);

    if (find_word(text, word)) {
        printf("The word '%s' is found in the paragraph.\n", word);
    } else {
        printf("The word '%s' is not found in the paragraph.\n", word);
    }

    return 0;
}
