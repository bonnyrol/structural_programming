#include "../include/other.h"
#include <string.h>


int delete_file(Fileinfo *folder, int *n, const int i) {

    if (!folder || !n) {
        return incorrect_parameters;
    } else if (*n == 0) {
        return length_error;
    } else if (i < 0 || i >= *n) {
        return bad_index;
    }

    if (i == 0) {
        memmove(folder, folder + 1, (*n - 1) * sizeof(Fileinfo));
    } else if (i != *n - 1) {
        memmove(folder + i, folder + i + 1, (*n - i - 1) * sizeof(Fileinfo));
    }

    (*n)--;

    return success;
}

int insert_file(Fileinfo *folder, int *n, const int i, const Fileinfo *item) {
    
    if (!folder || !n || !item) {
        return incorrect_parameters;
    } else if (*n + 1 > MAX_FILES) {
        return length_error;
    } else if (i < 0) {
        return bad_index;
    }

    if (!i) {
        memmove(folder + 1, folder, *n * sizeof(Fileinfo));
        folder[i] = *item;
    } else if (i >= *n) {
        folder[*n] = *item;
    } else {
        memmove(folder + i + 1, folder + i, (*n - i) * sizeof(Fileinfo));
        folder[i] = *item;
    }

    (*n)++;

    return success;
}

int get_total_size(const Fileinfo *folder, const int n, double *total) {

    if (!folder || !total) {
        return incorrect_parameters;
    }

    int i;
    for (i = 0; i < n; i++) {
        *total += folder[i].size;
    }

    return success;
}