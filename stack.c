/* 
* Mitesh Madaan             2018B5A70901P
* Shreyas Das               2019A7PS0111P
* Rahul Taak                2019A7PS0012P
* Manik Chopra              2019A7PS0144P
* Muppirisetty R Bharadwaj  2019A7PS0025P
*/
#include "stack.h"
#include <stdlib.h>

Stack createStack(){
	Stack parserKaStack = malloc(sizeof( struct stack));
	parserKaStack->tail = NULL;
	parserKaStack->head = NULL;
	parserKaStack->count = 0;
	return parserKaStack;
}

void insertElementAtBottom(Stack parserKaStack, StackElement e){
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

		
StackElement createElement(Key k)
{
	StackElement a = malloc(sizeof(struct stackElement));
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
	Key key = createKey(id, pt);
	StackElement e = createElement(key);
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
		StackElement enext = parserKaStack->head->next;
		StackElement curr = parserKaStack->head;
        curr->next = NULL;
		parserKaStack->head = enext;
        parserKaStack->count--;
		free(curr);
	}
	else if(parserKaStack->count == 1){
		StackElement curr = parserKaStack->head;
        parserKaStack->tail = NULL;
		parserKaStack->head = NULL;
        parserKaStack->count = 0;
		free(curr);
		
	}
	
}	