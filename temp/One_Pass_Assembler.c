#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char label[20];
    int address;
} Symbol;

Symbol symtab[MAX];
int symcount = 0;

typedef struct {
    char opcode[10];
    char code[5];
} Opcode;

Opcode optab[] = {
    {"LOAD", "01"},
    {"STORE", "02"},
    {"ADD", "03"},
    {"SUB", "04"},
    {"MUL", "05"},
    {"DIV", "06"},
    {"JMP", "07"},
    {"HALT", "08"},
    {"MOV", "09"}
};

int search_symtab(char *label) {
    for (int i = 0; i < symcount; i++)
        if (strcmp(symtab[i].label, label) == 0)
            return symtab[i].address;
    return -1;
}

void add_symtab(char *label, int addr) {
    strcpy(symtab[symcount].label, label);
    symtab[symcount].address = addr;
    symcount++;
}
char* get_opcode(char *mnemonic) {
    for (int i = 0; i < sizeof(optab)/sizeof(optab[0]); i++)
        if (strcmp(optab[i].opcode, mnemonic) == 0)
            return optab[i].code;
    return NULL;
}

int get_or_add_var(char *var, int *var_addr) {
    int addr = search_symtab(var);
    if (addr == -1) {
        add_symtab(var, *var_addr);
        addr = *var_addr;
        (*var_addr)++;
    }
    return addr;
}

int main() {
    FILE *f = fopen("input.asm", "r");
    char line[100], label[20], opcode[10], op1[20], op2[20];
    int loc = 0, var_addr = 50;

    if (!f) {
        printf("Input file not found!\n");
        return 1;
    }

    printf("Machine Code:\n");
    while (fgets(line, sizeof(line), f)) {
        label[0] = opcode[0] = op1[0] = op2[0] = '\0';

        int n = sscanf(line, "%[^:]: %s %[^,], %s", label, opcode, op1, op2);
        if (n < 2) {
            label[0] = '\0';
            n = sscanf(line, "%s %[^,], %s", opcode, op1, op2);
        }

        char *code = get_opcode(opcode);
        if (code) {
            int addr1 = 0, addr2 = 0;
            if (op1[0])
                addr1 = get_or_add_var(op1, &var_addr);
            if (op2[0])
                addr2 = get_or_add_var(op2, &var_addr);

            // Print both operands if present
            if (op2[0])
                printf("%02d %s %02d %02d\n", loc, code, addr1, addr2);
            else
                printf("%02d %s %02d\n", loc, code, addr1);
            loc++;
        }
    }

    fclose(f);
    return 0;
}