/* 
* Group No. 46
* Mitesh Madaan             2018B5A70901P
* Shreyas Das               2019A7PS0111P
* Rahul Taak                2019A7PS0012P
* Manik Chopra              2019A7PS0144P
* Muppirisetty R Bharadwaj  2019A7PS0025P
*/
#include "parserDef.h"
typedef struct key{
	int id;
	parseTree parent;
}key;
typedef key* Key;

typedef struct stackElement{
	Key k;
	struct stackElement* next;
}stackElement;
typedef stackElement* StackElement;

typedef struct stack{
	int count;
	stackElement* head;
	stackElement* tail;
}stack;
typedef stack* Stack;

Stack createStack();
void insertElementAtBottom(Stack s, StackElement e);
void push(Stack s, int id, parseTree pt);
void pop(Stack s);
Key KeyAtTopElement(Stack s);
StackElement createElement(Key k);
Key createKey(int id, parseTree pt);