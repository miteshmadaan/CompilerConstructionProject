#include "defForLexer.h"
#include "driver.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>


//This function is called when the dfa identifies a lexeme as toke and now needs to return it as token struct
TOKEN makeToken()
{
    TOKEN token;
    token.lineNumber = lineNumber;

    //decide the lexemtype, tokenType and then store the lexeme depending on the state number



    return token;
}

