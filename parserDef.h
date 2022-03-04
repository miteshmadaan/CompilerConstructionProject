/* 
* Mitesh Madaan             2018B5A70901P
* Shreyas Das               2019A7PS0111P
* Rahul Taak                2019A7PS0012P
* Manik Chopra              2019A7PS0144P
* Muppirisetty R Bharadwaj  2019A7PS0025P
*/
#ifndef PARSERDEF_H
#define PARSERDEF_H

#include "lexerDef.h"

#define NUM_NTERMINALS 53
#define NUM_TERMINALS 60
#define NUM_RULES 95
#define RULE_MAX_LEN 15
#define NTERMINAL_OFFSET 12345
#define ID_MAX_SIZE 30
#define eps 59

typedef enum nonTerminals{
program = NTERMINAL_OFFSET,
mainFunction,
otherFunctions,
function,
input_par,
output_par,
parameter_list,
dataType,
primitiveDatatype,
constructedDatatype,
remaining_list,
stmts,
typeDefinitions,
typeDefinition,
fieldDefinitions,
fieldDefinition,
moreFields,
declarations,
declaration,
global_or_not,
otherStmts,
stmt,
assignmentStmt,
singleOrRecId,
singleOrRecIdPrime,
funCallStmt,
outputParameters,
inputParameters,
iterativeStmt,
conditionalStmt,
elsePart,
ioStmt,
allVar,
arithmeticExpression,
expPrime,
term,
termPrime,
factor,
highPrecedenceOperators,
lowPrecedenceOperators,
all,
temp,
booleanExpression,
var,
logicalOp,
relationalOp,
returnStmt,
optionalReturn,
idList,
more_ids,
actualOrRedifined,
fieldType,
option_single_constructed,
oneExpansion,
moreExpansions,
definetypestmt,
A
}nonTerminals;

typedef struct NTERMINAL{
    int rulesNum;
    int** prodRules;
}NTERMINAL;

typedef NTERMINAL* Grm;

typedef struct treeNode
{
	int numChild;
	int numChildAST;
	TOKEN* terminal;
    int ruleNo;
	int nonTerminal;
	struct treeNode* children;
	// struct tablePointer* tp;
} treeNode;

typedef int* FIRST;
typedef struct PTEntry
{
	int nonTerm;
	int productionNum;
	int syn;
}PTEntry;

typedef treeNode* parseTree;
typedef FIRST* FirstSet;
typedef FIRST* FollowSet;
typedef PTEntry parseTable[NUM_NTERMINALS][NUM_TERMINALS];

#endif