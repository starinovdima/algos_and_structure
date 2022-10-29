#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

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
        }else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = (char*)calloc(1,sizeof(char));
    }

    return res;
}

void int_input1(int *a)
{
    int n;
    do
    {
        n = scanf("%d", a);
        if (n == 0)
        {
            printf("Error, try again: ");
            scanf("%*s");
        }
        if (n > 0 && *a <= 0){
            printf("Enter natural int: ");
            scanf("%*c");
            n = -1;
        }
    } while (n <= 0);
}

int free_tree(Tree *tree){      //Концевой обход
    Item *last_item = NULL;
    if(tree == NULL){
        return 0;
    }
    free_tree(tree->left);
    free_tree(tree->right);
    while(tree->item != NULL){
        last_item = tree->item;
        free(tree->item->info->str);
        free(tree->item->info);
        tree->item = tree->item->next;
        free(last_item);
    }
    free(tree->key);
    free(tree);
    return 0;
}

Tree *create_element(char *key,char *info,int num_info,Item *last_item,Tree *par){
    Tree *element = (Tree*)calloc(1,sizeof(Tree));
    element->key = (char*)calloc(strlen(key) + 1 ,sizeof(char));
    strcpy(element->key,key);
    element->item = create_item(info,num_info,last_item);
    element->parent = par;
    return element;
}

Item *create_item(char *info, int num_info,Item *last_item){
    Item *item = (Item*)calloc(1,sizeof(Item));
    item->info = (Info*)calloc(1,sizeof(Info));
    item->info->str = (char*)calloc(strlen(info) + 1 ,sizeof(char));
    strcpy(item->info->str,info);
    item->info->num_info = num_info;
    if(last_item == NULL){
        item->version = 1;
        item->next = NULL;
    }
    else{
        item->version = last_item->version + 1;
        item->next = last_item;
    }
    return item;
}

int output_element(Tree *element,int release){
    Item *item = element->item;
    while(item != NULL){
        if(item->version == release) {
            printf("\nItem[] - key:%s release-item:%d info:%d %s\n", element->key, item->version,
                   item->info->num_info, item->info->str);
            return 0;
        }
               item = item->next;
    }
    return -1;
}

int print_tree(Tree *ptr, int space){           //центрированный обход
    if(ptr == NULL)
        return 0;
    print_tree(ptr->right, space + 1);
    for(int i=0; i<space;i++, printf("      "));
    if(ptr->parent != NULL){
        if(ptr->parent->left == ptr)
            printf("\\ ");
        else
            printf("/ ");
    }
    printf("%s\n", ptr->key);
    print_tree(ptr->left, space + 1);
    return 0;
}

int output_tree(Tree *tree,FILE *output){
    if(tree == NULL)
        return 0;
    if(tree->left != NULL && tree->right != NULL)
        fprintf(output,"%s->%s,%s\n",tree->key,tree->left->key,tree->right->key);
    else if(tree->left == NULL || tree->right == NULL){
        if(tree->left == NULL && tree->right != NULL)
            fprintf(output,"%s->%s\n",tree->key,tree->right->key);
        else if(tree->right == NULL && tree->left != NULL)
            fprintf(output,"%s->%s\n",tree->key,tree->left->key);
    }
    output_tree(tree->left,output);
    output_tree(tree->right,output);
    return 0;
}

int output_keys(Tree *tree,char *key) {
    if(tree == NULL)
        return 0;

    output_keys(tree->left,key);
    if(strcmp(tree->key,key) > 0)
        printf("Key:%s  info:%d %s\n", tree->key,tree->item->info->num_info,tree->item->info->str);
    output_keys(tree->right,key);
    return 0;
}


int add_element_to_tree(Tree **tree,char *key,char *info,int num_info) {
    Tree *now = *tree;
    Item *last_item = NULL;
    Tree *par = NULL;
    if (now == NULL) {
        *tree = create_element(key, info, num_info, last_item,par);
        return 1;
    }
    else{
        par = find_way(*tree,key,num_info,info);
        if(par == NULL)
            return 2;
        else {
            if (strcmp(key, par->key) > 0) {
                par->right = create_element(key, info, num_info, last_item, par);
            } else {
                par->left = create_element(key, info, num_info, last_item, par);
            }
        }
    }
    return 1;
}

Tree *find_way(Tree *tree,char *key,int num_info,char *info){
    Tree *par = NULL;
    Tree *now = tree;

    while(now != NULL) {        //Итерационный алгоритм
        par = now;
        if (strcmp(key, now->key) > 0) {
            now = now->right;
        } else if (strcmp(key, now->key) < 0) {
            now = now->left;
        } else {
            now->item = create_item(info, num_info, now->item);
            return NULL;
        }
    }
    return par;
}

Tree *search_element(Tree *root,char *key){
    Tree *now = root;
    if(now == NULL)
        return NULL;
    else{
        while(now != NULL){                 //Итерационный алгоритм
            if(strcmp(now->key,key) == 0)

                return now;
            else if (strcmp(key, now->key) < 0)
                now = now->left;
            else
                now = now->right;
        }
    }
    return NULL;
}

int delete_element(Tree **tree,Tree *now,int release){
    int result;
    if(now->item->version != 1 && now->item->next != NULL){
        result = delete_item(now,release);
        if(result == -1)
            return -1;
    }
    else if(now->right == NULL && now->left == NULL){
           delete1(tree,now,release);
    }
    else if(now->right == NULL || now->left == NULL){
            delete2(tree,now,release);
    }
    else if(now->right != NULL && now->left != NULL){
        delete3(now,release);
    }
    return 0;
}

int delete1(Tree **tree, Tree *now,int release){
    Tree *par = now->parent;
    if(par != NULL) {
        if (par->left == now) {
            par->left = NULL;
        } else {
            par->right = NULL;
        }
        delete_item(now, release);
        free(now);
    }else{
        delete_item(now,release);
        free(now);
        *tree = NULL;
    }
    return 0;
}

int delete2(Tree **tree, Tree *now,int release){
    Tree *par = now->parent;
    if(par != NULL) {
        if (par->left == now) {
            if (now->left != NULL){
                par->left = now->left;
                now->left->parent = par;
            }else {
                par->left = now->right;
                now->right->parent = par;
            }
        } else {
            if (now->left != NULL) {
                par->right = now->left;
                now->left->parent = par;
            }else {
                par->right = now->right;
                now->right->parent = par;
            }
        }
        delete_item(now, release);
        free(now);
    }
    else{
        if(now->right != NULL)
            *tree = now->right;
        else
            *tree = now->left;
        delete_item(now,release);
        free(now);
    }
    return 0;
}
int delete3(Tree *now,int release){
    Tree *nxt = NULL, *next = NULL,*par2 = NULL;
    Item *del = NULL;
    nxt = find_next_element(now);
    next = nxt->right;
    par2 = nxt->parent;
    strcpy(now->key, nxt->key);
    del = now->item;
    now->item = nxt->item;
    nxt->item = del;
    if(nxt == now->right){
        now->right = next;
        if(now->right != NULL)
            next->parent = now;
    }
    else if(next == NULL)
        par2->left = NULL;
    else {
        next->parent = par2;
        par2->left = next;
    }
    delete_item(nxt,release);
    free(nxt);
    return 0;
}

Tree *find_next_element(Tree *el){
    Tree *ptr = el->right;
    while(ptr->left != NULL){
        ptr = ptr->left;
    }

    return ptr;

}

Tree *find_next(Tree *tree,char *key){
    Tree *now = tree;
    Tree *next = NULL;
    if(now == NULL)
        return NULL;
    else{
        while(now != NULL){                 //Итерационный алгоритм
            if(strcmp(key, now->key) < 0){
                next = now;
                now = now->left;
            }
            else{
                now = now->right;
            }
        }
    }
    return next;
}

Tree *find_prev(Tree *tree,char *key){
    Tree *now = tree;
    Tree *next = NULL;
    if(now == NULL)
        return NULL;
    else{
        while(now != NULL){                 //Итерационный алгоритм
            if(strcmp(key, now->key) < 0){
                next = now;
                now = now->right;
            }
            else{
                now = now->left;
            }
        }
    }
    return next;
}

Tree *choose(Tree *el1, Tree *el2,char *key){
    if(el1 == NULL)
        if(el2 != NULL) {
            if (strcmp(el2->key, key) != 0)
                return el2;
            else return NULL;
        }
        else return NULL;
    if(el2 == NULL)
        if(el1 != NULL){
            if(strcmp(el1->key,key) != 0)
                return el1;
            else return NULL;
        }else return NULL;

    if(strcmp(el1->key,el2->key) > 0)
        return el2;
    else if(strcmp(el1->key,el2->key) < 0)
        return el1;
}

int delete_item(Tree *el,int release){
    if(el->item->next == NULL){
        free(el->item->info->str);
        free(el->item->info);
        free(el->item);
        free(el->key);
    }
    else{
        Item *item1 = el->item;
        while(item1 != NULL){
            if(item1->version == release){
                if(item1 == el->item) {
                    el->item = list_delete_head(el->item);
                    return 0;
                }
                else{
                    el->item = delete_elem(el->item,item1);
                    return 0;
                }
            }
            else
                item1 = item1->next;
        }
        return -1;
    }
    return 0;
}

Item *delete_elem(Item *head,Item *elem){   //Удаление элемента списка
    Item * temp = head;
    while (temp->next != elem){
        temp = temp->next;
    }
    temp->next = elem->next;
    free(elem->info->str);
    free(elem->info);
    free(elem);

    return head;
}

Item* list_delete_head(Item* head){
    Item* temp = head->next;
    free(head->info->str);
    free(head->info);
    free(head);
    return temp;
}

int loading(Tree **tree){
    FILE *txt;
    int num_info = 0;
    char key[31], info[1000];
    txt = fopen("C:\\Users\\79885\\CLionProjects\\input.txt", "r");
    if(txt == NULL)
        return -1;
    else{
        while(!feof(txt)){
            fscanf(txt, "%s\n", key);
            fscanf(txt, "%d\n", &num_info);
            fscanf(txt, "%s\n", info);
            add_element_to_tree(tree,key,info,num_info);
        }
    }
    fclose(txt);
    return 0;
}













