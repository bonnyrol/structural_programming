#include "../include/other.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int delete_file(Folder *f, const int i) {

    if (!f) {
        return incorrect_parameters;
    } else if (f->n == 0) {
        return length_error;
    } else if (i < 0 || i >= f->n) {
        return bad_index;
    }

    int code = success;
    
    // memset(&f->file[i], 0, sizeof(Fileinfo));

    /* TODO: выделить копирование в отдельную функцию */
    // Folder temp = {0};
    // allocate(&temp, f->n);
    // memcpy(temp.file, f->file, sizeof(Fileinfo) * f->n);
    // temp.size = f->size, temp.n = f->n;

    f->size -= f->file[i].size;

    if (i == 0) {
        memmove(f->file, f->file + 1, (f->n - 1) * sizeof(Fileinfo));
    } else if (i != f->n - 1) {
        memmove(f->file + i, f->file + i + 1, (f->n - i - 1) * sizeof(Fileinfo));
    }

    f->n--;
    if (!f->n) {
        free(f->file), f->file = NULL;
    } else {
        Fileinfo *temp = NULL;
        temp = realloc(f->file, f->n * sizeof(Fileinfo));
        if (temp) {
            free(f->file);
            f->file = temp;
        }
    }

    // temp.n--;
    // Fileinfo *t = NULL;
    // if (temp.n) {
    //     t = realloc(temp.file, temp.n * sizeof(Fileinfo));
    //     if (t) {
    //         temp.file = t;
    //         free(f->file);
    //         *f = temp;
    //     } else {
    //         code = bad_alloc;
    //     }
    // } else {
    //     free(f->file);
    //     free(temp.file);
    //     f->file = NULL, f->n = 0, f->size = 0;
    // }


    return code;
}

int get_unique_id(const Folder *f) {

    static int max_id = 0;

    if (!max_id) {
        for (int i = 0; i < f->n; i++) {
            if (f->file[i].id > max_id) {
                max_id = f->file[i].id;
            }
        }
    }

    return ++max_id;
}

int insert_file(Folder *f, const int i, Fileinfo *item) {
    
    if (!f || !item) {
        return incorrect_parameters;
    // } else if (f->n + 1 > MAX_FILES) {
    //     return length_error;
    } else if (i < 0) {
        return bad_index;
    } else if (allocate(f, f->n + 1)) {
        return bad_alloc;
    }
    
    item->id = get_unique_id(f);

    if (!i) {
        memmove(f->file + 1, f->file, (f->n - 1) * sizeof(Fileinfo));
        f->file[i] = *item;
    } else if (i >= f->n - 1) {
        f->file[f->n - 1] = *item;
    } else {
        memmove(f->file + i + 1, f->file + i, (f->n - i - 1) * sizeof(Fileinfo));
        f->file[i] = *item;
    }

    f->size += item->size;

    return success;
}

double get_sizes(const Folder *f) {
    double result = 0.0f;

    for (int i = 0; i < f->n; i++) {
        result += f->file[i].size;
    }

    return result;
}

void clear_all(Folder *f) {
    int n = f->n;
    for (int i = 0; i < n; i++) {
        delete_file(f, 0);
    }
}

int save_to_file(const Folder *f, const char *filename) {
    if (!f || !filename) {
        return incorrect_parameters;
    }

    int code = success;

    FILE *fp = NULL;

    fp = fopen(filename, "wb");

    if (!fp) {
        return fopen_error;
    } else {

        fwrite(&f->n, sizeof(f->n), 1, fp);
        fwrite(f->file, sizeof(Fileinfo), f->n, fp);

        fclose(fp);
    }

    return code;
}


int load_from_file(Folder *f, const char *filename) {

    if (!f || !filename) {
        return incorrect_parameters;
    }

    int code = success;
    
    FILE *bin = NULL;
    
    bin = fopen(filename, "rb");
            long file_size = 0;
    if (bin) {
        
        int new_n = 0;
        fread(&new_n, sizeof(f->n), 1, bin);

        if (new_n > 0) {

            fseek(bin, 0, SEEK_END);
            file_size = ftell(bin);
            if (!(file_size - sizeof(f->n) - sizeof(Fileinfo) * new_n)) {
                fseek(bin, sizeof(f->n), SEEK_SET);

                Folder new = {0};
                // new.file = NULL;

                if (!allocate(&new, new_n)) {
                    fread(new.file, sizeof(Fileinfo), new_n, bin);
                    new.n = new_n, new.size = get_sizes(&new);
                    free(f->file);
                    *f = new;
                } else {
                    code = bad_alloc;
                }


                
                
                // int cnt = 0;
                // allocate(&new, new_n);

                // for (int i = 0; i < new_n; i++) {
                //     char buff[NAME_SIZE + EXT_SIZE + 2] = {'\0'};
                //     snprintf(buff, NAME_SIZE + EXT_SIZE + 2, "%s.%s", f->file[i].name, f->file[i].extension);
                //     if (check_date(&f->file[i].creation_time) || check_filename(buff) || f->file[i].size < 0) {
                //         delete_file(f, i - cnt);
                //         cnt++;
                //     }
                // }
                



            } else {
                code = fcorrupt;
            }

        } else {
            code = length_error;
        }

        // printf("n: %d, size: %ld\n", new_n, file_size);
        fclose(bin);

    } else {
        code = fopen_error;

    }

    return code;
}


int allocate(Folder *f, const int n) {
    if (!f || n < 0) {
        return incorrect_parameters;
    }

    int code = success;

    Fileinfo *temp = NULL;

    if (!f->file) {
        temp = calloc(n, sizeof(Fileinfo));
    } else {
        temp = realloc(f->file, n * sizeof(Fileinfo));
    }

    if (temp) {
        f->file = temp;
        f->n = n;
    } else {
        code = bad_alloc;
    }

    return code;
}