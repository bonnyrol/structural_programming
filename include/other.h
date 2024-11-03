#ifndef OTHER_H_
#define OTHER_H_

#include "../include/main.h"

int delete_file(Fileinfo *folder,  int *n, const int i);
int get_total_size(const Fileinfo *folder, const int n, double *total);
int insert_file(Fileinfo *folder, int *n, const int i, const Fileinfo *item);

#endif /* OTHER_H_ */