#ifndef LAB4A_3B_FUNC_H
#define LAB4A_3B_FUNC_H

typedef struct Node{
    int version;
    int key1;
    char key2[30];
    long offset_str;
    int size_str;
    long offset_next;
}Node;

typedef struct KeySpace1{
    int key;
    int par;
    long offset_head;
}KeySpace1;

typedef struct KeySpace2{
    int busy;
    char key[30];
    long offset_head;
}KeySpace2;

typedef struct Table{
    KeySpace1 *ks1;
    KeySpace2 *ks2;
    int msize1;
    int msize2;
    int csize1;
    int csize2;
    long info_size;
}Table;

int dialog(const char *msgs[], int n);

char *get_str();

void getInt(int *a);

Table * CreateTable();

int loading_ks(Table *table);

void DeleteTable(Table *table);

#endif //LAB4A_3B_FUNC_H
