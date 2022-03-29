/* 
* Group No. 46
* Mitesh Madaan             2018B5A70901P
* Shreyas Das               2019A7PS0111P
* Rahul Taak                2019A7PS0012P
* Manik Chopra              2019A7PS0144P
* Muppirisetty R Bharadwaj  2019A7PS0025P
*/
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
    printf("\nImplementation details of code:\n");
    printf("1) First and Follow sets are automated\n");
    printf("2) Lexical analyser and Parser module implemented\n");
    printf("3) Lexical module working on all test cases\n");
    printf("4) Parser module compiling, but segmentation errors\n");
    printf("5) Parser module not called in driver.c due to segmentation error\n");
    printf("6) Parse tree could not be constructed\n\n");
    FILE *sourceCode;
    
    initializeParser();
    // return 0;
    int error=0;
    printf("analysing file : sourceCode.txt\n");
    sourceCode =fopen("sourceCode.txt","r");
    fseek(sourceCode,0,SEEK_SET);
    if(sourceCode==NULL){
        printf("Error cannot open file\n");
        exit(0);
    }
    initializeLexer(sourceCode);
    // tokenizeSource();
    parseInputSourceCode(&error);
    FILE *outputFile = fopen("new.txt","w");
    printParseTree(outputFile,root);
    fclose(sourceCode);
    return 0;
    
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
            printf("Option 3: Parser Module removed due to unresolved errors\n");
            printf("Option 4: Print the time taken by lexer\n");
            scanf("%c" , &option);
            if(option =='\n')
            {
                scanf("%c" , &option);
            }
            if(option == '0')
                {
                    break;
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
                printf("\n----------------Parser module not available due to segmentation error ---------------\n");
                
                
            }
            else if(option =='4')
            {
                clock_t start_time, end_time;

                double total_CPU_time, total_CPU_time_in_seconds;

                start_time = clock();

                printf("\n----------------Lexer module invoked---------------\n");
                printf("\n----------------Time taken only for only lexical analysis---------------\n");
                
                sourceCode =fopen(argv[1],"r");
                fseek(sourceCode,0,SEEK_SET);
                if(sourceCode==NULL){
                    printf("Error cannot open file\n");
                    exit(0);
                }
                initializeLexer(sourceCode);
                TOKEN tokenFromDfa;
                while(1)
                {
                    tokenFromDfa = getNextTokenFromDFA();
                    if (tokenFromDfa.tokenType == TK_EOF)
                    {
                        break;
                    }
                }
                fclose(sourceCode);

                end_time = clock();

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