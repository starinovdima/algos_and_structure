#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int dialog(const char *msgs[], int n) {
    char *error = "";
    int choice;
    do {
        puts(error);
        error = "You're wrong. Try again!";
        for (int i = 0; i < n; ++i) {
            puts(msgs[i]);
        }
        puts("Make your choice: ");
        choice = getchar() - '0';
        while (getchar() != '\n') {}
    } while (choice < 0 || choice >= n);
    return choice;
}

char *get_str() {
    printf("Enter string with variable length -> ");
    scanf("%*c");
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = (char*)realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = (char *)calloc(1, sizeof(char));
    }

    return res;
}

void int_input(int *a)
{
    int n;
    do
    {
        n = scanf("%d", a);

        if (n == 0)
        {
            printf("Error, try again: ");
            scanf("%*c");
        }
        if (n > 0 && *a <= 0){
            printf("Enter natural int: ");
            scanf("%*c");
            n = -1;
        }

    } while (n <= 0);

}

void enter_keys(int *key1,char *key2){
    printf("Enter the first key:\n");
    int_input(key1);
    printf("Enter the second key (no more than 30 symbols):\n");
    scanf("%s",key2);
    scanf("%*c");

}

void free_table(Table *table){
    Item *last_item = NULL;
    for(int i = 0; i < Size;i++){
        if (table->ks1[i].busy != 0) {
            while (table->ks1[i].item != NULL){
                last_item = table->ks1[i].item;
                table->ks1[i].item = table->ks1[i].item->next;
                free(last_item->info->str);
                free(last_item->info);
                free(last_item);
            }
        }
    }
    list *list1 = NULL;
    for(int j = 0; j<Size; j++){
        if(table->ks2[j].list != NULL){
            while(table->ks2[j].list != NULL){
                list1 = table->ks2[j].list;
                table->ks2[j].list = table->ks2[j].list->next;
                free(list1);
            }
        }
    }
    free(table->ks1);
    free(table->ks2);
    free(table);

}

Table *table_selection(){
    Table *table = (Table *)calloc(1,sizeof(Table));
    table->ks1 = (KeySpace1 *)calloc(Size,sizeof(KeySpace1));
    table->ks2 = (KeySpace2 *)calloc(Size,sizeof(KeySpace2*));
    table->csize1 = 0;
    return table;
}

Item *create_item(int key,char *key2,int num,char *str,int release,Item *last_item,int version){
    int size_len = strlen(str) + 1;

    Item *item = (Item*)calloc(1,sizeof(Item));
    item->info = (InfoType*)calloc(1,sizeof(InfoType));
    item->info->num = num;
    item->info->str = (char *)calloc(size_len,sizeof(char));
    strcpy(item->info->str,str);
    item->key1 = key;
    strcpy(item->key2,key2);
    item->version = version;

    if(release == 1){
        item->release = release;
        item->next = NULL;
    }
    else{
        item->release = release;
        item->next = last_item;
    }
    return item;
}

void show_table(Table *table){
    for (int i = 0;i < table->csize1; i++){
        printf("Item[]->busy:%d key1:%d version:%d \n",table->ks1[i].busy,table->ks1[i].key1,table->ks1[i].release);
    }
}

void show_table2(Table *table){

    for (int i = 0;i <table->csize1; i++){
        if(table->ks1[i].busy != 0)
            printf("Item[]->key1:%d key2:%s version:%d info:%d %s\n",table->ks1[i].key1,table->ks1[i].item->key2,table->ks1[i].release,
                   table->ks1[i].item->info->num,table->ks1[i].item->info->str);

    }
}

int output_all_versions(Table *table,int key1){
    Item *item = NULL;
    int coin = 0;
    for(int i = 0;i<table->csize1;i++){
        if (table->ks1[i].key1 == key1 && table->ks1[i].busy == 1) {
            coin += 1;
            if (coin == 1)
                printf("Item found and has version\n");
            item = table->ks1[i].item;
            while (item != NULL) {
                printf("Item[]->key1:%d key2:%s release %d Item-release:%d info: info %d %s \n", item->key1, item->key2,
                       table->ks1[i].release,item->release, item->info->num, item->info->str);
                item = item->next;
            }
        }
    }
    if(coin > 0)
        return 0;
    return -2;
}

void output_item(Item *item) {
    while (item != NULL) {
        printf("Item[]->key1:%d key2:%s Item-release:%d info: info %d %s \n", item->key1, item->key2,
               item->release, item->info->num, item->info->str);
        item = item->next;
    }
}


void Reorganization_first_table(Table *table){
    int i = 0;
    int j;
    struct KeySpace1 tmp;
    while (i < table->csize1){
        if(table->ks1[i].busy == 1){
            tmp = table->ks1[i];
            j = i;
            while(j != 0){
                table->ks1[j] = table->ks1[j-1];
                j--;
            }
            table->ks1[0] = tmp;
        }
        i++;
    }
}

int find_key1(Table *table, int key){

    if(table->csize1 == 0){
        return -2;                               // Таблица пуста
    }

    for (int i = 0; i < table->csize1; i++) {
        if(table->ks1[i].key1 == key && table->ks1[i].busy == 1){
            return i;                          // Есть такой ключ
        }
    }

    return -3;                                   // Вообще нет такого ключа
}

int delete_item_by(Table *table, int release, int key){
    char key2[30];
    Item *last_item;
    if(release < 0){                          //Удаление всех версий
        for(int i = 0; i<table->csize1; i++){
            if(table->ks1[i].key1 == key && table->ks1[i].busy == 1){
                strcpy(key2,table->ks1[i].item->key2);
                table->ks1[i].busy = 0;
                while (table->ks1[i].item != NULL){
                    last_item = table->ks1[i].item;
                    table->ks1[i].item = table->ks1[i].item->next;
                    free(last_item->info->str);
                    free(last_item->info);
                    free(last_item);
                }
                delete_item_by_KeySpace2(table->ks2,key2);
            }
        }
    }
    else{                                       //Удаление одной версии
        for(int i = 0; i<table->csize1; i++){
            if(table->ks1[i].key1 == key && table->ks1[i].busy == 1 && table->ks1[i].release == release){
                strcpy(key2,table->ks1[i].item->key2);
                table->ks1[i].busy = 0;
                while (table->ks1[i].item != NULL){
                    last_item = table->ks1[i].item;
                    table->ks1[i].item = table->ks1[i].item->next;
                    free(last_item->info->str);
                    free(last_item->info);
                    free(last_item);
                }
                delete_item_by_KeySpace2(table->ks2,key2);
                return 0;
            }
        }
    }
    return -1;
}

int add_element(Table *table, int key1,char *key2,char *info, int num_info){
    int finder1,release;
    int csize_now;
    int hash = Hash_function(key2);
    Item *item = NULL;
    Item *last_item = NULL;
    int last_version = 0;
    csize_now = table->csize1;
    if(table->csize1 == Size){
        return 1;                       // Места нет для элемента в первом пространстве
    }
    finder1 = find_key1(table,key1);
    Item *finder2 = find_key2(table,key2);

    for (int i = 0; i <table->csize1 ; i++){
        if(table->ks1[i].key1 == key1){
            last_version +=1;
        }
    }
    if(finder1 >= 0 && finder2 != NULL){
        release = table->ks1[finder1].item->release + 1;
        item = create_item(key1,key2,num_info,info,release,table->ks1[finder1].item,table->ks1[finder1].item->version);
        table->ks1[finder1].item = item;
        list *list4 = table->ks2[hash].list;
        while(list4 != NULL) {
            if (strcmp(list4->key2, key2) == 0){
                list4->item = item;
                break;
            }
            else
                list4 = list4->next;
        }

        return 4;
    }
    else if(finder1 < 0 && finder2 != NULL)
        return 5;

    else if(finder1 >= 0 || last_version > 0){                                              //Добавляем новую версию
        release = 1;
        int new_version = last_version + 1;
        table->ks1[csize_now].key1 = key1;
        table->ks1[csize_now].release = new_version;
        table->ks1[csize_now].busy = 1;
        item = create_item(key1,key2,num_info,info,release,last_item,new_version);
        table->ks1[csize_now].item = item;
        if (table->ks2[hash].list == NULL){
            table->ks2[hash].list = create_list(key2,item);
        }
        else{
            table->ks2[hash].list = add_to_list(key2,item,table->ks2[hash].list);
        }

        table->csize1 += 1;

        return 2;
    }
    else if (finder1 == -2 || finder1 == -3){             //Добавляем элемент
        release = 1;
        int new_version = 1;
        table->ks1[csize_now].key1 = key1;
        table->ks1[csize_now].release = new_version;
        table->ks1[csize_now].busy = 1;
        item = create_item(key1,key2,num_info,info,release,last_item,new_version);
        table->ks1[csize_now].item = item;
        if (table->ks2[hash].list == NULL){
            table->ks2[hash].list = create_list(key2,item);
        }
        else{
            table->ks2[hash].list = add_to_list(key2,item,table->ks2[hash].list);
        }
        table->csize1 += 1;

        return 3;
    }
}


int Hash_function(char *key2){
    int len = strlen(key2);
    return ((11 + len) % Size);
}

Item *find_key2(Table *table, char *key2){
    int hash = Hash_function(key2);
    list *str = table->ks2[hash].list;
    if(str == NULL){
        return NULL;                               // Нет ни одного элемента
    }
    else{
        while(str != NULL){
            if(strcmp(str->key2,key2) == 0)
                    return str->item;         // Элемент найден

            else{
                str = str->next;
            }
        }
        return NULL;                          //Элементы есть, но с таким ключом нет
    }
}

list *create_list(char *key2,Item *item){
    list *List = (list*)calloc(1,sizeof(list));
    strcpy(List->key2,key2);
    List->item = item;
    List->next = NULL;
    return List;
}

list *add_to_list(char *key2,Item *item,list *list1){
    list *List = (list*)calloc(1,sizeof(list));
    List->next = list1;
    List->item = item;
    strcpy(List->key2,key2);
    return List;
}

void delete_item_by_KeySpace2(KeySpace2 *ks2,char *key2){
    int hash = Hash_function(key2);
    list *str = ks2[hash].list;
    while(str != NULL){
        if(strcmp(str->key2,key2) == 0 && ks2[hash].list != str){
            ks2[hash].list = delete_elem(ks2[hash].list,str);
            break;
        }
        else if(strcmp(str->key2,key2) == 0 && ks2[hash].list == str){
            ks2[hash].list = list_delete_head(ks2[hash].list);
            break;
        }
        else{
            str = str->next;
        }
    }
}

list *delete_elem(list *head,list *elem){   //Удаление элемента списка
    list * temp = head;
    while (temp->next != elem){
        temp = temp->next;
    }
    temp->next = elem->next;
    free(elem);

    return head;
}

list* list_delete_head(list* head){
    list* temp = head->next;
    free(head);
    return temp;
}