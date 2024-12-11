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
    
    // memset(&f->file[i], 0, sizeof(Fileinfo));

    f->size -= f->file[i].size;

    if (i == 0) {
        memmove(f->file, f->file + 1, (f->n - 1) * sizeof(Fileinfo));
    } else if (i != f->n - 1) {
        memmove(f->file + i, f->file + i + 1, (f->n - i - 1) * sizeof(Fileinfo));
    }

    f->n--;
    return success;
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
    }
    


    item->id = get_unique_id(f);

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

        if (new_n <= MAX_FILES && new_n > 0) {

            fseek(bin, 0, SEEK_END);
            file_size = ftell(bin);
            if (!(file_size - sizeof(f->n) - sizeof(Fileinfo) * new_n)) {
                fseek(bin, sizeof(f->n), SEEK_SET);
                fread(f->file, sizeof(Fileinfo), new_n, bin);

                // int cnt = 0;

                f->n = new_n;
                // for (int i = 0; i < new_n; i++) {
                //     char buff[NAME_SIZE + EXT_SIZE + 2] = {'\0'};
                //     snprintf(buff, NAME_SIZE + EXT_SIZE + 2, "%s.%s", f->file[i].name, f->file[i].extension);
                //     if (check_date(&f->file[i].creation_time) || check_filename(buff) || f->file[i].size < 0) {
                //         delete_file(f, i - cnt);
                //         cnt++;
                //     }
                // }
                

                f->size = get_sizes(f);


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


int allocate(Folder *f) {
    if (!f) {
        return incorrect_parameters;
    }

    int code = success;

    if (!f->n) {
        f->n = 1, f->file = NULL;
        f->file = calloc(f->n, sizeof(Fileinfo));
        if (!f->file) {
            code = bad_alloc;
        }
    } else {
        Fileinfo *temp = NULL;


        temp = realloc(f->file, f->n + 1);
        if (temp) {
            f->file = temp;
            f->n++;
        } else {
            code = bad_alloc;
        }
    }

    return code;
}

// void freemem(Folder *f) {
//     free(f->file);
//     f->n = 0, f->size = 0;
// }