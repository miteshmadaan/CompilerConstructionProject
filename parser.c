#include "parser.h"


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
		int* followRule=followSet[i].first;
		for(int j=0;j<nonTerm.rulesNum;j++)
		{
			rule=rules[j];
			int* firstRule=malloc(sizeof(int)*NUM_TERMINALS);
			int index=0,flag=0;
			for(int k=1;k<=rule[0];k++)
				ruleArray[index++]=rule[k];
			firstString(ruleArray,firstRule,index,firstSet);
			
			for(int k=0;k<NUM_TERMINALS;k++)
				if(firstSet[i].first[k])
					t[i][k].syn=0;	
					
			for(int k=0;k<NUM_TERMINALS;k++)
				if(followSet[i].first[k])
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