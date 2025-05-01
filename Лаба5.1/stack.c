/* Лабораторная работа №5. ПОНЯТИЕ СТЕКА. ОПЕРАЦИИ НАД СТЕКОМ
   Реализация операций над стеком
   Фамилия студента: Волкович Ника Ивановна
   Дата написания: 25.04.2025
*/

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
        return 0; 
    }
    return stack->data[stack->top--];
}

void displayStack(Stack* stack) {
    if (stack->top == -1) {
        printf("Стек пуст.\n");
        return;
    }
    printf("Содержимое стека (сверху вниз):\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d\n", stack->data[i]);
    }
}

int findMax(Stack* stack) {
    if (stack->top == -1) {
        printf("Ошибка: стек пуст.\n");
        return -1; 
    }
    int max = stack->data[0];
    for (int i = 1; i <= stack->top; i++) {
        if (stack->data[i] > max) {
            max = stack->data[i];
        }
    }
    return max;
}
