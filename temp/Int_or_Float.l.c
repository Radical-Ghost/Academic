%{
#include <stdio.h>
#include <stdlib.h>
%}

digit [0-9]

%%
{digit}+                  {printf("\nInteger recognized!");}
{digit}+"\\."{digit}+     {printf("\nFloating point number recognized!");}
.                         {printf("\nEntered input is neither int nor float!");}
%%

int yywrap() {
    return 1;
}

int main() {
    printf("\nEnter input to recognize integer or floating point number: ");
    yylex();
    return 0;
}