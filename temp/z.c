// #include <stdio.h>
// #include <string.h>

// typedef struct {
//     char opcode[10];
//     char add[5];
// } Opcode;

// typedef struct {
//     char symbol[10];
//     int add;
// } Symbol;

// Symbol symtab[100];
// int symptr = 0;

// Opcode optab[] = {
//     {"LOAD", "01"},
//     {"STORE", "02"},
//     {"ADD", "03"},
//     {"SUB", "04"},
//     {"MUL", "05"},
//     {"DIV", "06"},
//     {"JMP", "07"},
//     {"HALT", "08"},
//     {"MOV", "09"}
// };

// int search_symtab(char *op) {
//     for (int i = 0; i < symptr; i++)
//         if (strcmp(symtab[i].symbol, op) == 0)
//             return symtab[i].add;
//     return -1;
// }

// void add_symtab(char *op, int var_add) {
//     strcpy(symtab[symptr].symbol, op);
//     symtab[symptr].add = var_add;
//     symptr++;
// }

// int get_symbol_address(char *op, int *var_add) {
//     int add = search_symtab(op);
//     if (add == -1){
//         add_symtab(op, *var_add);
//         add = *var_add;
//         (*var_add)++;
//     }
//     return add;
// }

// char* get_opcode(char *opcode) {
//     for (int i = 0; i < 10; i++)
//         if (strcmp(optab[i].opcode, opcode) == 0)
//             return optab[i].add;
//     return NULL;
// }

// int main() {
//     FILE *f = fopen("input.asm", "r");
//     char line[100], label[10], opcode[10], op1[10], op2[10];
//     int loc=0, var_add=50;

//     printf("Machine Code: \n");
//     while(fgets(line, sizeof(line),f)) {
//         label[0] = opcode[0] = op1[0] = op2[0] = '\0';

//         int n = sscanf(line, "%[^:]: %s %[^,], %s", label, opcode, op1, op2);
//         if (n < 2) {
//             label[0] = '\0';
//             sscanf(line, "%s %[^,], %s", opcode, op1, op2);
//         }

//         char *code = get_opcode(opcode);
//         if (code) {
//             int add1 = 0, add2 = 0;
//             if (op1[0]) add1 = get_symbol_address(op1, &var_add);
//             if (op2[0]) add2 = get_symbol_address(op2, &var_add);
            
//             if (op2[0]) printf("%02d %s %02d %02d\n", loc, code, add1, add2);
//             else printf("%02d %s %02d\n", loc, code, add1);
//             loc++;
//         }
//     }

//     fclose(f);
//     return 0;
// }


// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>

// char *kw[] = {"int", "float", "if", "else", "while", "for", "return"};

// int is_kw(char *w) {
//     for (int i = 0; i < 7; i++)
//         if (strcmp(w, kw[i]) == 0)
//             return 1;
//     return 0;
// }

// int main() {
//     FILE *f = fopen("input.txt", "r");
//     int i, j;
//     char line[100], word[100];

//     while (fgets(line, sizeof(line), f)) {
//         i = 0;
//         while (line[i]) {
//             if (isalnum(line[i]) || line[i] == '_') {
//                 j = 0;
//                 while (isalnum(line[i]) || line[i] == '_') 
//                     word[j++] = line[i++];
//                 word[j] = '\0';
//                 if (is_kw(word)) printf("Keyword: %s\n", word);
//                 else printf("Identifier: %s\n", word);
//             }
//             else if (strchr("+-*/=<>", line[i])) printf("Operator: %c\n", line[i++]); 
//             else i++;
//         }
//     }
//     fclose(f);
//     return 0;
// }

// #include <stdio.h>
// #include <ctype.h>
// #include <string.h>

// void word_count() {
//     char line[1000];
//     int i, wordCount = 0;
//     printf("Enter a line: ");
//     fgets(line, sizeof(line), stdin);
//     for (i = 0; line[i]; i++)
//         if((i==0 && !isspace(line[i])) || (isspace(line[i-1]) && !isspace(line[i])))
//             wordCount++;
//     printf("The number of words are: %d", wordCount);
// }

// void char_count() {
//     char word[100];
//     printf("Enter a word: ");
//     scanf("%s", word);
//     printf("The number of character in %s are: %d", word ,(int)strlen(word));
// }

// int main() {
//     int c;
//     printf("1. Count words in a sentence\n2. Count characters in a word\nChoice: ");
//     scanf("%d", &c);
//     getchar();
//     if (c == 1) word_count();
//     else if (c == 2) char_count();
//     else printf("Enter Valid number.");
//     return 0;
// }

// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>

// typedef struct {
//     char A;
//     char alpha[100][10];
//     char beta[100][10];
//     int alphaCount;
//     int betaCount;
// } Production;

// Production productions[10];
// int prodCount = 0;

// void loadGrammar() {
//     FILE *f = fopen("example.txt", "r");
//     char line[100];
//     while (fgets(line, sizeof(line), f)) {
//         if (line[0] == "\n" || line[0] == "\0") continue;
//         Production *e = &productions[prodCount++];
//         char *token = strtok(line, " \n");
//         if (!token) continue;
//         e->A = token[0];
//         e->alphaCount = e->betaCount = 0;
//         while ((token = strtok(NULL, " \n")) != NULL) {
//             if (!strcmp(token, "|") || !strcmp(token, "->")) continue;
//             else if (token[0] == e->A) strcpy(e->alpha[e->alphaCount++], token+1); 
//             else strcpy(e->beta[e->betaCount++], token);
//         } 
//     }
//     fclose(f);
// }

// void printGrammar() {
//     for (int i = 0; i < prodCount; i++) {
//         Production *e = &productions[i];
//         if (e->alphaCount == 0) {
//             printf("No left recursion present for %c\n", e->A);
//             printf("%c -> ", e->A);
//             for (int j = 0; j < e->betaCount - 1; j++)
//                 printf("%s | ", e->beta[j]);
//             printf("%s\n", e->beta[e->betaCount -1]);
//             continue;
//         }

//         printf("Left recursion removal for %c\n", e->A);
//         printf("%c -> ", e->A);
//         for (int j = 0; j < e->betaCount - 1; j++)
//             printf("%s%c' | ", e->beta[j], e->A);
//         printf("%s%c'\n", e->beta[e->betaCount -1], e->A);
//         printf("%c' -> ", e->A);
//         for (int j = 0; j < e->alphaCount; j++)
//             printf("%s%c' | ", e->alpha[j], e->A);
//         printf("epsilon\n");
//         continue;
//     }
// }

// int main() {
//     loadGrammar();
//     printGrammar();
//     return 0;
// }

