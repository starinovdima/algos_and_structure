#ifndef LABA4BBB_KD_TREE_H
#define LABA4BBB_KD_TREE_H
#include <stdio.h>

typedef struct Info{
    char *str;
    int num_info;
}Info;

typedef struct Tree {
    int key[2];
    Info *info;
    int remember;       // 0 если х; 1 если y;
    struct Tree *left;
    struct Tree *right;
    struct Tree *par;
}Tree;




int dialog1(const char *msgs[], int n);
void int_input(int *a);
char *get_str();
int add_element(Tree **tree,int key1,int key2,int num_info,char *info);
Tree *create_element(int key1,int key2,int num_info,char *info,int remember,Tree *par);
Tree *search_element(Tree *tree, int key1,int key2);
void output_element(Tree *el);
int loadingg(Tree **tree);
int print(Tree *ptr, int space);
int output_keys(Tree *tree);
int fre_tree(Tree *tree);
int grapvhiz(Tree *tree,FILE *output);
int delete_element(Tree **tree,Tree *element);
int delete1(Tree **tree,Tree *element);
int delete2(Tree **tree,Tree *element);
int delete3(Tree *element);
void delete_item(Tree *element);
Tree *find_element(Tree *element);
int D_Timing();
int outputkeys1(Tree *tree);
int outputkeys2(Tree *tree);
int biggest_element(Tree *tree,Tree **search);
Tree *find_biggest(Tree *tree);
int rebuild(Tree *gr);
Tree *find_next(Tree *el,int remember);
Tree *find_prev(Tree *el,int remember);


#endif //LABA4BBB_KD_TREE_H
