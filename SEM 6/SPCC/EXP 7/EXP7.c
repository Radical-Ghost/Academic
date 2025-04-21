#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LABELS 100
#define MAX_INSTRUCTIONS 100
#define LINE_LENGTH 50

typedef struct {
    char label[10];
    int address;
} Symbol;

Symbol symbolTable[MAX_LABELS];
int symbolCount = 0;
char instructions[MAX_INSTRUCTIONS][LINE_LENGTH];
int instructionCount = 0; // Track total instructions

typedef struct {
    char mnemonic[10];
    char opcode[10];
} Opcode;

Opcode opcodes[] = {
    {"MOV", "01"},
    {"ADD", "02"},
    {"SUB", "03"},
    {"JMP", "04"},
    {"HLT", "FF"}
};

int findOpcode(char *mnemonic) {
    for (int i = 0; i < sizeof(opcodes) / sizeof(Opcode); i++) {
        if (strcmp(opcodes[i].mnemonic, mnemonic) == 0) {
            return i;
        }
    }
    return -1;
}

void addSymbol(char *label, int address) {
    for (int i = 0; i < symbolCount; i++) { 
        if (strcmp(symbolTable[i].label, label) == 0) {
            symbolTable[i].address = address; // Update if found
            return;
        }
    }
    strcpy(symbolTable[symbolCount].label, label);
    symbolTable[symbolCount].address = address;
    symbolCount++;
}

int getSymbolAddress(char *label) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].label, label) == 0) {
            return symbolTable[i].address;
        }
    }
    return -1;
}

void passOne(FILE *source) {
    char line[LINE_LENGTH], label[10], mnemonic[10], operand[10];
    int address = 0;

    while (fgets(line, sizeof(line), source)) {
        int numTokens = sscanf(line, "%s %s %s", label, mnemonic, operand);

        if (numTokens == 3) {
            if (findOpcode(label) == -1) { // It's a label
                addSymbol(label, address);
                strcpy(instructions[address], mnemonic);
                strcat(instructions[address], " ");
                strcat(instructions[address], operand);
            } else { // No label, only instruction and operand
                strcpy(instructions[address], label);
                strcat(instructions[address], " ");
                strcat(instructions[address], mnemonic);
                addSymbol(mnemonic, -1); // Assume operand is a symbol
            }
        } else if (numTokens == 2) {
            strcpy(instructions[address], label);
            strcat(instructions[address], " ");
            strcat(instructions[address], mnemonic);
            addSymbol(mnemonic, -1); // Assume operand is a symbol
        } else if (numTokens == 1) {
            strcpy(instructions[address], label);
        }
        address++;
        instructionCount++;
    }

    // Resolve labels with unknown (-1) addresses
    for (int i = 0; i < symbolCount; i++) {
        if (symbolTable[i].address == -1) {
            symbolTable[i].address = getSymbolAddress(symbolTable[i].label);
        }
    }
}

void passTwo() {
    printf("\nGenerated Machine Code:\n");
    for (int i = 0; i < instructionCount; i++) {
        char mnemonic[10], operand[10];
        int opcodeIndex, address = -1;

        int numTokens = sscanf(instructions[i], "%s %s", mnemonic, operand);

        if (numTokens >= 1) {
            opcodeIndex = findOpcode(mnemonic);
            if (numTokens == 2) {
                address = getSymbolAddress(operand);
                if (address == -1 && isdigit(operand[0])) { // If operand is a number
                    address = atoi(operand);
                }
            } else {
                address = 0; // Default for instructions like HLT
            }
        }

        if (opcodeIndex != -1) {
            printf("%02d %s %02d\n", i, opcodes[opcodeIndex].opcode, address);
        }
    }
}

int main() {
    char filename[50];
    printf("Enter the filename containing assembly code: ");
    scanf("%s", filename);

    FILE *source = fopen(filename, "r");
    if (!source) {
        printf("Error opening file: %s\n", filename);
        return 1;
    }

    passOne(source);
    fclose(source);

    passTwo();

    return 0;
}
