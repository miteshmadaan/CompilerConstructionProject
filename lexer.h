/* 
* Mitesh Madaan             2018B5A70901P
* Shreyas Das               2019A7PS0111P
* Rahul Taak                2019A7PS0012P
* Manik Chopra              2019A7PS0144P
* Muppirisetty R Bharadwaj  2019A7PS0025P
*/
#ifndef LEXER_H
#define LEXER_H

#include "lexerDef.h"

TOKEN makeToken(tokenType tokenTypeInput);
void initializeLexer(FILE *sourceCode);
void tokenizeSource();//Calls the DFA
char getCharFromBuffer();
TOKEN getNextTokenFromDFA();//Contains DFA
void populateBuffer();
void retract(int retractNum);

void initializeHashTable();
void populateHashTable();
int calcHash(char *lexeme);
tokenType searchHashTable(char *lexeme);//return TK_FIELDID if not keyword

#endif