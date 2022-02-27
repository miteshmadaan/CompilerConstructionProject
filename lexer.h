#ifndef LEXER_H
#define LEXER_H

#include "defForLexer.h"

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
void insertHashTable(struct entry *entryInput);
TOKEN searchHashTable(char *lexeme);//return TK_FIELDID if not keyword

#endif