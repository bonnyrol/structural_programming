#ifndef OTHER_H_
#define OTHER_H_

#include "../include/main.h"

int delete_file(Folder *f, const int i);
int insert_file(Folder *f, const int i, Fileinfo *item);
double get_sizes(const Folder *f);

#endif /* OTHER_H_ */