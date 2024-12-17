#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "queue.h"
#include "evalPostfix.h"

int evaluatePostfix(Queue* postfixQueue, int* errorFlag) {
    Stack* operands = createStack();
    *errorFlag = 0;  // Initialize error flag

    while (!queueIsEmpty(postfixQueue)) {
        int dequeueError = 0;
        char* token = dequeue(postfixQueue, &dequeueError);
        if (token == NULL) {
            freeStack(operands);
            *errorFlag = 1;  // Set error flag
            return 0;
        }

        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            pushStack(operands, token);
        } else {
            int result = 0;
            if (strcmp(token, "!") == 0) {  // Unary operator
                int val = atoi(popStack(operands));
                result = !val;
            } else {  // Binary operators
                int val1 = atoi(popStack(operands));
                int val2 = atoi(popStack(operands));
                
                if (strcmp(token, "+") == 0) result = val2 + val1;
                else if (strcmp(token, "-") == 0) result = val2 - val1;
                else if (strcmp(token, "*") == 0) result = val2 * val1;
                else if (strcmp(token, "/") == 0) {
                    if (val1 == 0) {
                        printf("Division by zero error!\n");
                        free(token);
                        freeStack(operands);
                        *errorFlag = 1;  // Set error flag
                        return 0;
                    }
                    result = val2 / val1;
                } else if (strcmp(token, "%") == 0) result = val2 % val1;
                else if (strcmp(token, "^") == 0) result = (int)pow(val2, val1);
                else if (strcmp(token, ">") == 0) result = val2 > val1;
                else if (strcmp(token, "<") == 0) result = val2 < val1;
                else if (strcmp(token, ">=") == 0) result = val2 >= val1;
                else if (strcmp(token, "<=") == 0) result = val2 <= val1;
                else if (strcmp(token, "==") == 0) result = val2 == val1;
                else if (strcmp(token, "!=") == 0) result = val2 != val1;
                else if (strcmp(token, "&&") == 0) result = val2 && val1;
                else if (strcmp(token, "||") == 0) result = val2 || val1;
                else {
                    free(token);
                    freeStack(operands);
                    *errorFlag = 1;  // Set error flag
                    return 0;
                }
            }

            char resultStr[20];
            sprintf(resultStr, "%d", result);
            pushStack(operands, strdup(resultStr));
        }
        free(token);
    }

    int finalResult = atoi(popStack(operands));
    freeStack(operands);
    return finalResult;
}
