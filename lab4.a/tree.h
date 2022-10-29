#ifndef MAIN_C_TREE_H
#define MAIN_C_TREE_H

typedef struct Info{
    char *str;
    int num_info;
}Info;

typedef struct Item{
    Info *info;
    int version;
    struct Item *next;
}Item;

typedef struct Tree {
    char *key;
    Item *item;
    struct Tree *left;
    struct Tree *right;
    struct Tree *parent;
}Tree;

Tree *find_way(Tree *tree,char *key,int num_info,char *info);
int dialog(const char *msgs[], int n);
char *get_str();
void int_input1(int *a);
int free_tree(Tree *tree);
int add_element_to_tree(Tree **tree,char *key, char *info,int num_info);
Tree *create_element(char *key,char *info,int num_info,Item *last_item,Tree *par);
Item *create_item(char *info, int num_info,Item *last_item);
Tree *search_element(Tree *root,char *key);
int output_element(Tree *element,int release);
int print_tree(Tree *tree,int space);
int output_keys(Tree *tree,char *key);
int delete_element(Tree **tree,Tree *now,int release);
int delete_item(Tree *el,int release);
Item* list_delete_head(Item* head);
Item *delete_elem(Item *head,Item *elem);
Tree *find_next_element(Tree *el);
int loading(Tree **tree);
int D_Timing();
int output_tree(Tree *tree,FILE *output);
Tree *find_next(Tree *tree,char *key);
Tree *find_prev(Tree *tree,char *key);
Tree *choose(Tree *el1, Tree *el2,char *key);
int delete1(Tree **tree, Tree *now,int release);
int delete2(Tree **tree, Tree *now,int release);
int delete3(Tree *now,int release);

#endif //MAIN_C_TREE_H