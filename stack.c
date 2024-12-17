#include <stdlib.h>
#include <string.h>
#include "stack.h"

Stack* createStack() {
Stack* stack = (Stack*)malloc(sizeof(Stack));
stack->sTop = NULL;
return stack;
}

void pushStack(Stack* stack, char* nData) {
Node* newNode = (Node*)malloc(sizeof(Node));
newNode->nData = strdup(nData);
newNode->pNext = stack->sTop;
stack->sTop = newNode;
}

char* popStack(Stack* stack) {
if (stackIsEmpty(stack)) {
return NULL;
}
Node* temp = stack->sTop;
char* nData = temp->nData;
stack->sTop = stack->sTop->pNext;
free(temp);
return nData;
}

char* stackTop(Stack* stack) {
if (stackIsEmpty(stack)) {
return NULL;
}
return stack->sTop->nData;
}

int stackIsEmpty(Stack* stack) {
return stack->sTop == NULL;
}

void freeStack(Stack* stack) {
while (!stackIsEmpty(stack)) {
free(popStack(stack));
}
free(stack);
}