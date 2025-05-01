#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <locale.h>


void initStack(Stack* stack, int size) {
    stack->data = (int*)malloc(size * sizeof(int));
    stack->top = -1;
    stack->maxSize = size;
}

int push(Stack* stack, int value) {
    if (stack->top == stack->maxSize - 1) {
        return 0; 
    }
    stack->data[++stack->top] = value;
    return 1;
}

int pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Ошибка: стек пуст.\n");
        return 0;
    }
    return stack->data[stack->top--];
}

void displayStack(Stack* stack) {
    if (stack->top == -1) {
        printf("Стек пуст.\n");
        return;
    }
    for (int i = stack->top; i >= 0; i--) {
        printf("%d\n", stack->data[i]);
    }
}

void mergeStacks(Stack* stack1, Stack* stack2, Stack* stack3) {
    while (stack1->top != -1 || stack2->top != -1) {
        if (stack1->top == -1) {
            push(stack3, pop(stack2));
        }
        else if (stack2->top == -1) {
            push(stack3, pop(stack1));
        }
        else if (stack1->data[stack1->top] < stack2->data[stack2->top]) {
            push(stack3, pop(stack1));
        }
        else {
            push(stack3, pop(stack2));
        }
    }
}

int inputInteger() {
    char buffer[100];
    int value;

    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        char* endptr;
        value = strtol(buffer, &endptr, 10);

        if (*endptr != '\0') {
            printf("Ошибка: ввод завершён. Переход к следующему шагу.\n");
            exit(0);
        }

        return value;
    }
}
