#include <stdio.h>
#include <string.h>
#include <ctype.h>

void countWords() {
    char sentence[1000];
    int i, wordCount = 0;

    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    
    sentence[strcspn(sentence, "\n")] = '\0';
    char *token = strtok(sentence, " \n\t");
    while (token != NULL) {
        wordCount++;
        token = strtok(NULL, " \n\t");
    }
    printf("Number of words in sentence is : %d", wordCount);
}

void countCharacters() {
    int count = 0, freq[26] = {0};
    char word[100];

    printf("Enter a word: ");
    scanf("%s", word);

    for (int i = 0; word[i]; i++) {
        count++;
        if (isalpha(word[i])) {
            freq[tolower(word[i]) - 'a']++;
        }
    }

    printf("Number of characters in the word: %d\n", count);
    printf("Letter frequencies:\n");
    for (int i = 0; i < 26; i++) if (freq[i] > 0) printf("%c: %d\n", i + 'a', freq[i]);
}

int main() {
    int choice;
    printf("1. Count words in a sentence\n2. Count characters in a word\nEnter choice: ");
    scanf("%d", &choice);
    getchar();
    if (choice == 1) countWords();
    else if (choice == 2) countCharacters();
    else printf("Invalid choice\n");
    return 0;
}