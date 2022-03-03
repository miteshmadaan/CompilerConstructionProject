#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lexer.h"
#include "parser.h"
#include "stack.h"
#include "parserHashTable.h"

bool check[NUM_NTERMINALS];

char* listTokens[] = {};

char* strRepId[] = {};
		  
int parseIdStr(char *idStr) 
{
	//return the id of string stored in hashtable
    parserKaTable* lookuptable = makeParserHashTable(220);
    return getTokenTypePHT(idStr,lookuptable);	
}

char *idRepr(int id) 
{
		if(id>=NTERMINAL_OFFSET && id<NTERMINAL_OFFSET+NUM_NTERMINALS)
		return strRepId[id-NTERMINAL_OFFSET+NUM_NTERMINALS-1];
		else if(id>=0 && id<=55)
		return strRepId[id];
		else
		return "";
}

char *tokenRepr(int id) 
{
	if(id >= 0 && id <=55)
		return listTokens[id];
	else
		return "";
}

void printParseTree(parseTree root)
{
	parseTree current;
	int class;
	for(int i=0;i<root->numChild;i++)
	{
		current=&(root->children[i]);
		if(!current)
		printf("NULL\n");
		if(current->numChildAST==0 && current->terminal->tokenType==eps)
		continue;
		if(current->numChildAST>0)
		{
			printf("-------\t\t");
			printf("-------\t\t");
			printf("-------\t\t");
			printf("-------\t\t");
		}
		else{
			printf("%s\t\t",current->terminal->strLexeme);
			printf("%d\t\t",current->terminal->lineNumber);
			printf("%s\t\t",tokenRepr(current->terminal->tokenType));
			if(current->terminal->tokenType==TK_NUM)
				printf("%d\t\t",current->terminal->intLexeme);
            else if(current->terminal->tokenType==TK_RNUM)
                printf("%0.5lf\t\t",current->terminal->reallexeme);
			else printf("-------\t\t");	
		}
		printf("%s\t\t",idRepr(root->nonTerminal));
		if(current->numChildAST==0)
		{
			printf("YES\t\t");
			printf("-------\t\t");
		}
		else{
			printf("NO\t\t");
			printf("%s\t\t",idRepr(current->nonTerminal));
		}
		printf("\n");
		printParseTree(current);
	}
}

void createParseTable(FirstSet firstSet,FollowSet followSet,Grm g,parseTable t)
{
    int ruleArray[RULE_MAX_LEN];
	int** rules;
	int* rule;
	int ruleNo=0;
	for(int i = 0; i < NUM_NTERMINALS; i++)
        for(int j = 0; j < NUM_TERMINALS; j++)
        {
        	t[i][j].nonTerm = -1;
        	t[i][j].productionNum= -1;
        	t[i][j].syn=-1;
        }	
	for(int i=0;i<NUM_NTERMINALS;i++)
	{
		NTERMINAL nonTerm=g[i];
		rules=nonTerm.prodRules;
		int* followRule=followSet[i];
		for(int j=0;j<nonTerm.rulesNum;j++)
		{
			rule=rules[j];
			int* firstRule=malloc(sizeof(int)*NUM_TERMINALS);
			int index=0,flag=0;
			for(int k=1;k<=rule[0];k++)
				ruleArray[index++]=rule[k];
			firstString(ruleArray,firstRule,index,firstSet);
			
			for(int k=0;k<NUM_TERMINALS;k++)
				if(firstSet[i][k])
					t[i][k].syn=0;	
					
			for(int k=0;k<NUM_TERMINALS;k++)
				if(followSet[i][k])
					t[i][k].syn=1;	
			
		        for(int k=0;k<NUM_TERMINALS;k++)
		        if(firstRule[k] && k!=eps)
		        {
		        	t[i][k].nonTerm = i;
        			t[i][k].productionNum= j;
        		}
		        if(firstRule[eps])
		        {
		        	for(int k=0;k<NUM_TERMINALS;k++)
		        	if(followRule[k] && k!=eps)
		        	{
					t[i][k].nonTerm = i;
					t[i][k].productionNum= j;
        			}
		        }
		        ruleNo++;
		}
	}
}

void parseInputSourceCode(FILE* sourceFile,parseTable t,Grm g,parseTree root,int* error)
{
	root->nonTerminal=program;
	root->numChild=2;
	parseTree leaf=NULL,parent=NULL,current;
	Stack stack=createStack();
	TOKEN token ;
	push(stack,TK_EOF,leaf);
	push(stack,program,root);
	int flag=1,terminal,nonTermID,productionNo,ruleLen;
	Key top;
	int* rule;
	do{
		if(flag)
		token = getNextTokenFromDFA();
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
		break ;
		flag=0 ;
		top=KeyAtTopElement(stack) ;
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
			nonTermID=t[top->id-NTERMINAL_OFFSET][terminal].nonTerm;
			productionNo=t[top->id-NTERMINAL_OFFSET][terminal].productionNum;
			if(nonTermID==-1 || productionNo==-1)
			{
				printf("\n\nPARSING ERROR AT LINE NO: %d\n",token.lineNumber);
				*error =1;
				token = getNextTokenFromDFA();
				if(token.tokenType==TK_ERROR)
				printf("\n\nERROR2:LINE NO: %d\n",token.lineNumber);
				while(token.tokenType!=TK_EOF && t[top->id-NTERMINAL_OFFSET][token.tokenType].syn==-1)
				{
					token = getNextTokenFromDFA();
					if(token.tokenType==TK_ERROR)
					printf("\n\nERROR2:LINE NO: %d\n",token.lineNumber);
				}
				
				if(token.tokenType==TK_EOF)
					return;
				
				if(t[top->id-NTERMINAL_OFFSET][token.tokenType].syn==1)
				pop(stack);
				continue;
			}
			rule=g[nonTermID].prodRules[productionNo];
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
}

void getGram(char *fname, Grm g)
{
     int i=0;
	
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

int* add(int* answer, int* addit){
	for(int i=0;i<=NUM_TERMINALS;i++)
	if(addit[i] && i!=eps) answer[i]=1;
	return answer;
}

int* calculateFirst(int produc,Grm g,FirstSet firstSet)
{
	int* answer=(int*)malloc(NUM_TERMINALS*sizeof(int));
	NTERMINAL nonTermSpec=g[produc];
int* tem1;
	
	int** array1=nonTermSpec.prodRules;
	int array1Size=nonTermSpec.rulesNum;
	for(int i=0;i<array1Size;i++)
	{
		if(array1[i][1]<NUM_TERMINALS)
		 	answer[array1[i][1]]=1;
		else{
			int m=1;
			while(m<=array1[i][0])
			{
				if(array1[i][m]<NUM_TERMINALS)
				{
					answer[array1[i][m]]=1;
					break;
				}
				if(!check[array1[i][m]-NTERMINAL_OFFSET])
				{
					tem1=calculateFirst(array1[i][m]-NTERMINAL_OFFSET,g,firstSet);
					(firstSet[array1[i][m]-NTERMINAL_OFFSET])=tem1;
					check[array1[i][m]-NTERMINAL_OFFSET]=1;
				}
				answer=add(answer,firstSet[array1[i][m]-NTERMINAL_OFFSET]);
				if(!tem1[eps])
				break;
				m++;
			}
			if(m>array1[i][0])
			answer[eps]=1;
		}
	}
	firstSet[produc]=answer;
	check[produc]=1;
	return answer;
}
		
void buildFirstSet(Grm g,FirstSet firstSet)
{
	int* nouse;
	for(int i=0;i<NUM_NTERMINALS;i++)
	if(!check[i])
	nouse=calculateFirst(i,g,firstSet);
}

//-----------------------------------------------------------------------------------------------------

void firstString(int* b,int* firstRule,int index,FirstSet firstSet)
{
	int flg0=0;
	for(int i = 0; i < index; i++)
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
      				if(i == index-1){flg0 = 1;}
      			}
		} 
	}
        if(flg0 == 1)
        firstRule[eps] = 1;
}

void add2(int* answer,int* add0,int* flg0)
{
	for(int i=0;i<NUM_TERMINALS;i++)
	{
		if(add0[i] && i!=eps)
		{
			if(!answer[i])
			*flg0=1;
			answer[i]=1;
		}
	}
}

void findFollow(int nTerminalNum, int prodNum, Grm g, FollowSet followSet, FirstSet firstSet,int* flg2)
{
	int *nextFirst,*temp,*temp2,*tem3;
int flg0=0,flg3=0;
int** rules=g[nTerminalNum].prodRules;
	int* rule=rules[prodNum];
	
	int ruleSize=rule[0];
	
	for(int i=1;i<=ruleSize;i++)
	{
		flg0=0;
		if(rule[i]<NUM_TERMINALS)
		continue;
		int* firstRule=malloc(sizeof(int)*NUM_TERMINALS);
		if(i==ruleSize)
		flg0=1;
		else
		{
			flg3=0;
			for(int j=0;j<NUM_TERMINALS;j++)
			firstRule[j]=0;
			int b[RULE_MAX_LEN];
int index=0;
			
			for(int k=i+1;k<=ruleSize;k++)
			b[index++]=rule[k];
			firstString(b,firstRule,index,firstSet);
			temp=followSet[rule[i]-NTERMINAL_OFFSET];
			add2(temp,firstRule,&flg3);
			if(!*flg2) *flg2=flg3;
			followSet[rule[i]-NTERMINAL_OFFSET]=temp;
		}
		if(firstRule[eps] || flg0)
		{
			for(int j=0;j<NUM_TERMINALS;j++)
			{
				tem3=followSet[rule[i]-NTERMINAL_OFFSET];
				if(followSet[nTerminalNum][j])
				{
					if(!tem3[j])
					{
						*flg2=1;
					}
					tem3[j]=1;
				}
			}
		}
	}
}
		
void getFollowSets(Grm g, FollowSet follow0, FirstSet first0){
	for(int i=0;i<NUM_NTERMINALS;i++)
	{
		follow0[i]=malloc(sizeof(int)*NUM_TERMINALS);
		for(int j=0;j<NUM_TERMINALS;j++)
		follow0[i][j]=0;
	}

	follow0[0][TK_EOF] = 1;
	int flg0;
	while(1){
		flg0=0;
		for(int i = 0; i < NUM_NTERMINALS; i++){
			for(int j = 0; j < g[i].rulesNum; j++){
				findFollow(i, j, g, follow0, first0,&flg0);
			}
		} 
		if(flg0==0) break;
	}        
}