#ifndef MAIN_H_
#define MAIN_H_

#define MAX_FILES 6
#define EXT_SIZE 5
#define NAME_SIZE 100

typedef enum {name, ext, size, datetime} mode; /* флаги для обозначния сортировки по типу.*/
typedef enum {ascending, descending} sorting; /* Флаги для обозначения сортировки по возрастанию или убыванию. */
typedef enum {success, incorrect_parameters, length_error, bad_index} errors;

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

typedef struct {
    Fileinfo file[MAX_FILES];
    int n;
    double size;
} Folder;


#include "data_io.h"
#include "sorting.h"
#include "other.h"

#endif /* MAIN_H_ */