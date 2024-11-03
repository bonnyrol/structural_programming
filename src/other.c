#include "../include/other.h"
#include <string.h>

int delete_file(Folder *f, const int i) {

    if (!f) {
        return incorrect_parameters;
    } else if (f->n == 0) {
        return length_error;
    } else if (i < 0 || i >= f->n) {
        return bad_index;
    }

    f->size -= f->file[i].size;

    if (i == 0) {
        memmove(f->file, f->file + 1, (f->n - 1) * sizeof(Fileinfo));
    } else if (i != f->n - 1) {
        memmove(f->file + i, f->file + i + 1, (f->n - i - 1) * sizeof(Fileinfo));
    }

    f->n--;
    return success;
}

int insert_file(Folder *f, const int i, const Fileinfo *item) {
    
    if (!f || !item) {
        return incorrect_parameters;
    } else if (f->n + 1 > MAX_FILES) {
        return length_error;
    } else if (i < 0) {
        return bad_index;
    }

    if (!i) {
        memmove(f->file + 1, f->file, f->n * sizeof(Fileinfo));
        f->file[i] = *item;
    } else if (i >= f->n) {
        f->file[f->n] = *item;
    } else {
        memmove(f->file + i + 1, f->file + i, (f->n - i) * sizeof(Fileinfo));
        f->file[i] = *item;
    }

    f->n++;
    f->size += item->size;

    return success;
}