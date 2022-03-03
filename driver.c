#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "lexer.h"
#include "parser.h"

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
    Grm grammar;
    grammar = (NTERMINAL*)malloc(sizeof(NTERMINAL) * NUM_NTERMINALS);
    getGram("grammar.txt", grammar);
    FirstSet firstSet=(FirstSet)malloc(NUM_NTERMINALS*sizeof(FIRST));
    FollowSet followSet=(FollowSet)malloc(NUM_NTERMINALS*sizeof(FIRST));
    buildFirstSet(grammar,firstSet);
    getFollowSets(grammar, followSet,firstSet);
    parseTable t;
    parseTree root=malloc(sizeof(treeNode)),ast=NULL;
    int error = 0;
    createParseTable(firstSet,followSet,grammar,t);

    if(argc < 2)
    {
        printf("insufficient command line arguments");
    }
    else{
        char option = '5';
        while(option != '0')
        {
            printf("Choose your option\n");
            scanf("%c" , &option);
            if(option =='\n')
            {
                scanf("%c" , &option);
            }
            printf("your option is %c\n" , option);
            if(option == '1')
            {
                sourceCode =fopen(argv[1],"r");
                removeComments(sourceCode);
                fclose(sourceCode);
            }
            else if(option == '2')
            {
                printf("analysing file : %s\n" , argv[1]);
                sourceCode =fopen(argv[1],"r");
                initializeLexer(sourceCode);
                tokenizeSource();
                fclose(sourceCode);
            }
            else if(option == '3')
            {
                printf("needs to be implemented\n");
            }
            else if(option =='4')
            {
                printf("needs to be implemented\n");
            }
            else
            {
                printf("no option found\n");
            }

        }
        printf("program exited\n");
    }
    return 0;
}