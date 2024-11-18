#include <time.h>
#include <stdio.h>
#include "../include/main.h"
#include "../include/table.h"

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
    input_date(&buff.creation_time);
    
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

        if (!point || !strlen(point + 1)) { 
            print_err("Неправильный формат ввода, пример: filename.ext");
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
        printf("Введите дату создания файла (формат ДД.ММ.ГГГГ): ");
        k = scanf("%02d.%02d.%d", &d->day, &d->month, &d->year);
        if (k != 3 || check_date(d)) {
            print_err("Некорректный ввод, попробуй снова.");
        } else {
            break;
        }
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

    if (d->month > 12 || d->month < 1 || (d->month > now->tm_mon + 1 && cur_year)) {
        result = 1;
    } else if (d->month == now->tm_mon + 1) {
        cur_mon = 1;
    }

    if (d->day > ((d->month % 2) ? 31 : 30) || d->day < 1 || (d->day > now->tm_mday && (cur_mon && cur_year))) {
        result = 1;
    }

    return result;
}

void print_err(const char *msg) {
    if (msg) {
        char ch;
        fprintf(stderr, "%s\n", msg);
        while (((ch = getchar()) != '\n') && (ch != EOF));
    }
}

void print_folder(const Folder *f) {

    /* Данная переменная служит для отслеживания изменений в f */
    static int prev_n = 0;
    static size_t max_len[4] = {0};

    /* Если были добавленны новые элементы, или мы вызываем эту функцию в первый раз */
    if (prev_n != f->n || !prev_n) {
        memset(max_len, 0, 4 * sizeof(size_t));

        for (int i = 0; i < f->n; i++) {
            char id[10], size[15], date[11]; // Все не строковые элементы мы должны сохранить в виде строки

            snprintf(id, 10, "%d", f->file[i].id);
            snprintf(size, 15, "%.2lf", f->file[i].size);
            snprintf(date, 11, "%02d/%02d/%d", f->file[i].creation_time.day, f->file[i].creation_time.month, f->file[i].creation_time.year);

            size_t curr_len[4] = {strlen(id), strlen(f->file[i].name) + strlen(f->file[i].extension) + 1,  strlen(size),  strlen(date)};

            for (int j = 0; j < 4; j++){
                if (curr_len[j] > max_len[j]) {
                    max_len[j] = curr_len[j]; 
                }
            }

        }

    }

    const char field_name[4][11] = {"id", "filename", "file size", "created at"}; 
    static Field ff[4] = {0};

    /* Если кол-во элементов изменилось, то переопределяем поля, иначе используем что есть */
    if (prev_n != f->n || !prev_n) {
        for (int i = 0; i < 4; i++) {
            strncpy(ff[i].name, field_name[i], strlen(field_name[i]) + 1);
            ff[i].len = get_dynamic_len(ff[i].name, max_len[i]);
        }
    }

    /*Счётчик для итераций по файлам*/
    int cnt = 0, fcnt = 0;

    /* Размер шапки таблицы с учётом одной границы */
    size_t header_size = 4;

    /* h - heigth. Учитывает две горизонтальные границы, размер шапки и кол-во выоводимых элементов */
    size_t h = 2 + header_size + f->n;

    /* w - weigth. Учитывает длину полей из шапки и их границы*/
    size_t w = 1;
    for (int i = 0; i < 4; i++) {
        w += ff[i].len;
    }

    for (size_t i = 0; i < h; i++) {
        char id[10], size[15], date[11], filename[EXT_SIZE + NAME_SIZE + 1];

        if (cnt < f->n && i > header_size) {
            snprintf(id, 10, "%*d", (int)max_len[0], f->file[cnt].id);
            snprintf(size, 15, "%.2lf", f->file[cnt].size);
            snprintf(date, 11, "%02d/%02d/%d", f->file[cnt].creation_time.day, f->file[cnt].creation_time.month, f->file[cnt].creation_time.year);
            snprintf(filename, EXT_SIZE + NAME_SIZE + 1, "%s.%s", f->file[cnt].name, f->file[cnt].extension);
            cnt++;
        }

        for (size_t j = 0; j < w; j++) {

            /* Отрисовка основных границ таблицы */
            if ((!i || i == h - 1 || i == header_size) && (!j || j == w - 1 || j == get_w(ff, 4, j))) {
                putchar('+');
            } else if (!j || j == w - 1 || j == get_w(ff, 4, j)) {
                putchar('|');
            } else if (!i || i == h - 1 || i == header_size) {
                putchar('-');

            /* Вывод названия полей */
            } else if (fcnt < 4 && i == header_size >> 1 && j == sum(ff, fcnt) + get_offset(ff, fcnt, NULL)) {
                printf("%s", ff[fcnt].name);
                j += strlen(ff[fcnt].name) - 1, fcnt++;
                
            /* Вывод данных полей */
            } else if (i > header_size && j == get_offset(ff, 0, id)) {
                printf("%s", id);
                j += strlen(id) - 1;

            } else if (i > header_size && j == sum(ff, 1) + get_offset(ff, 1, filename)) {
                printf("%s", filename);
                j += strlen(filename) - 1;

            } else if (i > header_size && j == sum(ff, 2) + get_offset(ff, 2, size)) {
                printf("%s", size);
                j += strlen(size) - 1;

            } else if (i > header_size && j == sum(ff, 3) + get_offset(ff, 3, date)) {
                printf("%s", date);
                j += strlen(date) - 1;

            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }
    printf("Общий размер файлов в папке: %.2lf\n\n", f->size);
    prev_n = f->n;
}

char *get_error(const int code) {

    char *msg = NULL;

    switch (code) {
    case incorrect_parameters:
        msg = "Функция принимает некорректные значения\n";
        break;
    case length_error:
        msg = "Выход за пределы массива\n";
        break;
    case bad_index:
        msg = "Некорректный индекс\n";
        break;
    case bad_alloc:
        msg = "Ошибка выделения памяти\n";
        break;

    }

    return msg;
}