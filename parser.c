/* 
* Group No. 46
* Mitesh Madaan             2018B5A70901P
* Shreyas Das               2019A7PS0111P
* Rahul Taak                2019A7PS0012P
* Manik Chopra              2019A7PS0144P
* Muppirisetty R Bharadwaj  2019A7PS0025P
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lexer.h"
#include "parser.h"
#include "stack.h"

bool check[NUM_NTERMINALS];

char* listTokens[] = {
"TK_ASSIGNOP",
"TK_COMMENT",
"TK_FIELDID",
"TK_ID",
"TK_NUM",
"TK_RNUM",
"TK_FUNID",
"TK_RUID",
"TK_WITH",
"TK_PARAMETERS",
"TK_END",
"TK_WHILE",
"TK_UNION",
"TK_ENDUNION",
"TK_DEFINETYPE",
"TK_AS",
"TK_TYPE",
"TK_MAIN",
"TK_GLOBAL",
"TK_PARAMETER",
"TK_LIST",
"TK_SQL",
"TK_SQR",
"TK_INPUT",
"TK_OUTPUT",
"TK_INT",
"TK_REAL",
"TK_COMMA",
"TK_SEM",
"TK_COLON",
"TK_DOT",
"TK_ENDWHILE",
"TK_OP",
"TK_CL",
"TK_IF",
"TK_THEN",
"TK_ENDIF",
"TK_READ",
"TK_WRITE",
"TK_RETURN",
"TK_PLUS",
"TK_MINUS",
"TK_MUL",
"TK_DIV",
"TK_CALL",
"TK_RECORD",
"TK_ENDRECORD",
"TK_ELSE",
"TK_AND",
"TK_OR",
"TK_NOT",
"TK_LT",
"TK_LE",
"TK_EQ",
"TK_GT",
"TK_GE",
"TK_NE",
"TK_ERROR",
"TK_EOF",
"eps"
};

char* strRepId[] ={
"'ASSIGNOP'",
"'COMMENT'",
"'FIELDID'",
"'ID'",
"'NUM'",
"'RNUM'",
"'FUNID'",
"'RUID'",
"'WITH'",
"'PARAMETERS'",
"'END'",
"'WHILE'",
"'UNION'",
"'ENDUNION'",
"'DEFINETYPE'",
"'AS'",
"'TYPE'",
"'MAIN'",
"'GLOBAL'",
"'PARAMETER'",
"'LIST'",
"'SQL'",
"'SQR'",
"'INPUT'",
"'OUTPUT'",
"'INT'",
"'REAL'",
"'COMMA'",
"'SEM'",
"'COLON'",
"'DOT'",
"'ENDWHILE'",
"'OP'",
"'CL'",
"'IF'",
"'THEN'",
"'ENDIF'",
"'READ'",
"'WRITE'",
"'RETURN'",
"'PLUS'",
"'MINUS'",
"'MUL'",
"'DIV'",
"'CALL'",
"'RECORD'",
"'ENDRECORD'",
"'ELSE'",
"'AND'",
"'OR'",
"'NOT'",
"'LT'",
"'LE'",
"'EQ'",
"'GT'",
"'GE'",
"'NE'",
"'ERROR'",
"'EOF'",
"'eps'",
"program", 
"mainFunction", 
"otherFunctions", 
"function", 
"input_par", 
"output_par",
"parameter_list", 
"dataType", 
"primitiveDatatype", 
"constructedDatatype", 
"remaining_list", 
"stmts", 
"typeDefinitions", 
"actualOrRedefined", 
"typeDefinition", 
"fieldDefinitions",
"fieldDefinition", 
"fieldType", 
"moreFields", 
"declarations",
"declaration", 
"global_or_not", 
"otherStmts", 
"stmt", 
"assignmentStmt", 
"singleOrRecId",
"option_single_constructed", 
"oneExpansion", 
"moreExpansions", 
"funCallStmt", 
"outputParameters", 
"inputParameters", 
"iterativeStmt",
"conditionalStmt", 
"elsePart", 
"ioStmt",
"arithmeticExpression", 
"expPrime", 
"term", 
"termPrime", 
"factor", 
"highPrecedenceOperators",
"lowPrecedenceOperators", 
"booleanExpression",
"var",
"logicalOp",
"relationalOp", 
"returnStmt", 
"optionalReturn", 
"idList", 
"more_ids", 
"definetypestmt", 
"A"
};
//terminals in natural language + eps + nonterminals list

int parseIdStr(char *idStr) 
{
	//return the id of string stored in hashtable
    return getTokenTypePHT(idStr,lookuptable);	
}

char *idRepr(int id) 
{
		if(id>=NTERMINAL_OFFSET && id<NTERMINAL_OFFSET+NUM_NTERMINALS)
		return strRepId[id-NTERMINAL_OFFSET+NUM_TERMINALS];
		else if(id>=0 && id<=59)
		return strRepId[id];
		else
		return "";
}

char *tokenRepr(int id) 
{
	if(id >= 0 && id <=59)
		return listTokens[id];
	else
		return "";
}

void printParseTree(FILE* parserOutput,parseTree root)
{
	parseTree current;
	int class=0;
	for(int i=0;i<root->numChild;i++)
	{
		current=&(root->children[i]);
		if(!current)
			fprintf(parserOutput,"NULL\n");
		
		if(current->numChildAST==0 && current->terminal->tokenType==eps)
			continue;
	
		if(current->numChildAST>0)
		{
			fprintf(parserOutput,"----\t\t");//lexeme of current node
			fprintf(parserOutput,"----\t\t");//linenumber
			fprintf(parserOutput,"----\t\t");//tokenname
			fprintf(parserOutput,"----\t\t");//valueifNumber
			fprintf(parserOutput,"%s\t\t",idRepr(root->nonTerminal));//parentnodesymbol
			fprintf(parserOutput,"NO\t\t");//isleaf
			fprintf(parserOutput,"%s\t\t",idRepr(current->nonTerminal));//current node symbol
		}
		else
		{
			if(current->terminal->tokenType==TK_NUM){
				fprintf(parserOutput,"%d\t\t",current->terminal->intLexeme);
			}
			else{
				fprintf(parserOutput,"%s\t\t",current->terminal->strLexeme);
			}
			fprintf(parserOutput,"%d\t\t",current->terminal->lineNumber);
			fprintf(parserOutput,"%s\t\t",tokenRepr(current->terminal->tokenType));
			if(current->terminal->tokenType==TK_NUM)
				fprintf(parserOutput,"%d\t\t",current->terminal->intLexeme);
            else if(current->terminal->tokenType==TK_RNUM)
                fprintf(parserOutput,"%s\t\t",current->terminal->strLexeme);
			else fprintf(parserOutput,"----\t\t");
			fprintf(parserOutput,"%s\t\t",idRepr(root->nonTerminal));//parentnodesymbol
			fprintf(parserOutput,"YES\t\t");//isleaf
			fprintf(parserOutput,"----\t\t");
		}
		fprintf(parserOutput,"\n");
		printParseTree(parserOutput, current);
	}
}

void createParseTable(){
	for(int i = 0; i < NUM_NTERMINALS; i++){
        for(int j = 0; j < NUM_TERMINALS; j++)
        {
        	parsetable[i][j].nonTerm = -1;
        	parsetable[i][j].productionNum= -1;
        	parsetable[i][j].syn=-1;
        }
	}

	int *arr1, *arr2;
	arr1 = (int*)malloc(NUM_TERMINALS*sizeof(int));

	int num_rules;
	int rule_len;

	for(int i=0; i<NUM_NTERMINALS; i++){
		// printf("%d\n",i);
		num_rules = grammar[i].rulesNum;
		
		for(int k=0;k<NUM_TERMINALS;k++)
			if(firstSet[i][k]==1)
				parsetable[i][k].syn=0;	
			
		for(int k=0;k<NUM_TERMINALS;k++)
			if(followSet[i][k]==1)
				parsetable[i][k].syn=1;	
		
		for(int j=0; j<num_rules; j++){
			// printf("rule no. %d\n",j);
			rule_len = grammar[i].prodRules[j][0];
			//populate arr1 here
			firstString(grammar[i].prodRules[j],arr1,rule_len);

			for(int k=0; k<NUM_TERMINALS; k++){
				if((arr1[k]==1) && (k!=eps)){
					parsetable[i][k].nonTerm = i;
					parsetable[i][k].productionNum = j;
					arr1[k] = 0;
				}
			}

			if(arr1[eps]==1){
				arr1[eps] = 0;
				arr2 = followSet[i];
				for(int k=0; k<NUM_TERMINALS; k++){
					if(arr2[k]==1){
						parsetable[i][k].nonTerm = i;
						parsetable[i][k].productionNum = j;
					}
				}
			}
		}
	}
	return;
}

void parseInputSourceCode(int* error){
	root->nonTerminal=(int)program;
	root->numChild=2;
	
	parseTree leaf=NULL,parent=NULL,current;
	Stack stack=createStack();
	TOKEN token;
	
	push(stack,TK_EOF,leaf);
	push(stack,program,root);
	int flag=1,terminal,nonTermID,productionNo,ruleLen;
	Key top;
	int* rule;
	
	do{
		
		if(flag){
			token = getNextTokenFromDFA();
			// printf("token: %d at line:%d\n",token.tokenType,token.lineNumber);
			// printf("dff1\n");
		}
		if(token.tokenType==TK_ERROR)
		{
			printf("\n\nLEXICAL ERROR AT LINE NO: %d   %s\n",token.lineNumber,token.strLexeme);
			//if(top1(stack)->parent->id < NUM_TERMINALS)
			//{
				pop(stack);
				continue;
			///}
		}
		if(token.tokenType==TK_COMMENT)
		continue;
		if(token.tokenType==TK_EOF)
		break;
		flag=0;
		
		top=KeyAtTopElement(stack) ;
		// printf("top ID: %d\n",top->id);
		terminal=token.tokenType ;
		current=top->parent;
		
		
		if(top->id<NUM_TERMINALS)
		{
			if(top->id!=terminal && top->id!=eps)
			{
				printf("\n\nPARSER ERROR AT LINE NO: %d The token %s for lexeme %s does not match with the expected token %s\n",token.lineNumber,tokenRepr(terminal),token.strLexeme,tokenRepr(top->id));
				*error=1;
				pop(stack);
			}
			else{
				pop(stack);
				current->terminal->lineNumber=token.lineNumber;
				current->terminal->tokenType=top->id;
				if(top->id==eps)
				{
					continue;
				}
				int lenn=0;
				while(token.strLexeme[lenn]!='\0')
				{
					current->terminal->strLexeme[lenn]=token.strLexeme[lenn];
					lenn++;
				}
				for(int i=lenn;i<LEXEME_MAX_LEN;i++)
				current->terminal->strLexeme[i]='\0';
				flag=1;
			}
		}
		else{
			nonTermID=parsetable[top->id-NTERMINAL_OFFSET][terminal].nonTerm;
			productionNo=parsetable[top->id-NTERMINAL_OFFSET][terminal].productionNum;
			if(nonTermID==-1 || productionNo==-1)
			{
				printf("\n\nPARSING ERROR AT LINE NO: %d\n",token.lineNumber);
				*error =1;
				token = getNextTokenFromDFA();
				if(token.tokenType==TK_ERROR)
				printf("\n\nERROR2:LINE NO: %d\n",token.lineNumber);
				while(token.tokenType!=TK_EOF && parsetable[top->id-NTERMINAL_OFFSET][token.tokenType].syn==-1)
				{
					token = getNextTokenFromDFA();
					if(token.tokenType==TK_ERROR)
					printf("\n\nERROR2:LINE NO: %d\n",token.lineNumber);
				}
				
				if(token.tokenType==TK_EOF)
					return;
				
				if(parsetable[top->id-NTERMINAL_OFFSET][token.tokenType].syn==1)	pop(stack);
				continue;
			}
			rule=grammar[nonTermID].prodRules[productionNo];
			ruleLen=rule[0];
			current->children = malloc(ruleLen*sizeof(treeNode));
			current->numChild = ruleLen;
			current->numChildAST = ruleLen;
			current->nonTerminal=top->id;
			
			for(int i=1;i<=ruleLen;i++)
			{
				if(rule[i]<NUM_TERMINALS)
				{
					current->children[i-1].terminal=malloc(sizeof(TOKEN));
					current->children[i-1].numChild=0 ;
					current->children[i-1].numChildAST=0;
					current->children[i-1].nonTerminal=-1;
					current->children[i-1].children=NULL;
					// current->children[i-1].tp = NULL;
				}
				else{
					current->children[i].nonTerminal=rule[i];
				}
			}
			pop(stack);
			for(int i=ruleLen;i>0;i--)
			{
				//if(rule[i]!=eps)
				push(stack,rule[i],&(current->children[i-1]));
			}
		}
	
	} while(token.tokenType!=TK_EOF);
	return;
}

void initializeParser(){
    grammar = (Grm)malloc(NUM_NTERMINALS*sizeof(NTERMINAL));

    firstSet = (FirstSet) malloc(NUM_NTERMINALS*sizeof(int*));
    
    followSet = (FollowSet)malloc(NUM_NTERMINALS*sizeof(int*));
    
	parsetable = (parseTable)malloc(NUM_NTERMINALS*sizeof(PTEntry*));

    for(int i=0; i<NUM_NTERMINALS; i++){
        firstSet[i] = (int*) malloc(NUM_TERMINALS*sizeof(int));
        followSet[i] = (int*) malloc(NUM_TERMINALS*sizeof(int));
		parsetable[i] = (PTEntry*)malloc(NUM_TERMINALS*sizeof(PTEntry));
    }

	root = (parseTree)malloc(sizeof(treeNode));
	
	lookuptable = makeParserHashTable(220);
    getGram("grammar.txt",grammar);
    getFirst("first.txt",firstSet);
    getFollow("follow.txt",followSet);
	createParseTable();
    
	return;
}

void getGram(char *fname, Grm g)
{
    int i=0,random;

	FILE* gf;
	gf=fopen(fname,"r");
	if(gf==NULL){
		return;
	}
	while(i<NUM_NTERMINALS)
	{
		fscanf(gf,"%d",&(g[i].rulesNum));
		g[i].prodRules=(int**)malloc((g[i].rulesNum)*sizeof(int*));
    		for (int j=0; j<g[i].rulesNum; j++) 
        	g[i].prodRules[j]= (int *)malloc((RULE_MAX_LEN+1) * sizeof(int));	
		
		int k,id;
		char temp[ID_MAX_SIZE];
		char tempo[ID_MAX_SIZE];
		
		for(int j=0;j<(g[i].rulesNum);j++)
		{
			fscanf(gf,"%s%d",temp,&k);
			g[i].prodRules[j][0]=k;
			for(int m=1;m<k+1;m++)
			{
				fscanf(gf,"%s",tempo);
				id=parseIdStr(tempo);
				g[i].prodRules[j][m]=id;
			}
		}
		i++;
	}

}

void getFirst(char *fname, FirstSet firstSet){

	int i=0;

	FILE* ff;
	ff=fopen(fname,"r");
	if(ff==NULL){
		return;
	}
	while(i<NUM_NTERMINALS)
	{
		int k,id;
		char temp[ID_MAX_SIZE];
		char tempo[ID_MAX_SIZE];

			fscanf(ff,"%s%d",temp,&k);
			for(int m=1;m<=k;m++)
			{
				fscanf(ff,"%s",tempo);
				id=parseIdStr(tempo);
				firstSet[i][id]=1;
			}
			
		i++;

	}
	return;
}

void getFollow(char *fname, FollowSet followSet){

	int i=0;

	FILE* ff;
	ff=fopen(fname,"r");
	if(ff==NULL){
		return;
	}
	while(i<NUM_NTERMINALS)
	{
		int k,id;
		char temp[ID_MAX_SIZE];
		char tempo[ID_MAX_SIZE];

			fscanf(ff,"%s%d",temp,&k);
			for(int m=1;m<=k;m++)
			{
				fscanf(ff,"%s",tempo);
				id=parseIdStr(tempo);
				followSet[i][id]=1;
			}
		i++;

	}
	return;
}

void firstString(int* b,int* firstRule,int index)
{
	int flg0=0;
	for(int i = 1; i <= index; i++)
	{	
		if(b[i] < NUM_TERMINALS)
		{
	       		firstRule[b[i]] = 1;
		        break;
		}
        	else{
      			int* temp = firstSet[b[i] - NTERMINAL_OFFSET];
      			if(temp[eps] == 0)
      			{
      				firstRule = add(firstRule, temp);
      				break;
      			}	
      			else{
      				firstRule = add(firstRule, temp);
      				if(i == index){flg0 = 1;}
      			}
		} 
	}
        if(flg0 == 1)
        firstRule[eps] = 1;
}

int* add(int* answer, int* addit){
	for(int i=0;i<=NUM_TERMINALS;i++)
	if(addit[i] && i!=eps) answer[i]=1;
	return answer;
}
