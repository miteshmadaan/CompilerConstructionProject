#include<stdio.h>
#include "defForLexer.h"
#include "lexer.h"


int main()
{
    FILE *sourceCode;
    sourceCode =fopen("sourceCode.txt","r");
    intializeLexer(sourceCode);
    fclose(sourceCode);
    return 0;
}