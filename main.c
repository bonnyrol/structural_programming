#include <stdlib.h>
#include <stdio.h>
#include "main.h"

int main() {
    int i;
    /* Fileinfo folder[MAX_FILES] = {0}; */
    Fileinfo folder2[5] = {{1, "game", "exe", 500, {12, 12, 2012}}, 
                          {2, "secret", "txt", 23403, {16, 11, 2023}},
                          {3, "my birthday", "jpeg", 321, {20, 8, 2005}},
                          {4, "Отчёт по лабараторной работе №7", "docx", 110, {25, 3, 2024}},
                          {5, "main", "c", 8, {1, 2, 2024}}};
    /* Fileinfo *a = &folder[0]; */
    double total_size = 0;
#ifdef _WIN64
    system("chcp 65001 > NUL");
#endif

    
    for(i = 0; i < 5; i++) {
        printf("File №%d:\n", i + 1);
        printf("Name: %s.%s\n", folder2[i].name, folder2[i].extension);
        printf("Size: %.2lf\n", folder2[i].size);
        print_date(&folder2[i].creation_time);
        putchar('\n');
    }
    
    printf("Sorting...\n");
    putchar('\n');
    sort(folder2, 5, size, ascending);

    for(i = 0; i < 5; i++) {
        printf("File №%d:\n", i + 1);
        printf("Name: %s.%s\n", folder2[i].name, folder2[i].extension);
        printf("Size: %.2lf\n", folder2[i].size);
        print_date(&folder2[i].creation_time);
        putchar('\n');
    }
    /* printf("1: %s 2: %s\n", folder2[0].name, folder2[1].name); */
    printf("size: %.2lf\n", total_size);

    return 0;
}

