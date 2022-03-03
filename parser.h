#ifndef PARSER_H
#define PARSER_H

#include "defForLexer.h"
#include "defForParser.h"

int* calculateFirst(int production, Grm g, FirstSet firstSet);
int* add(int* ans, int* addit);
void buildFirstSet(Grm g, FirstSet firstSet);
void getGram(char *fname, Grm g);
void getFollowSets(Grm g, FollowSet fw, FirstSet fr);
void findFollow(int NonTerminalNo, int productionNo, Grm g, FollowSet fw, FirstSet fr,int* flag);
void createParseTable(FirstSet firstSet,FollowSet followSet,Grm g,parseTable t);
void add2(int* ans,int* add,int* flag);
void parseInputSourceCode(FILE* sourceFile,parseTable t,Grm g,parseTree root,int* error);
void printParseTree(parseTree root);

#endif