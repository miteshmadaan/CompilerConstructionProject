#ifndef DEFFORLEXER_H
#define DEFFORLEXER_H

#include "driver.h"


#define LEXEME_MAX_LEN 100
#define BUFFER_SIZE 10000
#define HASHTABLE_SIZE 163
#define PRIME 53

int retractCount;
int lineNumber;
int dfaState;
int forwardBufferPointer;
int lexemeBeginPointer;
char lexeme[LEXEME_MAX_LEN];
char buffer[BUFFER_SIZE];
struct entry *hashTable[HASHTABLE_SIZE];
FILE *sourceCode;

typedef enum {
#include "tokenTypes.txt"
} tokenType;

typedef enum {
  INT,
  DOUBLE,
  STRING
} lexemeType;

typedef struct TOKEN {
  tokenType tokenType;
  lexemeType lexemeType;
  union {
    char strLexeme[LEXEME_MAX_LEN];
    int intLexeme;
    double reallexeme;
  };
  int lineNumber;
} TOKEN;

typedef struct entry{
  char keyword[LEXEME_MAX_LEN];
  tokenType tokenID;
} entry;

#endif
