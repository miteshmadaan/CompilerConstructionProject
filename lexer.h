#ifndef LEXER_H
#define LEXER_H

#include "defForLexer.h"

TOKEN makeToken();
void intializeLexer(FILE *sourceCode);
void tokenizeSource(FILE *sourceCode);//Calls the DFA
char getCharFromBuffer(FILE *sourceCode);
TOKEN getNextTokenFromDFA(FILE *sourceCode);//Contains DFA
void populateBuffer(FILE *sourceCode);
void retract(int retractNum);


#endif