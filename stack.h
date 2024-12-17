#ifndef STACK_H
#define STACK_H

typedef struct Node {
char* nData;
struct Node* pNext;
} Node;

typedef struct Stack {
Node* sTop;
} Stack;

// Function prototypes
Stack* createStack();
void pushStack(Stack* stack, char* nData);
char* popStack(Stack* stack);
char* stackTop(Stack* stack);
int stackIsEmpty(Stack* stack);
void freeStack(Stack* stack);

#endif // STACK_H