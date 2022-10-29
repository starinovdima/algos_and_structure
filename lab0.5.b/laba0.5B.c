#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Item{

    char c;
    struct Item *next;

}Item;

Item *deleteList(Item *ptr){       //Очистка
    Item *tmp = NULL;
    while(ptr != NULL){
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    return ptr;
}

int getList (Item **a, int *n) {
    char buf[81] = {0}, *str;
    int fl = 0;
    Item head = {'*',NULL};
    Item *last = &head;
    do{
        *n = scanf("%80[^\n]",buf);
        if (*n < 0){
            deleteList(head.next);
            head.next = NULL;
            continue;
        }
        if (*n > 0) {
            for (str = buf; *str != '\0'; ++str) {
                if (fl == 1){
                    last->c = *str;
                    fl = 0;
                }else{
                    last->next = (Item *) malloc(sizeof(Item));
                    if(last->next == NULL) {
                        printf("Error with memory");
                        free(last->next);
                        deleteList(head.next);
                        return -1;
                    }
                    last = last->next;
                    last->c = *str;
                }
            }
            last->next = (Item *) malloc(sizeof(Item));
            if(last->next == NULL) {
                printf("Error with memory");
                free(last->next);
                deleteList(head.next);
                return -1;
            }
            last = last->next;
            last->c = ' ';
            last->next = NULL;
            fl = 1;
        }

        if (strlen(buf) < 80 && fl == 1)
            scanf("%*c");

        if (*n == 0) {
            scanf("%*c");
            last->next = (Item *) malloc(sizeof(Item));
            if(last->next == NULL) {
                printf("Error with memory");
                free(last->next);
                deleteList(head.next);
                return -1;
            }
            last = last->next;
            last->c = ' ';
            last->next = NULL;


        }

    }while (*n > 0 && strlen(buf) == 80);
    *a = head.next;
    return 0;
}

void output(Item *ptr){
    Item *p;
    p = ptr;
    while (p != NULL){
        printf("%c",p->c);
        p = p->next;
    }
}

int probel_list(Item *ptr) {//Вставляем пробелы между группами
    Item *list = ptr;
    Item *str,*p;
    while(list->next != NULL){
        if(list->c == list->next->c)
            list = list->next;
        else{
            str = (Item *)malloc(sizeof(Item));
            if(str == NULL) {
                printf("Error with memory");
                free(str);
                deleteList(list);
                return -1;
            }
            p = list->next;
            list->next = str;
            str->c = ' ';
            str->next = p;
            list = str->next;
        }

    }
    return 0;
}

int add_space(Item *ptr){
    Item *list = ptr;
    Item *str,*p;
    while(list->next != NULL){
        if(isspace(list->c)) {
            if (isspace(list->c) && isspace(list->next->c))
                list = list->next;
            else {
                str = (Item *) malloc(sizeof(Item));
                if(str == NULL) {
                    printf("Error with memory");
                    free(str);
                    deleteList(list);
                    return -1;
                }
                p = list->next;
                list->next = str;
                str->c = list->c;
                str->next = p;
                list = str->next;
            }

        }
        else{
            list = list->next;
        }
    }
    return 0;
}

Item* list_delete_head(Item* head){
    Item* temp = head->next;
    free(head);
    return temp;
}

Item *delete_elem(Item *head,Item *elem){   //Удаление элемента списка
    Item* temp = head;
    while (temp->next != elem){
        temp = temp->next;
    }
    temp->next = elem->next;
    free(elem);

    return head;
}

void remove_spaces(Item *ptr){
    Item *str = ptr;
    while(str->next != NULL){
        if(isspace(str->c) && isspace(str->next->c))
            delete_elem(ptr,str->next);
        else
            str = str->next;
    }
}

Item *work_list(Item *head){                     //Находим группы и удаляем лишние элементы
    int j = 0;
    Item *gtr = NULL;
    j = add_space(head);
    if (j == -1)
        return gtr;
    int flag = 0 ;
    Item *ptr = head;
    while(ptr->next != NULL){
        if(ptr->c == ptr->next->c || flag == 1){
            if(ptr->c == ptr->next->c){
                flag = 1;
                ptr = ptr->next;
            }

            else{
                flag = 0;
                ptr = ptr->next;
            }

        }
        else{
            if(head != ptr){
                ptr->c = ' ';
                ptr = ptr->next;
            }
            else {
                head = list_delete_head(head);
                ptr = head;

            }
        }
    }
    j = probel_list(head);
    if (j == -1)
        return gtr;
    remove_spaces(head);

    return head;
}

Item *proverka(Item *ptr){
    if (ptr->c == ' ' && ptr->next == NULL)
        printf(" Empty list");

    return ptr;
}

int main(){
    printf("      LAB 0.5B");

    Item *str;
    int num;
    int p = 0;

    do{
        printf("\n\nInput string, please: ");
        p = getList(&str,&num);
        if (str == NULL || p == -1)
            break;
        printf("\nThe entered string:");
        output(str);
        str = work_list(str);
        if(str == NULL)
            break;
        printf("\n\nReworked string:");
        proverka(str);
        output(str);
        deleteList(str);

    }while(str);

    deleteList(str);

    return 0;
}