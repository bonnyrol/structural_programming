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
    // Folder folder = {{{1, "game", "exe", 5300, {12, 12, 2012}}, 
    //                  {2, "secret", "txt", 23403, {16, 11, 2023}},
    //                  {3, "my birthday", "jpeg", 321, {20, 8, 2005}},
    //                  {4, "test", "docx", 110, {25, 3, 2024}},
    //                  {5, "main", "c", 8, {1, 2, 2024}}},
    //                   5,
    //                   get_sizes(&folder)};
    Folder folder = {0};

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
    printf("2. Вставка файла в любое место\n");
    printf("3. Сортировка файлов\n");
    printf("4. Удаление файла\n");
    printf("5. Сохранить данные в файл\n");
    printf("6. Загрузить из файла\n");
    printf("7. Очистить данные\n");
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
    char buff[NAME_SIZE + EXT_SIZE + 1];
    mode a = 0; // name
    sorting b = 0; // asc

    print_folder(folder);
    menu();
    choise = input_int("Выберите пункт: ");
    cls();
    print_folder(folder);

    switch (choise) {
    case 0:
        printf("Выход из программы...\n");
        free(folder->file);
        code = 0;
        break;
    case 1:
        error_code = input(folder, NULL);
        print_err(get_error(error_code));
        break;
    case 2:
        value = input_int("Введите индекс для вставки: ");
        error_code = input(folder, &value);
        print_err(get_error(error_code));
        break;
    case 3:
        a = input_int("Введите параметры для сортитровки.\n\
        0) Имя файла\n\
        1) Расширение файла\n\
        2) Размер\n\
        3) Дата создания\n\
        Выбор:  ");
        b = input_int("Как сортировать?.\n\
        0) По возрастанию\n\
        1) По убыванию\n\
        Выбор: ");
        sort(folder, a, b);
        break;
    case 4:
        value = input_int("Введите индекс для удаления: ");
        error_code = delete_file(folder, value);
        print_err(get_error(error_code));
        break;
    case 5:
        printf("Введите название файла для сохранения: ");
        scanf("%s", buff);
        error_code = save_to_file(folder, buff);
        print_err(get_error(error_code));
        break;
    case 6:
        printf("Введите названия файла для загрузки данных: ");
        scanf("%s", buff);
        error_code = load_from_file(folder, buff);
        print_err(get_error(error_code));
        break;
    case 7:
        clear_all(folder);
        break;

    default:
        print_err("Такого пункта меню нет, попробуй снова");
        break;
    }
    

    // char ch;
    // while ((ch = getchar()) != '\n' && ch != EOF);
    getchar();
    cls();

    return code;
}