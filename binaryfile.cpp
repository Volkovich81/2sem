#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void write_numbers_to_file(const char* filename, int count) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Ошибка открытия файла для записи");
        return;
    }

    int number = 0;
    for (int i = 0; i < count; i++) {
        printf("Введите число %d: ", i + 1);
        while (scanf_s("%d", &number) != 1 || getchar() != '\n') {
            printf("Ошибка: введите целое число: ");
            while (getchar() != '\n'); // Очистка буфера
        }
        fwrite(&number, sizeof(int), 1, file);
    }
    fclose(file);
}

void read_numbers_from_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка открытия файла для чтения");
        return;
    }

    fseek(file, 0, SEEK_SET);
    int number = 0;
    printf("Данные из файла:\n");
    while (fread(&number, sizeof(int), 1, file) == 1) {
        printf("%d ", number);
    }
    printf("\n");
    fclose(file);
}

int count_less_than(const char* filename, int threshold) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка открытия файла для чтения");
        return -1;
    }

    int number, count = 0;
    while (fread(&number, sizeof(int), 1, file) == 1) {
        if (number < threshold) {
            count++;
        }
    }
    fclose(file);
    return count;
}

void delete_less_than(const char* filename, int threshold) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка открытия файла для чтения");
        return;
    }

    int number;
    long pos = 0, write_pos = 0;
    FILE* temp_file = fopen("temp.bin", "wb"); // Временный файл для записи

    while (fread(&number, sizeof(int), 1, file) == 1) {
        if (number >= threshold) {
            fwrite(&number, sizeof(int), 1, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(filename); // Удаляем старый файл
    rename("temp.bin", filename); // Переименовываем временный файл
}

void sort_descending(const char* filename) {
    FILE* file = fopen(filename, "rb+");
    if (file == NULL) {
        perror("Ошибка открытия файла для чтения и записи");
        return;
    }

    int number;
    int count = 0;

    // Подсчет элементов
    while (fread(&number, sizeof(int), 1, file) == 1) {
        count++;
    }
    fseek(file, 0, SEEK_SET);

    // Сортировка пузырьком
    int* numbers = malloc(count * sizeof(int));
    if (numbers == NULL) {
        perror("Ошибка выделения памяти");
        fclose(file);
        return;
    }

    fread(numbers, sizeof(int), count, file);
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (numbers[j] < numbers[j + 1]) {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }

    fseek(file, 0, SEEK_SET);
    fwrite(numbers, sizeof(int), count, file);
    free(numbers);
    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    setlocale(LC_ALL, "Rus");

    int count = 0;
    printf("Введите количество целых чисел: ");
    while (scanf_s("%d", &count) != 1 || getchar() != '\n') {
        printf("Ошибка: введите целое число: ");
        while (getchar() != '\n'); // Очистка буфера
    }

    write_numbers_to_file(argv[1], count);
    read_numbers_from_file(argv[1]);

    int threshold = 0;
    printf("Введите пороговое значение: ");
    while (scanf_s("%d", &threshold) != 1 || getchar() != '\n') {
        printf("Ошибка: введите целое число: ");
        while (getchar() != '\n'); // Очистка буфера
    }

    int less_count = count_less_than(argv[1], threshold);
    printf("Количество элементов меньше %d: %d\n", threshold, less_count);

    delete_less_than(argv[1], threshold);
    printf("После удаления элементов меньше %d:\n", threshold);
    read_numbers_from_file(argv[1]);

    sort_descending(argv[1]);
    printf("После сортировки по убыванию:\n");
    read_numbers_from_file(argv[1]);

    return 0;
}