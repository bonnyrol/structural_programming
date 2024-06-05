#ifndef MAIN_H_
#define MAIN_H_

#define MAX_FILES 64
#define EXT_SIZE 5
#define NAME_SIZE 255

typedef enum {name, ext, size, datetime} mode; /* флаги для обозначния сортировки по типу.*/
typedef enum {ascending, descending} sorting; /* Флаги для обозначения сортировки по возрастанию или убыванию. */

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    int id; /* Идентификатор файла */
    char name[NAME_SIZE]; /* Имя файла */
    char extension[EXT_SIZE]; /* Расширение файла */
    double size; /* Размер файла в КБ */
    Date creation_time; /* Дата создания */
} Fileinfo;

#include "include/data_io.h"
#include "include/sorting.h"
#include "include/menu.h"

#endif /* MAIN_H_ */