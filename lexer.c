#include "driver.h"
#include "lexer.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
// #include <errno.h>
// #include <stdbool.h>


//This function is called when the dfa identifies a lexeme as toke and now needs to return it as token struct
TOKEN makeToken()
{
    TOKEN token;
    token.lineNumber = lineNumber;

    //decide the lexemtype, tokenType and then store the lexeme depending on the state number



    return token;
}

void populateBuffer(FILE *sourceCode)
{
    //fread(&buffer[forwardBufferPointer], 1, BUFFER_SIZE / 2, sourceCode);
    //shreyas will implement rest
    //suppose if lexeme begin is at 5 and forward is at 10 , Now if the populate fxn is called then all the data
    //from index 5 to 10 should shift to 0 to 4 and now from index 5 new data from source code needs to added
}

void intializeLexer(FILE *sourceCode)
{
    dfaState = 0;
    lineNumber =1;
    retractCount =0;
    lexemeBeginPointer =0;
    forwardBufferPointer = 0;

    populateBuffer(sourceCode);
}


char getCharFromBuffer(FILE *sourceCode)
{
    if(forwardBufferPointer == BUFFER_SIZE-1)
    {
        populateBuffer(sourceCode);
    }

    forwardBufferPointer++;
    return buffer[forwardBufferPointer];

}

void retract(int retractNum)
{
    forwardBufferPointer -= retractNum;
}