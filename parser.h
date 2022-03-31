/* 
* Group No. 46
* Mitesh Madaan             2018B5A70901P
* Shreyas Das               2019A7PS0111P
* Rahul Taak                2019A7PS0012P
* Manik Chopra              2019A7PS0144P
* Muppirisetty R Bharadwaj  2019A7PS0025P
*/
#ifndef PARSER_H
#define PARSER_H

#include "parserDef.h"

void initializeParser();
void getGram(char *fname, Grm g);
void getFirst(char *fname, FirstSet firstSet);
void getFollow(char *fname, FollowSet followSet);

void createParseTable();
parseTree parseInputSourceCode(int* error);
void printParseTree(FILE* parserOutput,parseTree root);
void firstString(int* b,int* firstRule,int index);
int* add(int* ans, int* addit);

#endif