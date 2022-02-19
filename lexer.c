#include "driver.h"
#include "lexer.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
// #include <errno.h>
// #include <stdbool.h>


//This function is called when the dfa identifies a lexeme as toke and now needs to return it as token struct
TOKEN makeToken(tokenType tokenType)
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
    while(1){

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
            
            case 24:
                dfaState = 0;
                return makeToken(TK_SQL);
                break;

            case 25:
                dfaState = 0;
                return makeToken(TK_SQR);
                break;  

            case 26:
                dfaState = 0;
                return makeToken(TK_OP);
                break;

            case 27:
                dfaState = 0;
                return makeToken(TK_CL);
                break;  
           
            case 28:
                dfaState = 0;
                return makeToken(TK_COMMA);
                break;
            
            case 29:
                dfaState = 0;
                return makeToken(TK_SEM);
                break;
            
            case 30:
                dfaState = 0;
                return makeToken(TK_COLON);
                break;
            
            case 31:
                dfaState = 0;
                return makeToken(TK_DOT);
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
                return makeToken(TK_NE);
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
                return makeToken(TK_GE);
                break;
            
            case 40:
                retract(1);
                dfaState = 0;
                return makeToken(TK_GT);
                break;

            case 41:
                ch = getCharFromBuffer();
                if(ch == '=')
                {
                    dfaState = 43;
                }
                else if(ch == '-')
                {
                    dfaState = 44;
                }
                else
                {
                    retract(1);
                    dfaState = 61;
                }
                break;
            
            case 42:
                retract(1);
                dfaState = 0;
                return makeToken(TK_LT);
                break;

            case 43:
                dfaState = 0;
                return makeToken(TK_LE);
                break;

            case 44:
                ch = getCharFromBuffer();
                if(ch == '-')
                {
                    dfaState = 45;
                }
                else
                {
                    dfaState = 61;
                }
                break;

            case 45:
                ch = getCharFromBuffer();
                if(ch == '-')
                {
                    dfaState = 46;
                }
                else
                {
                    dfaState = 61;
                }
                break;

            case 46:
                dfaState = 0;
                return makeToken(TK_ASSIGNOP);
                break;

            case 47:
                ch = getCharFromBuffer();
                if(ch == '=')
                {
                    dfaState = 48;
                }
                else
                {
                    dfaState = 61;
                }
                break;

            case 48:
                dfaState = 0;
                return makeToken(TK_EQ);
                break;

            case 49:
                ch = getCharFromBuffer();
                if(ch == '&')
                {
                    dfaState = 50;
                }
                else
                {
                    dfaState = 61;
                }
                break;

            case 50:
                ch = getCharFromBuffer();
                if(ch == '&')
                {
                    dfaState = 51;
                }
                else
                {
                    dfaState = 61;
                }
                break;

            case 51:
                dfaState = 0;
                return makeToken(TK_AND);
                break;
            
            case 52:
                ch = getCharFromBuffer();
                if(ch == '@')
                {
                    dfaState = 51;
                }
                else
                {
                    dfaState = 61;
                }
                break;

            case 53:
                ch = getCharFromBuffer();
                if(ch == '@')
                {
                    dfaState = 51;
                }
                else
                {
                    dfaState = 61;
                }
                break;

            case 54:
                dfaState = 0;
                return makeToken(TK_OR);
                break;

            case 55:
                dfaState = 0;
                return makeToken(TK_NOT);
                break;

            case 56:
                dfaState = 0;
                return makeToken(TK_PLUS);
                break;

            case 57:
                dfaState = 0;
                return makeToken(TK_MINUS);
                break;

            case 58:
                dfaState = 0;
                return makeToken(TK_MUL);
                break;

            case 59:
                dfaState = 0;
                return makeToken(TK_DIV);
                break;

            case 60:
                //needs to be implemented
                break;

            case 61:
                //needs to be implemented
                break;    
        }
}
