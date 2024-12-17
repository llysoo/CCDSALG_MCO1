#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"
#include "queue.h"
#include "converter.h"

int operatorPrecedence(char *opr) {
    if (strcmp(opr, "||") == 0) return 1;
    if (strcmp(opr, "&&") == 0) return 2;
    if (strcmp(opr, "==") == 0 || strcmp(opr, "!=") == 0) return 3;
    if (strcmp(opr, ">") == 0 || strcmp(opr, "<") == 0 || strcmp(opr, ">=") == 0 || strcmp(opr, "<=") == 0) return 4;
    if (strcmp(opr, "+") == 0 || strcmp(opr, "-") == 0) return 5;
    if (strcmp(opr, "*") == 0 || strcmp(opr, "/") == 0 || strcmp(opr, "%") == 0) return 6;
    if (strcmp(opr, "^") == 0) return 7;
    if (strcmp(opr, "!") == 0) return 8;
    return -1;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' ||
           ch == '>' || ch == '<' || ch == '=' || ch == '!' || ch == '&' || ch == '|';
}

void convertInfix(char* expression, Queue* outputQueue) {
    Stack* operatorStack = createStack();
    int i = 0;
    char numberBuffer[256];
    int bufferIndex = 0;
    int wasOperator = 1; // Start as if the previous character was an operator

    while (expression[i]) {
        if (isdigit(expression[i]) || (expression[i] == '-' && wasOperator)) {
            if (expression[i] == '-') {
                numberBuffer[bufferIndex++] = expression[i++];
            }
            while (isdigit(expression[i]) || expression[i] == '.') {
                numberBuffer[bufferIndex++] = expression[i++];
            }
            numberBuffer[bufferIndex] = '\0';
            enqueue(outputQueue, strdup(numberBuffer));
            bufferIndex = 0;
            wasOperator = 0;
        } else if (expression[i] == '(') {
            pushStack(operatorStack, strdup("("));
            wasOperator = 1;
            i++;
        } else if (expression[i] == ')') {
            while (!stackIsEmpty(operatorStack) && strcmp(stackTop(operatorStack), "(") != 0) {
                enqueue(outputQueue, popStack(operatorStack));
            }
            if (!stackIsEmpty(operatorStack)) {
                char* temp = popStack(operatorStack); // Remove '('
                free(temp);
            }
            wasOperator = 0;
            i++;
        } else if (isOperator(expression[i])) {
            char opr[3] = {expression[i], '\0', '\0'};
            if (expression[i] == '&' || expression[i] == '|' || expression[i] == '=') {
                if (expression[i + 1] == expression[i] || expression[i + 1] == '=') {
                    opr[1] = expression[i + 1];
                    i++;
                }
            } else if (expression[i] == '!' || expression[i] == '<' || expression[i] == '>') {
                if (expression[i + 1] == '=') {
                    opr[1] = expression[i + 1];
                    i++;
                }
            }

            while (!stackIsEmpty(operatorStack) && operatorPrecedence(stackTop(operatorStack)) >= operatorPrecedence(opr)) {
                enqueue(outputQueue, popStack(operatorStack));
            }
            pushStack(operatorStack, strdup(opr));
            wasOperator = 1;
            i++;
        } else {
            i++;
        }
    }

    while (!stackIsEmpty(operatorStack)) {
        char* op = popStack(operatorStack);
        if (strcmp(op, "(") != 0) { // Ignore unmatched opening parentheses
            enqueue(outputQueue, op);
        } else {
            free(op); // Clean up memory for unmatched opening parenthesis
        }
    }

    freeStack(operatorStack);
}
