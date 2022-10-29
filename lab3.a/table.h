#ifndef LABA3_A_HEAD_H
#define LABA3_A_HEAD_H
#define Size 20


typedef struct InfoType{
    char *str;                                        //Строка произвольной длины
    int num;                                         //Два целых числа
}InfoType;

typedef struct Item{
    InfoType *info;
    int key1;
    int release;
    char key2[30];
    int version;
    struct Item *next;
}Item;

typedef struct KeySpace1{           // Просматриваемая таблица, организованная вектором;
    int busy;
    int key1;
    int release;
    Item *item;
}KeySpace1;

typedef struct list {
    char key2[30];
    Item *item;
    struct list *next;
}list;

typedef struct KeySpace2{           //Перемешанная таблица сцеплением

    list *list;

}KeySpace2;

typedef struct Table{
    KeySpace1 *ks1;
    KeySpace2 *ks2;
    int csize1;
}Table;


int dialog(const char *msgs[], int n);
Table* table_selection();
void free_table(Table *table);
void int_input(int *a);
void show_table(Table *table);
void show_table2(Table *table);
Item *create_item(int key,char *key2,int num,char *str,int release,Item *last_item,int version);
char *get_str();
int Hash_function(char *key2);
void Reorganization_first_table(Table *table);
void enter_keys(int *key1,char *key2);
int find_key1(Table *table, int key1);
Item *find_key2(Table *table, char *key2);
list *create_list(char *key2,Item *item);
list *add_to_list(char *key2,Item *item,list *list1);
void delete_item_by_KeySpace2(KeySpace2 *ks2,char *key2);
list *delete_elem(list *head,list *elem);
list* list_delete_head(list* head);
int add_element(Table *table, int key1,char *key2,char *info,int num_info);
int delete_item_by(Table *table, int position, int key);
int output_all_versions(Table *table,int key1);
void output_item(Item *item);


#endif
