#include <stdlib.h>
#include <stdio.h>
#include "include/main.h"

/*Функиця для очитски экрана*/
void cls();

/*Вывод меню в консоль*/
void menu();

/*Возвращает введённое целочисленное значение*/
int input_int(char *msg);

int entry(Folder *folder);


int main() {
    Folder folder = {{{1, "game", "exe", 500, {12, 12, 2012}}, 
                     {2, "secret", "txt", 23403, {16, 11, 2023}},
                     {3, "my birthday", "jpeg", 321, {20, 8, 2005}},
                     {4, "Отчёт по лабараторной работе №7", "docx", 110, {25, 3, 2024}},
                     {5, "main", "c", 8, {1, 2, 2024}}},
                      5,
                      24342};

#ifdef _WIN
    system("chcp 65001 > NUL");
#endif
    while(entry(&folder));
    
#ifdef _WIN
    system("pause");
#endif

    return 0;
}


void cls() {
#ifdef _WIN
    system("cls");
#elif defined __linux__
    system("clear");
#endif
}

void menu() {
    printf("1. Создать новый файл\n");
    printf("2. Вывод всех файлов на экран\n");
    printf("3. Вывод файла на экран по индексу\n");
    printf("4. Подсчёт всех элементов в списке\n");
    printf("5. Сортировка файлов\n");
    printf("6. Вставка файла в любое место\n");
    printf("7. Удаление файла\n");
    printf("0. Выход из программы\n");
}

int input_int(char *msg) {
    double buff = 0;
    char ch = '\0';
    int flag = 1;

    while (flag) {

        if (msg) {
            printf("%s", msg);
        }
        if (scanf("%lf", &buff) != 1 || buff - (int)buff != 0) {
            print_err("Некорректный ввод, попробуй снова");
            while ((ch = getchar()) != '\n' && ch != EOF);
        } else {
            flag = 0;
        }
    }  

    return (int)buff;
}

int entry(Folder *folder) {
    int code = 1, choise = 0, value = 0;
    int error_code = 0;
    // char ch = '\0';

    menu();
    choise = input_int("Выберите пункт: ");
    cls();

    switch (choise) {
    case 0:
        printf("Выход из программы...\n");
        code = 0;
        break;
    case 1:
        error_code = input(folder, NULL);
        print_err(get_error(error_code));
        break;
    case 2:
        if (print_folder(folder)) {
            print_err("Пустая папка");
        }
        break;
    case 3:
        value = input_int("Введите индекс для вывода файла: ");
        if (print_file(folder->file, value)) {
            print_err("Файл с таким индексом отстутсвует в папке");
        }
        break;
    case 4:
        printf("Размер всех файлов в папке: %.2lf\n", folder->size);
        break;
    case 5:
        printf("Сортировка\n");
        break;
    case 6:
        value = input_int("Введите индекс для вставки: ");
        error_code = input(folder, &value);
        print_err(get_error(error_code));
        break;
    case 7:
        value = input_int("Введите индекс для удаления: ");
        error_code = delete_file(folder, value);
        print_err(get_error(error_code));
        break;
    default:
        print_err("Такого пункта меню нет, попробуй снова");
        break;
    }

    //printf("Press enter to countinue...\n");
    // while ((ch = getchar()) != '\n' && ch != EOF);
    // getchar();
    // cls();

    return code;
}