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

#include "lexerDef.h"
#include "parserDef.h"

void initializeParser();
void getGram(char *fname, Grm g);
void getFirst(char *fname, FirstSet firstSet);
void getFollow(char *fname, FollowSet followSet);

int* calculateFirst(int produc,Grm g,FirstSet firstSet);
void buildFirstSet(Grm g, FirstSet firstSet);
void getFollowSets(Grm g, FollowSet follow0, FirstSet first0);
void findFollow(int nTerminalNum, int prodNum, Grm g, FollowSet followSet, FirstSet firstSet,int* flg2);
void add2(int* answer,int* add0,int* flg0);

void createParseTable();
void printParseTable();
void parseInputSourceCode(FILE* sourceFile,int* error);
void printParseTree(FILE* parserOutput,parseTree root);
void firstString(int* b,int* firstRule,int index);
int* add(int* ans, int* addit);

int parseIdStr(char *idStr);
char *idRepr(int id);
char *tokenRepr(int id);

#endif