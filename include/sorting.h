#ifndef SORTING_H_
#define SORTING_H_

#include <string.h>
#include "main.h"

typedef int (*Comparator)(const Fileinfo *a, const Fileinfo *b, const int sorting);

void sort(Folder *f, const int mode, const int sorting);
int (*sort_routing(const int mode))(const Fileinfo *a, const Fileinfo *b, const int sorting);
int namecmp(const Fileinfo *a, const Fileinfo *b, int sorting);
int extcmp(const Fileinfo *a, const Fileinfo *b, int sorting);
int sizecmp(const Fileinfo *a, const Fileinfo *b, int sorting);
int datecmp(const Fileinfo *a, const Fileinfo *b, int sorting);

#endif /* SORTING_H_ */