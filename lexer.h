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


#endif