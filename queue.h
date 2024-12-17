#ifndef QUEUE_H
#define QUEUE_H

typedef struct qNode {
char* nData;
struct qNode* pNext;
} qNode;

typedef struct Queue {
qNode* qHead;
qNode* qTail;
} Queue;

// Function prototypes
Queue* createQueue();
void enqueue(Queue* queue, char* nData);
char* dequeue(Queue* queue, int* error);
int queueIsEmpty(Queue* queue);
void freeQueue(Queue* queue);

#endif // QUEUE_H