#include<stdio.h>
#include "defForLexer.h"
#include "lexer.h"


int main(int argc, char *argv[])
{
    FILE *sourceCode;
    if(argc < 2)
    {
        printf("insufficient command line arguments");
    }
    else{
        printf("analysing file : %s\n" , argv[1]);
        sourceCode =fopen(argv[1],"r");
        initializeLexer(sourceCode);
        tokenizeSource();
        fclose(sourceCode);
    }
    return 0;
}