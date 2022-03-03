/* 
* Mitesh Madaan             2018B5A70901P
* Shreyas Das               2019A7PS0111P
* Rahul Taak                2019A7PS0012P
* Manik Chopra              2019A7PS0144P
* Muppirisetty R Bharadwaj  2019A7PS0025P
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defForLexer.h"

struct parserelement{
	char* lexeme;
	tokenType type;
	
	struct parserelement* next;
};

typedef struct parserelement parserKaElement;

struct parserlist{
	parserKaElement* head;
};

typedef struct parserlist parserKaList;

struct parsertable{
	
	parserKaList** positions;
	int number_pos;
};	

typedef struct parsertable parserKaTable;

//Function Declarations
parserKaTable* makeParserHashTable(int number_pos);
void addElementInPHT(parserKaTable* lookUpTable, char* k, tokenType tokentype);
int hashingFuncForPHT(char* k, int number_pos);
void fillingPHT(parserKaTable* lookUpTable);
tokenType getTokenTypePHT(char* k, parserKaTable* lookUpTable);

