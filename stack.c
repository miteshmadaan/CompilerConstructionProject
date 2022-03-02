#include "stack.h"


Stack createStack(){
	Stack parserKaStack = malloc(sizeof( struct stack));
	parserKaStack->tail = NULL;
	parserKaStack->head = NULL;
	parserKaStack->count = 0;
	return parserKaStack;
}

void insertElementAtBottom(Stack parserKaStack, stackElement e){
	if(parserKaStack->count == 0){
		e->next = NULL;
		parserKaStack->head = e;
		parserKaStack->tail=e;
		parserKaStack->count++;
	}
	else{
		parserKaStack->tail->next = e;
		parserKaStack->tail=e;
		parserKaStack->count++;
		e->next = NULL;
	}
}


Key KeyAtTopElement(Stack parserKaStack){
	if(parserKaStack->head != NULL){return parserKaStack->head->k;}
	else{
		printf("Empty Stack\n");
		return NULL;
	}
}

		
stackElement createElement(Key k)
{
	stackElement a = malloc(sizeof(struct stackElement));
	a->k = k;
	a->next=NULL;
	return a;

}		   

Key createKey(int id, parseTree pt){
	Key k = malloc(sizeof(struct key));
	(k)->id = id;
	(k)->parent = pt;
	return k;
}
		
void push(Stack parserKaStack, int id, parseTree pt){
	Key key = newKey(id, pt);
	stackElement e = newElement(key);
	if(parserKaStack->count == 0){
		parserKaStack->head = e;
		parserKaStack->tail=e;
		e->next = NULL;
		parserKaStack->count++;
	}
	else{
		e->next = parserKaStack->head;
		parserKaStack->head= e;
		parserKaStack->count++;
	}
}

void pop(Stack parserKaStack){
	if(parserKaStack->count == 0){
		printf("Stack is empty\n");
	}
    else if(parserKaStack->count > 1){
		stackElement enext = parserKaStack->head->next;
		stackElement curr = parserKaStack->head;
        curr->next = NULL;
		parserKaStack->head = enext;
        parserKaStack->count--;
		free(curr);
	}
	else if(parserKaStack->count == 1){
		stackElement curr = parserKaStack->head;
        parserKaStack->tail = NULL;
		parserKaStack->head = NULL;
        parserKaStack->count = 0;
		free(curr);
		
	}
	
}	