#include <time.h>
#include <stdio.h>
#include "../include/data_io.h"
#include "../main.h"

void input(Fileinfo *file) {
    input_filename(file);
    input_size(&file->size);
    input_date(&file->creation_time);
}

void input_filename(Fileinfo *file) {
    char *point;
    char buff[NAME_SIZE + EXT_SIZE];

    while (1) {
        printf("Введите имя и расширение файла: ");
        scanf("%s", buff);
        point = strrchr(buff, '.'); /* Сохранение адреса нахождения точки */

        if (!point) { 
            print_err("Неправильный формат ввода, пример: filename.ext.");
        } else if (((point - buff + 1) > NAME_SIZE) || (strlen(point + 1) > EXT_SIZE)) {
            print_err("Слишком длинное название или расширение.");
        } else if (strpbrk(buff, "/\\:*?\"<>|")) {
            print_err("Имя или расширение файла не может содержать спец.символы.");
        } else {
            *point++ = '\0';
            strncpy(file->name, buff, point - buff);
            strcpy(file->extension, point);
            break;
        }
    }

}

void input_size(double *size) {
    printf("Введите размер файла в КБ: ");
    while (scanf("%lf", size) != 1 || *size < 0) {
        print_err("Размер не может быть отрицательным.");
    }
}

void input_date(Date *d) {
    int k = 0;
    while (1) {
        printf("Введите дату создания файла: ");
        k = scanf("%d.%d.%d", &d->day, &d->month, &d->year);
        if (k != 3 || check_date(d)) {
            print_err(NULL);
            continue;
        }
        break;
    }
}

int check_date(const Date *d) {
    int result = 0, cur_year = 0, cur_mon = 0;
    time_t current_time = time(NULL);
    struct tm *now = localtime(&current_time);

    if (d->year < 1900 || d->year > now->tm_year + 1900) {
        result = 1; 
    } else if (d->year == now->tm_year + 1900){
        cur_year = 1;
    }

    if (d->month < 1 || (d->month > now->tm_mon + 1 && cur_year)) {
        result = 1;
    } else if (d->month == now->tm_mon + 1) {
        cur_mon = 1;
    }

    if (d->day < 1 || (d->day > now->tm_mday && (cur_mon && cur_year))) {
        result = 1;
    }

    return result;
}

void print_date(const Date *d) {
    printf("%d.%d.%d\n", d->day, d->month, d->year);
}

void print_err(const char *msg) {
    char ch;
    if (msg) {
        fprintf(stderr, "Некорректный ввод. %s\n", msg);
    } else {
        fprintf(stderr, "Некорректный ввод.\n");
    }
    while (((ch = getchar()) != '\n') && (ch != EOF));
}