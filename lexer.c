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
    int s = 0;
    while(lexemeBeginPointer < BUFFER_SIZE){
        buffer[s++] = buffer[lexemeBeginPointer];
        lexemeBeginPointer++;
    }
    forwardBufferPointer = s-1;
    lexemeBeginPointer = 0;
    int n = fread(&buffer[s], 1, BUFFER_SIZE - s, sourceCode);
    if(n != BUFFER_SIZE - s){
        buffer[s + n] = EOF;
    }
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

char getCharFromBuffer()
{
    if(forwardBufferPointer == BUFFER_SIZE-1)
    {
        populateBuffer(sourceCode);
    }

    char ch = buffer[forwardBufferPointer];
    forwardBufferPointer++;
    return ch;
}

void retract(int retractNum)
{
    forwardBufferPointer -= retractNum;
}

//Contains DFA
TOKEN getNextTokenFromDFA(){
    char ch;
    TOKEN token;
    int tokenReady = 0;
    while(1){
        token.lineNumber = lineNumber;

        switch(dfaState){
            //cases here!

            case 0:
                ch = getCharFromBuffer();
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
                    dfaState = 61; //error report state
                }
                break;
                
            case 24:
                dfaState = 0;
                token.tokenType = TK_SQL;
                tokenReady = 1;
                break;

            case 25:
                dfaState = 0;
                token.tokenType = TK_SQR;
                tokenReady = 1;
                break;  

            case 26:
                dfaState = 0;
                token.tokenType = TK_OP;
                tokenReady = 1;
                break;

            case 27:
                dfaState = 0;
                token.tokenType = TK_CL;
                tokenReady = 1;
                break;  
           
            case 28:
                dfaState = 0;
                token.tokenType = TK_COMMA;
                tokenReady = 1;
                break;
            
            case 29:
                dfaState = 0;
                token.tokenType = TK_SEM;
                tokenReady = 1;
                break;
            
            case 30:
                dfaState = 0;
                token.tokenType = TK_COLON;
                tokenReady = 1;
                break;
            
            case 31:
                dfaState = 0;
                token.tokenType = TK_DOT;
                tokenReady = 1;
                break;

            case 32:
                ch = getCharFromBuffer();
                if(ch=='\n'){
                    lineNumber++;
                    dfaState = 33;
                }
                else{
                    dfaState = 32;
                }
                break;

            case 33:
                dfaState = 0;
                break;

            case 34:
                if( (ch==' ') || (ch=='\t') || (ch=='\n') || (ch=='\r') ){
                    dfaState = 34;
                    if(ch=='\n'){
                        lineNumber++;
                    }
                }
                else{
                    dfaState = 35;   
                }
                break;
            
            case 35:
                retract(1);
                dfaState = 0;
                break;

            case 36:
                ch = getCharFromBuffer();
                if(ch =='='){
                    dfaState = 37;
                }
                else{
                    retract(1);
                    dfaState = 61; //error report state
                }
                break;
            
            case 37:
                dfaState = 0;
                token.tokenType = TK_NE;
                tokenReady = 1;
                break;
            
            case 38:
                ch = getCharFromBuffer();
                if(ch =='='){
                    dfaState = 39;
                }
                else{
                    dfaState = 40;
                }
                break;
            
            case 39:
                dfaState = 0;
                token.tokenType = TK_GE;
                tokenReady = 1;
                break;
            
            case 40:
                retract(1);
                dfaState = 0;
                token.tokenType = TK_GT;
                tokenReady = 1;
                break;





            case 61:
                //report whatever from lexeme begin to just before forward pointer as an error!!

            default:
                break;   
        }//End of switch-case

        if(tokenReady ==1){}
            return token;
        
    }//End of while loop


}
