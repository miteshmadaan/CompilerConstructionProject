#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexer.h"
#include "parser.h"
// #include "utils.h"
#include "stack.h"

bool check[NUM_NTERMINALS];

void printParseTree(parseTree root)
{
	parseTree current;
	int class;
	for(int i=0;i<root->numChild;i++)
	{
		current=&(root->children[i]);
		if(!current)
		printf("NULL\n");
		if(current->numChildAST==0 && current->terminal->tokenType==58)
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
			printf("%d\t\t",tokenRepr(current->terminal->tokenType));
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
		        if(firstRule[k] && k!=58)
		        {
		        	t[i][k].nonTerm = i;
        			t[i][k].productionNum= j;
        		}
		        if(firstRule[58])
		        {
		        	for(int k=0;k<NUM_TERMINALS;k++)
		        	if(followRule[k] && k!=58)
		        	{
					t[i][k].nonTerm = i;
					t[i][k].productionNum= j;
        			}
		        }
		        ruleNo++;
		}
	}
}

/*
void parseInputSourceCode(FILE* sourceFile,parseTable t,Grm g,parseTree root,int* error);

void parseInputSourceCode(FILE* sourceFile,Table t,Grammar g,parseTree root,int* error)
{
	root->nonTerminal=program;
	root->numChild=2;
	parseTree leaf=NULL,parent=NULL,current;
	Stack stack=newStack();
	tokenInfo token ;
	push(stack,TK_EOF,leaf);
	push(stack,program,root);
	int flag=1,terminal,nonTermID,productionNo,ruleLen;
	Key top;
	int* rule;
	do{
		if(flag)
		getNextToken(sourceFile,&token);
		if(token.tokenType==TK_ERROR)
		{
			printf("\n\nLEXICAL ERROR AT LINE NO: %lld   %s\n",token.lineNum,token.lexeme);
			//if(top1(stack)->parent->id < NO_OF_TERMINALS)
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
		top=top1(stack) ;
		terminal=token.tokenType ;
		current=top->parent;
		if(top->id<NO_OF_TERMINALS)
		{
			if(top->id!=terminal && top->id!=eps)
			{
				printf("\n\nPARSER ERROR AT LINE NO: %lld The token %s for lexeme %s does not match with the expected token %s\n",token.lineNum,tokenRepr(terminal),token.lexeme,tokenRepr(top->id));
				*error=1;
				pop(stack);
			}
			else{
				pop(stack);
				current->terminal->lineNum=token.lineNum;
				current->terminal->tokenType=top->id;
				if(top->id==eps)
				{
					continue;
				}
				int lenn=0;
				while(token.lexeme[lenn]!='\0')
				{
					current->terminal->lexeme[lenn]=token.lexeme[lenn];
					lenn++;
				}
				for(int i=lenn;i<MAX_LEXEME_SIZE;i++)
				current->terminal->lexeme[i]='\0';
				flag=1;
			}
		}
		else{
			nonTermID=t[top->id-NONTERMINAL_OFFSET][terminal].nonTerm;
			productionNo=t[top->id-NONTERMINAL_OFFSET][terminal].productionNum;
			if(nonTermID==-1 || productionNo==-1)
			{
				printf("\n\nPARSING ERROR AT LINE NO: %lld\n",token.lineNum);
				*error =1;
				getNextToken(sourceFile,&token);
				if(token.tokenType==TK_ERROR)
				printf("\n\nERROR2:LINE NO: %lld\n",token.lineNum);
				while(token.tokenType!=TK_EOF && t[top->id-NONTERMINAL_OFFSET][token.tokenType].syn==-1)
				{
					getNextToken(sourceFile,&token);
					if(token.tokenType==TK_ERROR)
					printf("\n\nERROR2:LINE NO: %lld\n",token.lineNum);
				}
				
				if(token.tokenType==TK_EOF)
					return;
				
				if(t[top->id-NONTERMINAL_OFFSET][token.tokenType].syn==1)
				pop(stack);
				continue;
			}
			rule=g[nonTermID].rules[productionNo];
			ruleLen=rule[0];
			current->children = malloc(ruleLen*sizeof(parsetree));
			current->numChild = ruleLen;
			current->numChildAST = ruleLen;
			current->nonTerminal=top->id;
			
			for(int i=1;i<=ruleLen;i++)
			{
				if(rule[i]<NO_OF_TERMINALS)
				{
					current->children[i-1].terminal=malloc(sizeof(tokenInfo));
					current->children[i-1].numChild=0 ;
					current->children[i-1].numChildAST=0;
					current->children[i-1].nonTerminal=-1;
					current->children[i-1].children=NULL;
					current->children[i-1].tp = NULL;
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
*/