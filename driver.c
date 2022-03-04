/* 
* Mitesh Madaan             2018B5A70901P
* Shreyas Das               2019A7PS0111P
* Rahul Taak                2019A7PS0012P
* Manik Chopra              2019A7PS0144P
* Muppirisetty R Bharadwaj  2019A7PS0025P
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <time.h>
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
    printf("Implementation details of code:\n");
    printf("1) FIRST and FOLLOW set automated\n");
    printf("2) Both lexical analyser and syntax analyser modules implemented\n");
    printf("3) lexical analyser module works on all testcases\n");
    printf("4) Parser module compiles but segmentation fault\n\n");
    FILE *sourceCode, *parserOutput;
    Grm grammar;
    grammar = (NTERMINAL*)malloc(sizeof(NTERMINAL) * NUM_NTERMINALS);
    getGram("grammar.txt", grammar);
    FirstSet firstSet=(FirstSet)malloc(NUM_NTERMINALS*sizeof(FIRST));
    FollowSet followSet=(FollowSet)malloc(NUM_NTERMINALS*sizeof(FIRST));
    buildFirstSet(grammar,firstSet);
    getFollowSets(grammar, followSet,firstSet);
    parseTable t;
    parseTree root=malloc(sizeof(treeNode)),ast=NULL;
    
    createParseTable(firstSet,followSet,grammar,t);

    if(argc < 3)
    {
        printf("insufficient command line arguments");
    }
    else{
        char option = '5';
        while(option != '0')
        {
            printf("\nChoose your option:\n");
            printf("Option 0: Exit\n");
            printf("Option 1: Remove Comments from code\n");
            printf("Option 2: Print the stream of tokens\n");
            printf("Option 3: Print the parse tree\n");
            printf("Option 4: Print the time taken by lexer and parser\n");
            scanf("%c" , &option);
            if(option =='\n')
            {
                scanf("%c" , &option);
            }
            printf("your option is %c\n" , option);
            if(option == '1')
            {
                printf("\n----------------Removing comments from code---------------\n");
                sourceCode =fopen(argv[1],"r");
                fseek(sourceCode,0,SEEK_SET);
                if(sourceCode==NULL){
                    printf("Error cannot open file\n");
                    exit(0);
                }
                removeComments(sourceCode);
                fclose(sourceCode);
                printf("\n----------------------------------------------------------\n");
                
            }
            else if(option == '2')
            {
                printf("\n----------------Lexer module invoked---------------\n");
                printf("analysing file : %s\n" , argv[1]);
                sourceCode =fopen(argv[1],"r");
                fseek(sourceCode,0,SEEK_SET);
                if(sourceCode==NULL){
                    printf("Error cannot open file\n");
                    exit(0);
                }
                initializeLexer(sourceCode);
                tokenizeSource();
                fclose(sourceCode);
                printf("\n----------------------------------------------------------\n");
            }
            else if(option == '3')
            {
                printf("\n----------------Lexer and Parser module invoked---------------\n");
                sourceCode =fopen(argv[1],"r");
                fseek(sourceCode,0,SEEK_SET);
                if(sourceCode==NULL){
                    printf("Error cannot open file\n");
                    exit(0);
                }
                parserOutput =fopen(argv[2],"w");
                fseek(parserOutput,0,SEEK_SET);
                if(parserOutput==NULL){
                    printf("Error cannot create parser output file\n");
                    exit(0);
                }
                
                initializeLexer(sourceCode);
                int errorFound = 0;
                parseInputSourceCode(sourceCode,t,grammar,root, &errorFound);

                if(errorFound==1){
                    break;
                }
                if(root==NULL){
                    fprintf(parserOutput,"NULL\n");
                }

                fprintf(parserOutput,"\nlexeme of CurrentNode\t\tlineno\t\ttokenName\t\tvalueIfNumber\t\tparentNodeSymbol\t\tisLeafNode(yes/no)\t\tNodeSymbol\t\t\n\n");
                fprintf(parserOutput,"----\t\t");
                fprintf(parserOutput,"----\t\t");
                fprintf(parserOutput,"----\t\t");
                fprintf(parserOutput,"----\t\t");
                fprintf(parserOutput,"ROOT\t\t");
                fprintf(parserOutput,"NO\t\t");
                fprintf(parserOutput,"program\t\t");
                fprintf(parserOutput,"\n");
		
                printParseTree(parserOutput,root);
                printf("\nInput source code is syntactically correct..........\n\n");
                printf("\t\t\t\tParsing succesfull\n\n");

                fclose(sourceCode);
                fclose(parserOutput);
                printf("\n----------------------------------------------------------\n");
            }
            else if(option =='4')
            {
                clock_t start_time, end_time;

                double total_CPU_time, total_CPU_time_in_seconds;

                
                printf("\n----------------Lexer and Parser module invoked---------------\n");
                sourceCode =fopen(argv[1],"r");
                fseek(sourceCode,0,SEEK_SET);
                if(sourceCode==NULL){
                    printf("Error cannot open file\n");
                    exit(0);
                }

                start_time = clock();
                
                initializeLexer(sourceCode);
                int errorFound = 0;
                parseInputSourceCode(sourceCode,t,grammar,root, &errorFound);

                end_time = clock();

                if(errorFound==1){
                    break;
                }
                if(root==NULL){
                    printf("NULL\n");
                }

                fclose(sourceCode);

                total_CPU_time = (double) (end_time - start_time);

                total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;

                // Print both total_CPU_time and total_CPU_time_in_seconds
                printf("total_CPU_time = %f and total_CPU_time_in_seconds %f\n", total_CPU_time , total_CPU_time_in_seconds);
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