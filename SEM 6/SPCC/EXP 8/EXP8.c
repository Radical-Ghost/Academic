#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MACROS 100
#define MAX_CODE_LINES 100
#define MAX_LINE_LENGTH 200

typedef struct {
    char name[50];
    char body[MAX_CODE_LINES][MAX_LINE_LENGTH];
    int num_lines;
} Macro;

Macro macros[MAX_MACROS];
int num_macros = 0;
char macro_calls[MAX_CODE_LINES][MAX_LINE_LENGTH];
int num_calls = 0;

void trim(char* str) {
    int start = 0, end = strlen(str) - 1;
    while (str[start] == ' ' || str[start] == '\t') start++;
    while (end > start && (str[end] == ' ' || str[end] == '\t')) end--;
    memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
}

void pass_one(char source_code[MAX_CODE_LINES][MAX_LINE_LENGTH], int num_lines) {
    int in_macro = 0, current_macro_line = 0;
    char current_macro_name[50];

    for (int i = 0; i < num_lines; i++) {
        char line[MAX_LINE_LENGTH];
        strcpy(line, source_code[i]);
        trim(line);

        if (strncmp(line, "MACRO", 5) == 0) {
            in_macro = 1;
            sscanf(line, "MACRO %s", current_macro_name);
            strcpy(macros[num_macros].name, current_macro_name);
            current_macro_line = 0;
        } else if (strncmp(line, "MEND", 4) == 0) {
            in_macro = 0;
            macros[num_macros].num_lines = current_macro_line;
            num_macros++;
        } else if (in_macro) {
            strcpy(macros[num_macros].body[current_macro_line], line);
            current_macro_line++;
        } else {
            strcpy(macro_calls[num_calls], line);
            num_calls++;
        }
    }
}

void replace_params(char* line, char params[][50], int num_params) {
    char temp[MAX_LINE_LENGTH];
    strcpy(temp, line);

    for (int p = 0; p < num_params; p++) {
        char param_placeholder[10];
        sprintf(param_placeholder, "$%d", p + 1);
        char* pos;
        while ((pos = strstr(temp, param_placeholder)) != NULL) {
            char before[MAX_LINE_LENGTH], after[MAX_LINE_LENGTH];
            strncpy(before, temp, pos - temp);
            before[pos - temp] = '\0';
            strcpy(after, pos + strlen(param_placeholder));
            snprintf(temp, sizeof(temp), "%s%s%s", before, params[p], after);
        }
    }
    strcpy(line, temp);
}

void pass_two() {
    for (int i = 0; i < num_calls; i++) {
        char call[MAX_LINE_LENGTH], macro_name[50], params[2][50];
        int num_params = 0;

        strcpy(call, macro_calls[i]);
        trim(call);

        char *token = strtok(call, " ,");
        if (token) {
            strcpy(macro_name, token);
            while ((token = strtok(NULL, " ,")) && num_params < 2) {
                strcpy(params[num_params], token);
                num_params++;
            }
        }

        for (int j = 0; j < num_macros; j++) {
            if (strcmp(macros[j].name, macro_name) == 0) {
                for (int k = 0; k < macros[j].num_lines; k++) {
                    char expanded_line[MAX_LINE_LENGTH];
                    strcpy(expanded_line, macros[j].body[k]);
                    replace_params(expanded_line, params, num_params);
                    printf("%s\n", expanded_line);
                }
                break;
            }
        }
    }
}

int main() {
    char filename[100], source_code[MAX_CODE_LINES][MAX_LINE_LENGTH];
    int num_lines = 0;

    printf("Enter the name of the source code file: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    while (fgets(source_code[num_lines], MAX_LINE_LENGTH, file) && num_lines < MAX_CODE_LINES) {
        source_code[num_lines][strcspn(source_code[num_lines], "\n")] = '\0';
        num_lines++;
    }
    fclose(file);

    // Print the unexpanded code
    printf("\nUnexpanded Code:\n");
    for (int i = 0; i < num_lines; i++) {
        printf("%s\n", source_code[i]);
    }

    // Perform macro processing
    pass_one(source_code, num_lines);

    // Print expanded code
    printf("\nExpanded Code:\n");
    pass_two();

    return 0;
}
