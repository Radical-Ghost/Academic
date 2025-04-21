%{
#include <stdio.h>
#include <stdlib.h>
%}

letter [a-zA-Z]
digit [0-9]

%%
{letter}({letter}|{digit})* {printf("\nIdentifier recognized!");}
.                           {printf("\nEntered input is not an identifier!");}
%%

int yywrap() {
    return 1;
}

int main() {
    printf("\nEnter input to determine whether it is an identifier or not: ");
    yylex();
    return 0;
}