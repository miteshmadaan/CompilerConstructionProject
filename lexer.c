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

void populateBuffer()
{
    //fread(&buffer[forwardBufferPointer], 1, BUFFER_SIZE / 2, sourceCode);
    //shreyas will implement rest
    //suppose if lexeme begin is at 5 and forward is at 10 , Now if the populate fxn is called then all the data
    //from index 5 to 10 should shift to 0 to 4 and now from index 5 new data from source code needs to added
}

void intializeLexer(FILE *inputFile)
{
    dfaState = 0;
    lineNumber =1;
    retractCount =0;
    lexemeBeginPointer =0;
    forwardBufferPointer = 0;
    sourceCode = inputFile;

    populateBuffer(sourceCode);
}

//Contains DFA
TOKEN getNextTokenFromDFA(){
    char ch;
    TOKEN token;
    while(1){
        token.lineNumber = lineNumber;

        switch(dfaState){
            //cases here!

            case 0:
                if((ch=='a') || ( ('e'<= ch) && (ch <= 'z')  ) ){
                    dfaState = 1;
                }
                else if(('b'<=ch) && (ch <= 'd')){
                    dfaState =2;
                }
                else if( (0<= (ch-'0')) && ((ch-'0') <=9) ){
                    dfaState  =7;
                }
                else if(ch=='_'){
                    dfaState = 17;
                }
                else if(ch=='#'){
                    dfaState = 21;
                }
                else if(ch=='['){
                    dfaState = 24;
                }
                else if(ch==']'){
                    dfaState = 25;
                }
                else if(ch=='('){
                    dfaState = 26;
                }
                else if(ch==')'){
                    dfaState = 27;
                }
                else if(ch==','){
                    dfaState = 28;
                }
                else if(ch==';'){
                    dfaState = 29;
                }
                else if(ch==':'){
                    dfaState = 30;
                }
                else if(ch=='.'){
                    dfaState = 31;
                }
                else if(ch=='%'){
                    dfaState = 32;
                }
                else if( (ch==' ') || (ch=='\t') || (ch=='\n') || (ch=='\r') ){
                    dfaState = 34;
                    if(ch=='\n'){
                        lineNumber++;
                    }
                }
                else if(ch=='!'){
                    dfaState = 36;
                }
                else if(ch=='>'){
                    dfaState = 38;
                }
                else if(ch=='<'){
                    dfaState = 41;
                }
                else if(ch=='='){
                    dfaState = 47;
                }
                else if(ch=='&'){
                    dfaState = 49;
                }
                else if(ch=='@'){
                    dfaState = 52;
                }
                else if(ch=='~'){
                    dfaState = 55;
                }
                else if(ch=='+'){
                    dfaState = 56;
                }
                else if(ch=='-'){
                    dfaState = 57;
                }
                else if(ch=='*'){
                    dfaState = 58;
                }
                else if(ch=='/'){
                    dfaState = 59;
                }
                else if(ch== EOF){
                    //leaving DOLLAR token, will add later
                    dfaState = 60;
                }
                else{
                    dfaState = 61; //error report state new state
                }
                break;
                
                
                
                

        }



    }


}