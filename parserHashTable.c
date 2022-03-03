#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "parserHashTable.h"

parserKaTable* makeParserHashTable(int number_pos)
{
	parserKaTable* lookUpTable = (parserKaTable*)malloc(sizeof(parserKaTable));

	lookUpTable->number_pos = number_pos;

	lookUpTable->positions = (parserKaList**)malloc(number_pos*sizeof(parserKaList*));
	for(int i=0;i<number_pos;i++){
		lookUpTable->positions[i] = (parserKaList*)malloc(sizeof(parserKaList));
		lookUpTable->positions[i]->head = NULL;
	}
	fillingPHT(lookUpTable);
	return lookUpTable;
}

void addElementInPHT(parserKaTable* lookUpTable, char* k, tokenType tokentype)
{
	parserKaElement* enter = (parserKaElement*)malloc(sizeof(parserKaElement));
	enter->type = tokentype;
	int hashedvalue =  hashingFuncForPHT(k,lookUpTable->number_pos);
	enter->lexeme = (char*)malloc(sizeof(char)*(strlen(k)+1));
	strcpy(enter->lexeme,k);
	enter->next = lookUpTable->positions[hashedvalue]->head;
	lookUpTable->positions[hashedvalue]->head = enter;
}


int hashingFuncForPHT(char* k, int number_pos)
{
	int sumtotal = 0;
	for(int i=0;i<strlen(k);i++){
		sumtotal = sumtotal*10 + (k[i] - '0');
		if(sumtotal<0)
			sumtotal = 0;
	}
	int hashedvalue = sumtotal % number_pos;
	return hashedvalue;
}

//filling table with entries of element
void fillingPHT(parserKaTable* lookUpTable)
{
	addElementInPHT( lookUpTable, "program", 12345);
	addElementInPHT( lookUpTable, "mainFunction", 12346);
	addElementInPHT( lookUpTable, "otherFunctions", 12347);
	addElementInPHT( lookUpTable, "function", 12348);
	addElementInPHT( lookUpTable, "input_par", 12349);
	addElementInPHT( lookUpTable, "output_par", 12350);
	addElementInPHT( lookUpTable, "parameter_list", 12351);
	addElementInPHT( lookUpTable, "dataType", 12352);
	addElementInPHT( lookUpTable, "primitiveDatatype", 12353);
	addElementInPHT( lookUpTable, "constructedDatatype", 12354);
	addElementInPHT( lookUpTable, "remaining_list", 12355);
	addElementInPHT( lookUpTable, "stmts", 12356);
	addElementInPHT( lookUpTable, "typeDefinitions", 12357);
	addElementInPHT( lookUpTable, "typeDefinition", 12358);
	addElementInPHT( lookUpTable, "fieldDefinitions", 12359);
	addElementInPHT( lookUpTable, "fieldDefinition", 12360);
	addElementInPHT( lookUpTable, "moreFields", 12361);
	addElementInPHT( lookUpTable, "declarations",12362);
	addElementInPHT( lookUpTable, "declaration", 12363);
	addElementInPHT( lookUpTable, "global_or_not", 12364);
	addElementInPHT( lookUpTable, "otherStmts", 12365);
	addElementInPHT( lookUpTable, "stmt", 12366);
	addElementInPHT( lookUpTable, "assignmentStmt", 12367);
	addElementInPHT( lookUpTable, "singleOrRecId", 12368);
	addElementInPHT( lookUpTable, "singleOrRecIdPrime", 12369);	
	addElementInPHT( lookUpTable, "funCallStmt", 12370);
	addElementInPHT( lookUpTable, "outputParameters", 12371);
	addElementInPHT( lookUpTable, "inputParameters", 12372);
	addElementInPHT( lookUpTable, "iterativeStmt",12373 );
	addElementInPHT( lookUpTable, "conditionalStmt", 12374);	
	addElementInPHT( lookUpTable, "elsePart", 12375);
	addElementInPHT( lookUpTable, "ioStmt", 12376);
	addElementInPHT( lookUpTable, "allVar", 12377);
	addElementInPHT( lookUpTable, "arithmeticExpression", 12378);
	addElementInPHT( lookUpTable, "expPrime", 12379);
	addElementInPHT( lookUpTable, "term", 12380);
	addElementInPHT( lookUpTable, "termPrime", 12381);
	addElementInPHT( lookUpTable, "factor", 12382);
	addElementInPHT( lookUpTable, "highPrecedenceOperators",12383);
	addElementInPHT( lookUpTable, "lowPrecedenceOperators", 12384);
	addElementInPHT( lookUpTable, "all", 12385);
	addElementInPHT( lookUpTable, "temp",12386);
	addElementInPHT( lookUpTable, "booleanExpression",12387);
	addElementInPHT( lookUpTable, "var",12388);
	addElementInPHT( lookUpTable, "logicalOp", 12389);
	addElementInPHT( lookUpTable, "relationalOp", 12390);
	addElementInPHT( lookUpTable, "returnStmt", 12391);
	addElementInPHT( lookUpTable, "optionalReturn", 12392);
	addElementInPHT( lookUpTable, "idList", 12393);
	addElementInPHT( lookUpTable, "more_ids", 12394);




	addElementInPHT( lookUpTable, "actualOrRedifined", 12395);
	addElementInPHT( lookUpTable, "fieldType", 12396);
	addElementInPHT( lookUpTable, "option_single_constructed", 12397);
	addElementInPHT( lookUpTable, "oneExpansion", 12398);
	addElementInPHT( lookUpTable, "moreExpansions", 12399);
	addElementInPHT( lookUpTable, "definetypestmt", 12400);
	addElementInPHT( lookUpTable, "A", 12401);
	

	
	
	addElementInPHT( lookUpTable, "TK_ASSIGNOP", TK_ASSIGNOP);
	addElementInPHT( lookUpTable, "TK_COMMENT", TK_COMMENT);
	addElementInPHT( lookUpTable, "TK_FIELDID", TK_FIELDID);
	addElementInPHT( lookUpTable, "TK_ID", TK_ID);
	addElementInPHT( lookUpTable, "TK_NUM", TK_NUM);
	addElementInPHT( lookUpTable, "TK_RNUM", TK_RNUM);
	addElementInPHT( lookUpTable, "TK_FUNID", TK_FUNID);
	addElementInPHT( lookUpTable, "TK_RUID", TK_RUID);
	addElementInPHT( lookUpTable, "TK_WITH", TK_WITH);
	addElementInPHT( lookUpTable, "TK_PARAMETERS", TK_PARAMETERS);
	addElementInPHT( lookUpTable, "TK_END", TK_END);
	addElementInPHT( lookUpTable, "TK_WHILE", TK_WHILE);
	addElementInPHT( lookUpTable, "TK_INT", TK_INT);
	addElementInPHT( lookUpTable, "TK_REAL", TK_REAL);
	addElementInPHT( lookUpTable, "TK_TYPE", TK_TYPE);
	addElementInPHT( lookUpTable, "TK_MAIN", TK_MAIN);
	addElementInPHT( lookUpTable, "TK_GLOBAL", TK_GLOBAL);
	addElementInPHT( lookUpTable, "TK_PARAMETER", TK_PARAMETER);
	addElementInPHT( lookUpTable, "TK_LIST", TK_LIST);
	addElementInPHT( lookUpTable, "TK_SQL", TK_SQL);
	addElementInPHT( lookUpTable, "TK_SQR", TK_SQR);
	addElementInPHT( lookUpTable, "TK_INPUT", TK_INPUT);
	addElementInPHT( lookUpTable, "TK_OUTPUT", TK_OUTPUT);
	addElementInPHT( lookUpTable, "TK_SEM", TK_SEM);
	addElementInPHT( lookUpTable, "TK_COLON", TK_COLON);
	addElementInPHT( lookUpTable, "TK_DOT", TK_DOT);
	addElementInPHT( lookUpTable, "TK_COMMA", TK_COMMA);
	addElementInPHT( lookUpTable, "TK_ENDWHILE", TK_ENDWHILE);
	addElementInPHT( lookUpTable, "TK_OP", TK_OP);
	addElementInPHT( lookUpTable, "TK_CL", TK_CL);
	addElementInPHT( lookUpTable, "TK_IF", TK_IF);
	addElementInPHT( lookUpTable, "TK_THEN", TK_THEN);
	addElementInPHT( lookUpTable, "TK_ENDIF", TK_ENDIF);
	addElementInPHT( lookUpTable, "TK_READ", TK_READ);
	addElementInPHT( lookUpTable, "TK_WRITE", TK_WRITE);
	addElementInPHT( lookUpTable, "TK_RETURN", TK_RETURN);
	addElementInPHT( lookUpTable, "TK_PLUS", TK_PLUS);
	addElementInPHT( lookUpTable, "TK_MINUS", TK_MINUS);
	addElementInPHT( lookUpTable, "TK_MUL", TK_MUL);
	addElementInPHT( lookUpTable, "TK_DIV", TK_DIV);
	addElementInPHT( lookUpTable, "TK_CALL", TK_CALL);
	addElementInPHT( lookUpTable, "TK_RECORD", TK_RECORD);
	addElementInPHT( lookUpTable, "TK_ENDRECORD", TK_ENDRECORD);
	addElementInPHT( lookUpTable, "TK_ELSE", TK_ELSE);
	addElementInPHT( lookUpTable, "TK_AND", TK_AND);
	addElementInPHT( lookUpTable, "TK_OR", TK_OR);
	addElementInPHT( lookUpTable, "TK_NOT", TK_NOT);
	addElementInPHT( lookUpTable, "TK_LT", TK_LT);
	addElementInPHT( lookUpTable, "TK_LE", TK_LE);
	addElementInPHT( lookUpTable, "TK_EQ", TK_EQ);
	addElementInPHT( lookUpTable, "TK_GT", TK_GT);
	addElementInPHT( lookUpTable, "TK_GE", TK_GE);
	addElementInPHT( lookUpTable, "TK_NE", TK_NE);




	addElementInPHT( lookUpTable, "TK_EOF", TK_EOF);
	
	addElementInPHT( lookUpTable, "TK_ERROR",TK_ERROR);



	addElementInPHT( lookUpTable, "TK_UNION",TK_UNION);
	addElementInPHT( lookUpTable, "TK_ENDUNION",TK_ENDUNION);
	addElementInPHT( lookUpTable, "TK_DEFINETYPE",TK_DEFINETYPE);
	addElementInPHT( lookUpTable, "TK_AS",TK_AS);
	addElementInPHT( lookUpTable, "eps",58);

}



tokenType getTokenTypePHT(char* k, parserKaTable* lookUpTable)
{
	int hashedvalue = hashingFuncForPHT(k, lookUpTable->number_pos);
	parserKaElement* var = lookUpTable->positions[hashedvalue]->head;
	while(var!=NULL)
	{
		if(strcmp(var->lexeme,k)==0)
			return var->type;

		var = var->next;
	}
	return -1;
}

