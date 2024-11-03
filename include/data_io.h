#ifndef DATA_IO_H_
#define DATA_IO_H_

#include <string.h>
#include "../main.h"

void input(Fileinfo *file);
void input_filename(Fileinfo *file);
void input_size(double *size);
void input_date(Date *d);
int check_date(const Date *d);
void print_date(const Date *d);
void print_err(const char *msg);

#endif /* DATA_IO_H_ */