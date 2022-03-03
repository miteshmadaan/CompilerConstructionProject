#include "defForParser.h"
typedef struct key{
	int id;
	parseTree parent;
} * Key;

typedef struct stackElement{
	Key k;
	stackElement next;
}* stackElement;

typedef struct stack{
	int count;
	stackElement head;
	stackElement tail;
}* Stack;


Stack createStack();
void insertElementAtBottom(Stack s, stackElement e);
void push(Stack s, int id, parseTree pt);
void pop(Stack s);
Key KeyAtTopElement(Stack s);
stackElement createElement(Key k);
Key createKey(int id, parseTree pt);