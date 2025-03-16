#include <bits/stdc++.h>
using namespace std;

#define MAX_INSTRUCTIONS 100
int n;

struct Instruction {
    string op;
    string arg1;
    string arg2;
    string result;
};

vector<Instruction> tac;

void ASM_Generator() {
    cout << "\nASM Code: " << endl;
    int reg_count = 1;
    
    for(int i = 0; i < n; i++){
        if(tac[i].op == "=") {
            cout << tac[i].result << " = " << tac[i].arg1 << endl;
            cout << "MOV " << tac[i].result << ", " << tac[i].arg1 << "\n" << endl;
        }   
        else {
            cout << tac[i].result << " = " << tac[i].arg1 << " " << tac[i].op << " " << tac[i].arg2 << endl;
            cout << "MOV R" << reg_count << ", " << tac[i].arg1 << endl;

            if(tac[i].op == "+") cout << "ADD R" << reg_count << ", " << tac[i].arg2 << endl;
            else if(tac[i].op == "-") cout << "SUB R" << reg_count << ", " << tac[i].arg2 << endl;
            else if(tac[i].op == "*") cout << "MUL R" << reg_count << ", " << tac[i].arg2 << endl;
            else if(tac[i].op == "/") cout << "DIV R" << reg_count << ", " << tac[i].arg2 << endl;
            else if(tac[i].op == "&&") cout << "AND R" << reg_count << ", " << tac[i].arg2 << endl;
            else if(tac[i].op == "||") cout << "OR R" << reg_count << ", " << tac[i].arg2 << endl;
            else if(tac[i].op == "!") cout << "NOT R" << reg_count << endl;
            else if(tac[i].op == "^") cout << "XOR R" << reg_count << ", " << tac[i].arg2 << endl;
            else if(tac[i].op == "<<") cout << "SHL R" << reg_count << ", " << tac[i].arg2 << endl;
            else if(tac[i].op == ">>") cout << "SHR R" << reg_count << ", " << tac[i].arg2 << endl;

            cout << "MOV " << tac[i].result << ", R" << reg_count << "\n" << endl;
            reg_count++;
        }
    }
}

void inputTAC() {
    cout << "Enter the number of instructions: ";
    cin >> n;
    cin.ignore();

    tac.resize(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter instruction " << i + 1 << " (operation arg1 arg2 result) {add None for blank}: ";
        string line;
        getline(cin, line);
        istringstream iss(line);
        iss >> tac[i].op >> tac[i].arg1 >> tac[i].arg2 >> tac[i].result;
    }
}

int main() {
    inputTAC();
    ASM_Generator();
    return 0;
}