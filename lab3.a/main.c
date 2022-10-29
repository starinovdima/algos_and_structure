#include <stdio.h>
#include "table.h"
#include <stdlib.h>

const char *MSGS[] = {"0.Quit", "1.Add new element","2.Search element by two keys",
                      "3.Delete element by one key","4.Search by any one key",
                      "5.Table output","6.Delete element by two keys",
                      "7.Reorganization first table"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main() {
    Table *table = table_selection();
    int c, what,num,p,l,answer,versus,d,del = -1;
    int key1;
    Item *now = NULL;
    char key2[30];
    char *str = NULL;
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch(c) {
            case 0:
                printf("***\nQuit\n***\n");
                free_table(table);
                break;
            case 1:
                printf("***\nAdd new element\n***\n");
                enter_keys(&key1, key2);
                printf("Enter two integer numbers:");
                do{
                int_input(&p);
                if(p < 9 || p>99){
                    printf("Please, enter correctly: ");
                    num = 0;
                }
                else
                    num = 1;
                }while(num == 0);
                str = get_str();
                what = add_element(table,key1,key2,str,p);
                if(what == 1) {
                    printf("The table is full, do reorganization please! ");
                }
                else if(what == 5){
                 printf("The Key2 cannot be repeated!");
                }
                else if(what == 4){
                    printf("The new version of the item has been recorded ");
                }
                else if (what == 2){
                    printf("The new version of the item in first space has been recorded ");
                }
                else if (what == 3){
                    printf("Item added\n");
                }
                free(str);
                break;
            case 2:
                printf("***\nSearch element by two keys\n***\n");
                enter_keys(&key1, key2);
                now = find_key2(table,key2);
                if (now == NULL || now->key1 != key1)
                    printf("\n******Item not found******\n");
                else {
                    printf("Item found:\n");
                    output_item(now);
                }
                break;
            case 3:
                printf("***\nDelete element by one key\n***\n");
                printf("What key do you want to delete: if key1 enter 1, if key2 enter 2 -> ");
                do{
                    int_input(&answer);
                    if(answer < 1 || answer > 2){
                        printf("Please, enter correctly -> ");
                        num = 0;
                    }
                    else
                        num = 1;
                }while(num == 0);
                if (answer == 1){
                    printf("Enter the first key:\n");
                    int_input(&key1);
                    l = find_key1(table,key1);
                    if(l == -2 || l == -3)
                        printf("\n******Item not found******\n");
                    else{
                        printf("Item found and has some versions \n");
                        printf("If you want to remove all versions enter  1,"
                               " if you want to remove a specific version enter  2 ->");
                        do{
                            int_input(&answer);
                            if(answer < 1 || answer > 2){
                                printf("Please, enter correctly -> ");
                                num = 0;
                            }
                            else
                                num = 1;
                        }while(num == 0);
                        if(answer == 1){
                            delete_item_by(table,del,key1);
                            printf("All versions of the item removed");
                        }
                        else{
                            printf("Enter version->");
                            int_input(&versus);
                            p = delete_item_by(table,versus,key1);
                            if (p == -1)
                                printf("There is no such version, repeat the operation!");
                            else
                                printf("Item removed!");
                        }
                    }
                }
                else{
                    printf("Enter the second key (no more than 30 symbols):\n");
                    scanf("%s",key2);
                    scanf("%*c");
                    now = find_key2(table,key2);
                    if (now == NULL)
                        printf("\n******Item not found******\n");
                    else{
                        delete_item_by(table,table->ks2[Hash_function(key2)].list->item->version,now->key1);
                        printf("Item removed!");
                        break;
                    }
                }
                break;
            case 4:
                printf("***\nSearch by any one key\n***\n");
                printf("What key to search for: if key1 enter 1, if key2 enter 2 -> ");
                do{
                    int_input(&answer);
                    if(answer < 1 || answer > 2){
                        printf("Please, enter correctly -> ");
                        num = 0;
                    }
                    else
                        num = 1;
                }while(num == 0);
                if (answer == 1){
                    printf("Enter the first key:\n");
                    int_input(&key1);
                    l = output_all_versions(table,key1);
                    if(l == -2)
                        printf("\n******Item not found******\n");
                }
                else{
                    printf("Enter the second key (no more than 30 symbols):\n");
                    scanf("%s",key2);
                    scanf("%*c");
                    now = find_key2(table,key2);
                    if (now == NULL)
                        printf("\n******Item not found******\n");
                    else{
                        printf("Item found:\n");
                        output_item(now);
                    }
                }
                break;
            case 5:
                printf("***\nTable output\n***\n");
                show_table2(table);
                break;
            case 6:
                printf("***\nDelete element by two keys\n***\n");
                enter_keys(&key1, key2);
                now = find_key2(table,key2);
                if (now == NULL || now->key1 != key1)
                    printf("\n******Item not found******\n");
                else{
                    delete_item_by(table,table->ks2[Hash_function(key2)].list->item->version,now->key1);
                    printf("Item deleted!");
                }
                break;
            case 7:
                printf("***\nReorganization first table\n***\n");
                Reorganization_first_table(table);
                show_table(table);
                break;
        }
    } while (c != 0);
    return 0;
}
