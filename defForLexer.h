#ifndef DEFFORLEXER_H
#define DEFFORLEXER_H


#define MAX_LEXEME_LEN  10


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
    char strLexeme[MAX_LEXEME_LEN];
    int intLexeme;
    double floatLexeme;
  };
  int lineNumber;
} TOKEN;



#endif