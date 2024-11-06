#include "../include/table.h"

size_t get_w(const Field *f, const int n, const size_t j) {

    size_t sum = 0, result = 0;
    for (int i = 0; i < n; i++) {
        sum += f[i].len;
        if (j <= sum) {
            result = sum;
            break;
        }
    }

    return result;
}

size_t get_offset(const Field *f, const int k, const char *str) {
    size_t result = 0;


    /*                          Обожаю хардкод))))))
    * По сути - ничего сложного, для того что бы вычислить наш оффсет необходимо
    *  учесть предыдущие поля(если они были), взять половину длины всего поля
    * (без учёта нашей границы) и вычесть из неё половину длины названия поля.
    * Грубо говоря, всё по формуле: (width / 2) - (text/2), только с учётом нюансов нашей таски*/
    result = ((f[k].len - 1) / 2) - ((strlen((str) ? str : f[k].name) >> 1) - 1);


    return result;
}

size_t sum(const Field *f, const int n) {
    size_t result = 0;
    for (int i = 0; i < n; i++) {
        result += f[i].len;
    }

    return result;
}

size_t get_dynamic_len(const char *tbl_field, const size_t max_len) {
    size_t result = strlen(tbl_field);
    // size_t temp = strlen(field_data);
    

    return (result > max_len) ? result + 3 : max_len + 3;
}