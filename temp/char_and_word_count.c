#include <stdio.h>
#include <string.h>
#include <ctype.h>

void countWords() {
    char sentence[1000];
    int i, wordCount = 0;
    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    for(i = 0; sentence[i]; i++)
        if((i == 0 && !isspace(sentence[i])) || (isspace(sentence[i-1]) && !isspace(sentence[i])))
            wordCount++;
    printf("Total number of words: %d\n", wordCount);
}

void countCharacters() {
    char word[100];
    printf("Enter a word: ");
    scanf("%s", word);
    printf("Number of characters in the word: %d\n", (int)strlen(word));
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