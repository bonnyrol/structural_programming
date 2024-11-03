#include <time.h>
#include <stdio.h>
#include "../include/main.h"

int input(Folder *f, const int *i) {

    if (!f) {
        return incorrect_parameters;
    } else if (f->n >= MAX_FILES) {
        return length_error;
    }

    Fileinfo buff = {0};
    int code = success;

    input_filename(&buff);
    input_size(&buff.size);
    //input_date(&buff->creation_time);
    
    code = insert_file(f, (i) ? *i : f->n, &buff);

    return code;
}

void input_filename(Fileinfo *file) {
    char *point = NULL;
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
        print_err("Некорректное значение. Попробуй снова");
    }
}

void input_date(Date *d) {
    int k = 0;
    while (1) {
        printf("Введите дату создания файла: ");
        k = scanf("%d.%d.%d", &d->day, &d->month, &d->year);
        if (k != 3) {
            print_err("Некорректный ввод, попробуй снова.");
            continue;
        } else if (check_date(d)) {
            print_err("Дата создания файла не может быть больше чем текущая дата компьютера.");
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
    if (msg) {
        char ch;
        fprintf(stderr, "%s\n", msg);
        while (((ch = getchar()) != '\n') && (ch != EOF));
    }
}

int print_file(const Fileinfo *file, const int i) { // NEED TO FIX THIS SHIT
    int code = 0;

    printf("%d\t%s.%s\t%.1lf KiB\n", i, file->name, file->extension, file->size);  
    
    return code;
}

int print_folder(const Folder *f) { // AND THIS TOO
    int code = 0, i;

    if (!f) {
        code = 1;
    } else {
        printf("id\tНазвание файла\tРазмер файла\tДата создания\n");
        for (i = 0; i < f->n; i++) {
            print_file(&f->file[i], i);
        }
    }

    return code;
}

char *get_error(const int code) {

    char *msg = NULL;

    switch (code) {
    case incorrect_parameters:
        msg = "Функция не должна принимать NULL\n";
        break;
    case length_error:
        msg = "Выход за пределы массива\n";
        break;
    case bad_index:
        msg = "Некорректный индекс\n";
        break;
    }

    return msg;
}