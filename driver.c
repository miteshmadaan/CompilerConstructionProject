#include<stdio.h>
#include "defForLexer.h"
#include "lexer.h"

void removeComments(FILE *inputFile)
{
    char ch = '\n';
    int comment = 0;
    while(ch != EOF)
    {
        if(ch == '%')
        {
            comment = 1;
        }
        else if (ch == '\n')
        {
            comment = 0;
        }
        if(comment==0)
        {
            printf("%c" , ch);
        }
        ch = fgetc(inputFile);
    }
    printf("\n");
}

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
        //removeComments(sourceCode);
        fclose(sourceCode);
    }
    return 0;
}