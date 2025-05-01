/* Лабораторная работа №5. ПОНЯТИЕ СТЕКА. ОПЕРАЦИИ НАД СТЕКОМ
   Задание: Создать два стека для целых чисел (включая отрицательные).
   Первый стек – ввод по убыванию, второй стек – ввод по убыванию.
   Без сортировок и переворачивания исходных стеков
   сформировать третий стек, упорядоченный по возрастанию.
   Фамилия студента: Волкович Ника Ивановна
   Дата написания: 30.04.2025
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Rus");
    int maxSize;

    printf("Введите максимальный размер стеков: ");
    while ((maxSize = inputInteger()) <= 0) {
        printf("Ошибка: максимальный размер должен быть положительным числом.\n");
    }

    Stack stack1, stack2, stack3;
    initStack(&stack1, maxSize);
    initStack(&stack2, maxSize);
    initStack(&stack3, maxSize * 2); 

    printf("Введите числа для первого стека (по убыванию, без повторов, любое нечисловое значение для завершения):\n");
    while (stack1.top < stack1.maxSize - 1) {
        int value = inputInteger();
        if (!push(&stack1, value)) {
            printf("Первый стек заполнен! Теперь вводим второй стек.\n");
            break; 
        }
    }
   
    printf("Введите числа для второго стека (по убыванию, без повторов, любое нечисловое значение для завершения):\n");
    while (stack2.top < stack2.maxSize - 1) {
        int value = inputInteger();
        if (!push(&stack2, value)) {
            printf("Второй стек заполнен! Формируем третий стек.\n");
            break; 
        }
    }

    mergeStacks(&stack1, &stack2, &stack3);

    printf("\nСодержимое третьего стека (по возрастанию, включая отрицательные числа):\n");
    displayStack(&stack3);

    free(stack1.data);
    free(stack2.data);
    free(stack3.data);

    return 0;
}
