#ifndef OTHER_H_
#define OTHER_H_

#include "../include/main.h"

int delete_file(Folder *f, const int i);
int insert_file(Folder *f, const int i, Fileinfo *item);
double get_sizes(const Folder *f);
void clear_all(Folder *f);
int save_to_file(const Folder *f, const char *filename);
int load_from_file(Folder *f, const char *filename);
int allocate(Folder *f, const int n);

#endif /* OTHER_H_ */