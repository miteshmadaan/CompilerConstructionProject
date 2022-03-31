#ifndef AST_H
#define AST_H

#include "parserDef.h"

int useful(int node);
parseTree createAST();
void buildAST(parseTree ast,parseTree root);
void createASTUtils(parseTree curr, parseTree par);
void copy(parseTree dst,parseTree src);
void nodeCount(parseTree root,int* ans);
void nodeCountAST(parseTree root,int* ans);
void printAST(parseTree root);

#endif