#include "kd_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int dialog1(const char *msgs[], int n) {
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

int fre_tree(Tree *tree){      //Концевой обход
    if(tree == NULL){
        return 0;
    }
    fre_tree(tree->left);
    fre_tree(tree->right);
    free(tree->info->str);
    free(tree->info);
    free(tree);
    return 0;
}

int print(Tree *ptr, int space){           //центрированный обход
    if(ptr == NULL)
        return 0;
    print(ptr->right, space + 1);
    for(int i=0; i<space;i++, printf("          "));
    if(ptr->par != NULL) {
        if (ptr->par->left == ptr)
            printf("\\ ");
        else
            printf("/ ");
    }
    printf("x:%d|y:%d\n", ptr->key[0],ptr->key[1]);
    print(ptr->left, space + 1);
    return 0;
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
            scanf("%*s");

        }
    } while (n <= 0);
}

Tree *create_element(int key1,int key2,int num_info,char *info,int remember,Tree *par){
    Tree *element = (Tree*)calloc(1,sizeof(Tree));
    element->par = par;
    element->key[0] = key1;
    element->key[1] = key2;
    element->remember = remember;
    Info *informat = (Info*)calloc(1,sizeof(Info));
    informat->str = (char*)calloc(strlen(info)+1,sizeof(char));
    strcpy(informat->str,info);
    informat->num_info = num_info;
    element->info = informat;
    return element;
}

int add_element(Tree **tree,int key1,int key2,int num_info,char *info){
    Tree *now = *tree;
    Tree *par = NULL;
    Tree *search = search_element(*tree,key1,key2);
    if(search != NULL)
        return -1;
    if(now == NULL){
        *tree = create_element(key1,key2,num_info,info,0,NULL);
        return 0;
    }else{
        int depth = 0;
        while(now != NULL){
            par = now;
            if(depth % 2 == 0){
                if(key1 <= now->key[0])
                    now = now->left;
                else now = now->right;
                depth += 1;
            }else{
                if(key2 < now->key[1])
                    now = now->left;
                else now = now->right;
                depth += 1;
            }
        }
        if(depth % 2 == 1){
            if(key1 <= par->key[0])
                par->left = create_element(key1,key2,num_info,info,1,par);
            else
                par->right = create_element(key1,key2,num_info,info,1,par);
        }else{
            if(key2 <= par->key[1])
                par->left = create_element(key1,key2,num_info,info,0,par);
            else
                par->right = create_element(key1,key2,num_info,info,0,par);
        }
    }

    return 0;

}

int delete_element(Tree **tree,Tree *element){
    if(element->right == NULL && element->left == NULL)
        delete1(tree,element);
    else if(element->right == NULL || element->left == NULL)
        delete2(tree,element);
    else if(element->right != NULL && element->left != NULL)
        delete3(element);
    return 0;
}

int delete1(Tree **tree,Tree *element){
    Tree *par = element->par;
    if(element->par != NULL) {
        if (par->left == element) {
            par->left = NULL;
        } else {
            par->right = NULL;
        }
        delete_item(element);
    }else{
        delete_item(element);
        *tree = NULL;
    }
    return 0;
}

int delete2(Tree **tree,Tree *element){
    Tree *par = element->par;
    if(par != NULL) {
        if (par->left == element) {
            if (element->left != NULL){
                par->left = element->left;
                element->left->par = par;
            }else {
                par->left = element->right;
                element->right->par = par;
            }rebuild(par->left);
        } else {
            if (element->left != NULL) {
                par->right = element->left;
                element->left->par = par;
            }else {
                par->right = element->right;
                element->right->par = par;
            }
            rebuild(par->right);
        }
        delete_item(element);
    }
    else{
        if(element->right != NULL)
            *tree = element->right;
        else
            *tree = element->left;
        (*tree)->remember = 0;
        (*tree)->par = NULL;
        delete_item(element);
    }
    return 0;
}

int delete3(Tree *element){
    Tree *el = NULL,*tree = NULL;
    Info *del = NULL;
    el = find_element(element);
    element->key[0] = el->key[0];
    element->key[1] = el->key[1];
    del = element->info;
    element->info = el->info;
    el->info = del;
    if(el->right == NULL && el->left == NULL)
        if(element->right != el)
            delete1(&tree, el);
        else{
            delete1(&tree,el);
            rebuild(element);
        }
    else if(el->right == NULL && el->left == NULL)
        delete3(el);
    else if (el->right == NULL || el->left == NULL)
        delete2(&tree,el);


    return 0;

}
int rebuild(Tree *gr){
    if(gr == NULL)
        return 0;
    if(gr->remember == 0)
        gr->remember = 1;
    else gr->remember = 0;
    int i = gr->remember;
    if(gr->right != NULL && gr->left != NULL){
        if(gr->left->key[i] > gr->key[i]) {
            Tree *in = gr->right;
            gr->right = gr->left;
            gr->left = in;
        }
        rebuild(gr->left);
        rebuild(gr->right);
//0,0
//-1,-1 1,-1
    }else if(gr->right != NULL || gr->left != NULL){
        if(gr->right != NULL){
            if(gr->right->key[i] < gr->key[i]){
                gr->left = gr->right;
                gr->right = NULL;
            }
            if(gr->right == NULL)
                rebuild(gr->left);
            else rebuild(gr->right);
        }else{
            if(gr->left->key[i] > gr->key[i]) {
                gr->right = gr->left;
                gr->left = NULL;
            }
            if(gr->left == NULL)
                rebuild(gr->right);
            else rebuild(gr->left);
        }
    }

    return 0;
}

Tree *find_element(Tree *element){
    int i = element->remember;
    Tree *nxt = find_next(element->right,element->remember);
    Tree *prev = find_prev(element->left,element->remember);
    if(nxt == NULL && prev == NULL){
        nxt = find_prev(element->right,element->remember);
        prev = find_next(element->left,element->remember);
        if(nxt == NULL && prev == NULL)
            return element->right;
        else if(nxt != NULL || prev != NULL){
            if(nxt == NULL)
                return prev;
            else
                return nxt;
        }else{
            if(prev->key[i] > nxt->key[i])
                return prev;
            else
                return nxt;
        }
    }else if(nxt == NULL || prev == NULL){
        if(nxt == NULL)
            return prev;
        else
            return nxt;
    }else{
        if(prev->key[i] > nxt->key[i])
            return prev;
        else
            return nxt;
    }
}

Tree *find_next(Tree *el,int remember){
    int count = 0;
    Tree *ptr = el;
    while(ptr->left != NULL){
        if(ptr->remember == remember)
            count += 1;
        ptr = ptr->left;
    }
    if(ptr->remember == remember)
        return ptr;
    if(count == 0)
        return NULL;
    else {
        while (ptr != el) {
            if (ptr->remember == remember)
                return ptr;
            ptr = ptr->par;
        }
    }
    return NULL;
}

Tree *find_prev(Tree *el,int remember){
    int count = 0;
    Tree *ptr = el;
    while(ptr->right != NULL){
        if(ptr->remember == remember)
            count += 1;
        ptr = ptr->right;
    }
    if(ptr->remember == remember)
        return ptr;
    if(count == 0)
        return NULL;
    else {
        while (ptr != el) {
            if (ptr->remember == remember)
                return ptr;
            ptr = ptr->par;
        }
    }
    return NULL;
}
void delete_item(Tree *element){
    free(element->info->str);
    free(element->info);
    free(element);
}


void output_element(Tree *el){
    printf("Item[] - key1:%d key2:%d info:%d %s\n",el->key[0],el->key[1],el->info->num_info,el->info->str);
}

int output_keys(Tree *tree) {
    if(tree == NULL)
        return 0;
    Tree *ptr = tree;
    printf("output by x:\n");
    outputkeys1(ptr);
    printf("output by y:\n");
    outputkeys2(ptr);
    return -1;
}

int outputkeys1(Tree *tree){
    if(tree == NULL)
        return 0;
    outputkeys1(tree->right);
    if(tree->remember == 1)
        output_element(tree);
    outputkeys1(tree->left);
    return 0;
}
int outputkeys2(Tree *tree){
    if(tree == NULL)
        return 0;
    outputkeys2(tree->right);
    if(tree->remember == 0)
        output_element(tree);
    outputkeys2(tree->left);
    return 0;
}

Tree *search_element(Tree *tree, int key1,int key2){
    Tree *now = tree;
    if(now == NULL)
        return NULL;
    int depth = 0;
    while(now != NULL){
        if(now->key[0] == key1 && now->key[1] == key2)
            return now;
        if(depth % 2 == 0){
            if(key1 < now->key[0])
                now = now->left;
            else now = now->right;
            depth += 1;
        }else{
            if(key2 < now->key[1])
                now = now->left;
            else now = now->right;
            depth += 1;
        }
    }
    return NULL;
}

Tree *find_biggest(Tree *tree){
    if(tree == NULL)
        return NULL;
    Tree *big = tree;
    biggest_element(tree,&big);
    return big;
}

int biggest_element(Tree *tree,Tree **search){
    if(tree == NULL)
        return 0;
    biggest_element(tree->right,search);
    if((tree->key[0]*tree->key[0]+tree->key[1]*tree->key[1])>((*search)->key[0]*(*search)->key[0]+(*search)->key[1]*(*search)->key[1]))
        *search = tree;
    biggest_element(tree->left,search);
    return 0;
}


int loadingg(Tree **tree){
    FILE *txt;
    int key1,key2;
    int num_info = 0;
    char info[1000];
    txt = fopen("C:\\Users\\79885\\CLionProjects\\Laba4BBB\\input.txt", "r");
    if(txt == NULL)
        return -1;
    else{
        while(!feof(txt)){
            fscanf(txt, "%d\n", &key1);
            fscanf(txt, "%d\n", &key2);
            fscanf(txt, "%d\n", &num_info);
            fscanf(txt, "%s\n", info);
            add_element(tree,key1,key2,num_info,info);
        }
    }
    fclose(txt);
    return 0;
}

int grapvhiz(Tree *tree,FILE *output){
    if(tree == NULL)
        return 0;
    if(tree->left != NULL && tree->right != NULL)
        fprintf(output,"\"%d|%d\"->\"%d|%d\",\"%d|%d\"\n",tree->key[0],tree->key[1],tree->left->key[0],tree->left->key[1],tree->right->key[0],tree->right->key[1]);
    else if(tree->left == NULL || tree->right == NULL){
        if(tree->left == NULL && tree->right != NULL)
            fprintf(output,"\"%d|%d\"->\"%d|%d\"\n",tree->key[0],tree->key[1],tree->right->key[0],tree->right->key[1]);
        else if(tree->right == NULL && tree->left != NULL)
            fprintf(output,"\"%d|%d\"->\"%d|%d\"\n",tree->key[0],tree->key[1],tree->left->key[0],tree->left->key[1]);
    }
    grapvhiz(tree->left,output);
    grapvhiz(tree->right,output);
    return 0;
}