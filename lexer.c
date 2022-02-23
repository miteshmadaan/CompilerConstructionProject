#include "driver.h"
#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <ctype.h>
// #include <errno.h>
// #include <stdbool.h>

int power(int base, int exponent){
    int ans = 1;
    while(exponent >= 1){
        ans = ans * base;
    }
    return ans;
}

double customAtof(char* str){
    double value=0.0;
    double nonExponentialPart=0.0;
    double exponentialPart=0.0;
    int factor = 1;
    char esign;

    char* chptr = str;
    while((*chptr!='.')){
        nonExponentialPart = nonExponentialPart*10 + (*chptr - '0');
        chptr++;
    }
    chptr++;
    while((*chptr != 'E') && (*chptr != '\0')){
        nonExponentialPart = nonExponentialPart*10 + (*chptr - '0');
        factor*=10;
        chptr++;
    }
    nonExponentialPart = nonExponentialPart/factor;

    if(*chptr == '\0')   return nonExponentialPart;
    chptr++;

    if((*chptr == '+') || (*chptr == '-')){
        esign = *chptr;
        chptr++;
    }
    else{
        esign = '+';
    }

    while(*chptr != '\0'){
        exponentialPart = exponentialPart*10 + (*chptr - '0');
        chptr++;
    }
    
    if(esign == '-'){
        value = nonExponentialPart*power(10,exponentialPart);
    }else{
        value = nonExponentialPart/power(10,exponentialPart);
    }

    return value;
}

//This function is called when the dfa identifies a lexeme as toke and now needs to return it as token struct
TOKEN makeToken(tokenType tokenTypeInput)
{
    TOKEN token;
    token.lineNumber = lineNumber;
    int lexemeSize=0;
    int ptr = lexemeBeginPointer;
    
    lexemeSize = forwardBufferPointer - lexemeBeginPointer;
    while(ptr<forwardBufferPointer){
            if((ptr-lexemeBeginPointer) == LEXEME_MAX_LEN)   break;
            lexeme[ptr-lexemeBeginPointer] = buffer[ptr];
            ptr++;
    }
    lexemeBeginPointer = forwardBufferPointer;
    
    if(lexemeSize<LEXEME_MAX_LEN){
            lexeme[lexemeSize] = '\0';
    }
    else{
            lexeme[LEXEME_MAX_LEN-1] = '\0';
    }
    
    switch(tokenTypeInput){

        case TK_FIELDID:
            if(lexemeSize > 20){
                token.tokenType = TK_ERROR;
            }
            else{
                // token.tokenType = search in lookup table
                token.tokenType = tokenTypeInput;
            }
            token.lexemeType = STRING;
            strncpy(token.strLexeme, lexeme, LEXEME_MAX_LEN);
            return token;
            break;

        case TK_FUNID:
            if(lexemeSize > 30){
                token.tokenType = TK_ERROR;
            }
            else{
                if(strcmp(lexeme, "_main") == 0){
                    token.tokenType = TK_MAIN;
                }
                else{
                    token.tokenType = TK_FUNID;
                }
            }
            token.lexemeType = STRING;
            strncpy(token.strLexeme, lexeme, LEXEME_MAX_LEN);
            return token;
            break;

        case TK_NUM:
            token.tokenType = TK_NUM;
            token.lexemeType = INT;
            token.intLexeme = atoi(lexeme);
            return token;
            break;

        case TK_RNUM:
            token.tokenType = TK_NUM;
            token.lexemeType = FLOAT;
            token.floatLexeme = customAtof(lexeme);//need special attention for E types
            return token;
            break;

        case TK_ERROR:
            token.tokenType = TK_ERROR;
            token.lexemeType = STRING;
            strncpy(token.strLexeme, lexeme, LEXEME_MAX_LEN);
            return token;
            break;

        case TK_COMMENT:
            token.tokenType = TK_COMMENT;
            return token;
            break;

        case TK_EOF:
            token.tokenType = TK_EOF;
            return token;
            break;

        default:
            if(lexemeSize > 20){
                token.tokenType = TK_ERROR;
            }
            else{
                token.tokenType = tokenTypeInput;
            }
            token.lexemeType = STRING;
            strncpy(token.strLexeme, lexeme, LEXEME_MAX_LEN);
            return token;
            break;

    }//End of switch
    
}

void tokenizeSource(){

    TOKEN tokenFromDfa;
    // int internalLineNumber = lineNumber;
    while(1)
    {
        tokenFromDfa = getNextTokenFromDFA();
        printf("Token : %d, " , tokenFromDfa.tokenType);
        if (tokenFromDfa.tokenType == TK_EOF)
        {
            printf("End Of File\nLexical Analysis completed\n");
            break;
        }
        else
        {
            if(tokenFromDfa.lexemeType == STRING)
            {   
                printf("lexeme : %s, " , tokenFromDfa.strLexeme);
            }
            else if(tokenFromDfa.lexemeType == INT)
            {
                printf("lexeme : %d, " , tokenFromDfa.intLexeme);
            }
            else
            {
                printf("lexeme : %f, " , tokenFromDfa.floatLexeme);
            }
            printf("Line Number : %d\n" , tokenFromDfa.lineNumber);
        }
    }

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

void initializeLexer(FILE *inputFile)
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
                    dfaState = 61; //error report state new state
                }
                break;
                
            case 1:
                ch = getCharFromBuffer();
                if((ch >= 'a') && (ch <= 'z')){
                    dfaState = 1;
                }
                else{
                    dfaState = 2;
                }
                break;

            case 2:
                retract(1);
                dfaState = 0;
                //lexemeBeginPointer = forwardBufferPointer;
                return makeToken(TK_FIELDID);
                break;
            
            case 3:
                ch = getCharFromBuffer();
                if((ch >= 'a') && (ch <= 'z')){
                    dfaState = 1;
                }
                else if((ch >= '2') && (ch <= '7')){
                    dfaState = 4;
                }
                else{
                   dfaState = 2;
                }
                break;

            case 4:
                ch = getCharFromBuffer();
                if((ch >= 'b') && (ch <= 'd')){
                    dfaState = 4;
                }
                else if((ch >= '2') && (ch <= '7')){
                    dfaState = 5;
                }
                else{
                    dfaState = 6;
                }
                break;

            case 5:
                ch = getCharFromBuffer();
                if((ch >= '2') && (ch <= '7')){
                    dfaState = 5;
                }
                else{
                    dfaState = 6;
                }
                break;

            case 6:
                retract(1);
                dfaState = 0;
                //lexemeBeginPointer = forwardBufferPointer;
                return makeToken(TK_ID);
                break;

            case 7:
                ch = getCharFromBuffer();
                if((ch >= '0') && (ch <= '9')){
                    dfaState = 7;
                }
                else if(ch == '.'){
                    dfaState = 9;
                }
                else{
                    dfaState = 8;
                }
                break;

            case 8:
                retract(1);
                dfaState = 0;
                //lexemeBeginPointer = forwardBufferPointer;
                return makeToken(TK_NUM);
                break;

            case 9:
                ch = getCharFromBuffer();
                if((ch >= '0') && (ch <= '9')){
                    dfaState = 10;
                }
                else{
                    retract(2);
                    dfaState = 0;
                    return makeToken(TK_NUM);
                }
                break;

    
            case 10:
                ch = getCharFromBuffer();;
                if((ch >= '0') && (ch <= '9')){
                    dfaState = 11;
                }
                else{
                    retract(3);
                    dfaState = 0;
                    return makeToken(TK_NUM);
                }
                break;

            case 11:
                ch = getCharFromBuffer();
                if(ch == 'E'){
                    dfaState = 12;
                }
                else{
                    dfaState = 16;
                }
                break;
            
            case 12:
                ch = getCharFromBuffer();
                if((ch == '+') || (ch == '-')){
                    dfaState = 13;
                }
                else if((ch >= '0') && (ch <= '9')){
                    dfaState = 14;
                }
                else{
                    retract(2);
                    dfaState = 0;
                    return makeToken(TK_RNUM);
                }
                break;

            case 13:
                ch = getCharFromBuffer();
                if((ch >= '0') && (ch <= '9')){
                    dfaState = 14;
                }
                else{
                    retract(3);
                    dfaState = 0;
                    return makeToken(TK_RNUM);
                }
                break;

            case 14: //Special Case
                ch = getCharFromBuffer();
                if((ch >= '0') && (ch <= '9')){
                    dfaState = 15;
                }
                else{
                    while(buffer[forwardBufferPointer] != 'E'){
                        retract(1);
                    }
                    dfaState = 0;
                    return makeToken(TK_RNUM);
                }
                break;

            case 15:
                ch = getCharFromBuffer();
                dfaState = 16;
                break;
            
            case 16:
                retract(1);
                dfaState = 0;
                return makeToken(TK_RNUM);
                break;

            case 17:
                ch = getCharFromBuffer();
                if(((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z'))){
                    dfaState = 18;
                }
                else{
                    retract(1);
                    dfaState = 61;
                } 
                break;
            
            case 18:
                ch = getCharFromBuffer();
                if(((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z'))){
                    dfaState = 18;
                }
                else if((ch >= '0') && (ch <= '9')){
                    dfaState = 19;
                }
                else{
                    dfaState = 20;
                }
                break;

            case 19:
                ch = getCharFromBuffer();
                if((ch >= '0') && (ch <= '9')){
                    dfaState = 19;
                }
                else{
                    dfaState = 20;
                }
                break;
            
            case 20:
                retract(1);
                dfaState = 0;
                return makeToken(TK_FUNID);
                break;

            case 21:
                ch = getCharFromBuffer();
                if((ch >= 'a') && (ch <= 'z')){
                    dfaState = 22;
                }
                else{
                    retract(1);
                    dfaState = 61;
                }
                break;

            case 22:
                ch = getCharFromBuffer();
                if((ch >= 'a') && (ch <= 'z')){
                    dfaState = 22;
                }
                else{
                    dfaState = 23;
                }
                break;

            case 23:
                retract(1);
                dfaState = 0;
                return makeToken(TK_RUID);
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
                return makeToken(TK_COMMENT);
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
                    dfaState = 42;
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
                    retract(2);
                    dfaState = 0;
                    return makeToken(TK_LT);
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
                    retract(3);
                    dfaState = 0;
                    return makeToken(TK_LT);
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
                    retract(1);
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
                    retract(1);
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
                    retract(1);
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
                    dfaState = 53;
                }
                else
                {
                    retract(1);
                    dfaState = 61;
                }
                break;

            case 53:
                ch = getCharFromBuffer();
                if(ch == '@')
                {
                    dfaState = 54;
                }
                else
                {
                    retract(1);
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
                return makeToken(TK_EOF);
                break;

            case 61:
                dfaState = 0;
                return makeToken(TK_ERROR);
                break;    
        }
    }
}
