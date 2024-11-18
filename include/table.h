#ifndef _TABLE_H
#define _TABLE_H

#include <string.h>

typedef struct {
    char name[20]; /* Название поля */
    size_t len; /* Длина поля в символах, обычно определяется по максимальной длине данных поля */
} Field;

size_t get_w(const Field *f, const int n, const size_t j);

size_t get_offset(const Field *f, const int k, const char *str);

size_t sum(const Field *f, const int n);

size_t get_dynamic_len(const char *tbl_field, const size_t max_len);

#endif // _TABLE_H