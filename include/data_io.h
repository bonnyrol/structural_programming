#ifndef DATA_IO_H_
#define DATA_IO_H_

#include <string.h>
#include "main.h"

int input(Fileinfo *folder, int *n, const int *i);
void input_filename(Fileinfo *file);
void input_size(double *size);
void input_date(Date *d);
int check_date(const Date *d);
void print_date(const Date *d);
void print_err(const char *msg);
int print_file(const Fileinfo* folder, const int n, const int i);
int print_folder(const Fileinfo *folder, const int n);
char *get_error(const int code);

#endif /* DATA_IO_H_ */