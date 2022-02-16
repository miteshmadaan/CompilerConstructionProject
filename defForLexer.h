#ifndef DEFFORLEXER_H
#define DEFFORLEXER_H

#include "driver.h"


#define LEXEME_MAX_LEN 100
#define BUFFER_SIZE 10000

int retractCount;
int lineNumber;
int dfaState;
char lexeme[LEXEME_MAX_LEN];
char buffer[BUFFER_SIZE];


typedef enum {
#include "tokenTypes.txt"
} tokenType;

typedef enum {
  INT,
  FLOAT,
  STRING
} lexemeType;

typedef struct TOKEN {
  tokenType tokenType;
  lexemeType lexemeType;
  union {
    char strLexeme[LEXEME_MAX_LEN];
    int intLexeme;
    double floatLexeme;
  };
  int lineNumber;
} TOKEN;



#endif
