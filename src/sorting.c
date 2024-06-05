#include "../include/sorting.h"
#include "../include/data_io.h"

void sort(Fileinfo *a, int n, int mode, int sorting) {
    int i, j, noSwap;
    Fileinfo temp;
    Comparator compare = sort_routing(mode);

    for (i = n - 1; compare && i >= 0; i--){
        noSwap = 1;
        for (j = 0; j < i; j++) {
            if (compare(&a[j], &a[j + 1], sorting)) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                noSwap = 0;
            }
        }

        if (noSwap) {
            break;
        } 
    }
}

int (*sort_routing(int mode))(const Fileinfo *a, const Fileinfo *b, int sorting) {
    Comparator result = NULL;

    switch (mode) {
        case name:
            result = namecmp;
            break;
        case ext:
            result = extcmp;
            break;
        case size:
            result = sizecmp;
            break;
        case datetime:
            result = datecmp;
            break;
        default:
            print_err("Сортировка по такой характеристке не существует.");
            break;
    }
    
    return result;
}

int namecmp(const Fileinfo *a, const Fileinfo *b, int sorting) {
    int result = 0;
    if (strcmp(a->name, b->name) > 0) {
        result = 1;
    }
    return (sorting) ? !result : result;
}

int extcmp(const Fileinfo *a, const Fileinfo *b, int sorting) {
    int result = 0;
    if (strcmp(a->extension, b->extension) > 0) {
        result = 1;
    }
    return (sorting) ? !result : result;
}

int sizecmp(const Fileinfo *a, const Fileinfo *b, int sorting) {
    int result = 0;
    if (a->size > b->size) {
        result = 1;
    }
    return (sorting) ? !result : result;
}

int datecmp(const Fileinfo *a, const Fileinfo *b, int sorting) {
    int result = 0;

    if (a->creation_time.year != b->creation_time.year) {
        result = a->creation_time.year - b->creation_time.year;
    } else if (a->creation_time.month != b->creation_time.month) {
        result = a->creation_time.month - b->creation_time.month;
    } else if (a->creation_time.day != b->creation_time.day) {
        result = a->creation_time.day - b->creation_time.day;
    }

    if (result > 0) { /* Если результат положительный => a > b */
        result = 1;
    } else {
        result = 0;
    }

    return (sorting) ? !result : result;
}