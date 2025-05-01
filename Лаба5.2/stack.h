#pragma once
/* Лабораторная работа №5. ПОНЯТИЕ СТЕКА. ОПЕРАЦИИ НАД СТЕКОМ
   Объявления функций и структуры для работы со стеком
   Фамилия студента: Волкович Ника Ивановна
   Дата написания: 30.04.2025
*/

#ifndef STACK_H
#define STACK_H


typedef struct {
    int* data;       
    int top;         
    int maxSize;     
} Stack;

void initStack(Stack* stack, int size);
int push(Stack* stack, int value);
int pop(Stack* stack);
void displayStack(Stack* stack);
void mergeStacks(Stack* stack1, Stack* stack2, Stack* stack3);
int inputInteger();

#endif
