#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "evalPostfix.h"
#include "converter.h"

int main() {
    char expression[256];
    Queue* postfixQueue = createQueue();
    int running = 1;

    while (running) {
        if (fgets(expression, sizeof(expression), stdin) != NULL) {
            expression[strcspn(expression, "\n")] = 0;  // Remove newline character

            if (strcmp(expression, "QUIT") == 0 || strcmp(expression, "quit") == 0) {
                running = 0;
            } else {
                convertInfix(expression, postfixQueue);
                printf("Postfix: ");
                int flag = 0;
                Queue* tempQueue = createQueue();
                while (!queueIsEmpty(postfixQueue)) {
                    char* token = dequeue(postfixQueue, &flag);
                    enqueue(tempQueue, strdup(token));  // Use strdup to duplicate the token
                    printf("%s ", token);
                    free(token);  // Free the token after use
                }
                printf("\n");

                int errorFlag = 0;
                int result = evaluatePostfix(tempQueue, &errorFlag);
                if (!errorFlag) {
                    printf("Result: %d\n", result);
                } else {
                    printf("Error in evaluating the expression.\n");
                }
                freeQueue(tempQueue);
            }
        } else {
            running = 0;  // End the loop if input fails
        }
    }

    freeQueue(postfixQueue);
    return 0;
}
