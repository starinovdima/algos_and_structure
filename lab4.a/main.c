#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <time.h>
#include <string.h>

const char *MSGS[] = {"0.Quit", "1.Add new element","2.Find element",
                      "3.Delete element","4.Output keys and info","5.Output tree",
                      "6.Find key is similar by value ","7.Load from file","8.Timing!","9.Graphviz to file"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main(){
    int c,num,result,k;
    char *key = NULL;
    char *key1 = NULL;
    char *str = NULL;
    Tree *tree = NULL, *search, *search2, *chose;
    FILE *output;
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch(c) {
            case 0:
                printf("***\nQuit\n***\n");
                free_tree(tree);
                break;
            case 1:
                printf("***\nAdd new element\n***\n");
                printf("Enter key please->\n");
                key = get_str();
                printf("Enter two integer numbers:");
                do{
                    int_input1(&num);
                    if(num < 9 || num>99){
                        printf("Please, enter correctly: ");
                        k = 1;
                    }
                    else
                        k = 0;
                }while(k == 1);
                scanf("%*c");
                printf("Enter string with variable length -> ");
                str = get_str();
                result = add_element_to_tree(&tree,key,str,num);
                if(result == 1)
                    printf("Element added!");
                else if(result == 2)
                    printf("The new version of the item has been recorded!");
                free(str);
                free(key);
                break;
            case 2:
                printf("***\nSearch element by key\n***\n");
                printf("Enter key please->\n");
                key = get_str();
                search = search_element(tree,key);
                if(search == NULL)
                    printf("Element didn't find!\n");
                else{
                    if(search->item->next != NULL){
                        printf("Element founded and has versoins\n");
                        printf("What version would you want see? ->");
                        int_input1(&num);
                        result = output_element(search,num);
                        if(result == -1)
                            printf("There is no such version!");
                    }
                    else{
                        printf("Element founded and has one version\n");
                        output_element(search,search->item->version);
                    }
                }
                free(key);
                break;
            case 3:
                printf("***\nDelete element\n***\n");
                printf("Enter key please->\n");
                key = get_str();
                search = search_element(tree,key);
                if(search == NULL)
                    printf("This key not founded!");
                else{
                    if(search->item->next != NULL){
                        printf("Enter version that you want delete-> ");
                        int_input1(&num);
                        result = delete_element(&tree,search,num);
                        if(result == -1)
                            printf("There is no such version!");
                        else
                            printf("Item removed");
                    }
                    else{
                        delete_element(&tree,search,search->item->version);
                        printf("Item removed");
                    }
                }
                free(key);
                break;
            case 4:
                printf("***\nOutput keys and info\n***\n");
                printf("If you enter key you can see keys bigger that this key,else you can see all table\n");
                printf("Enter please ->");
                key = get_str();
                output_keys(tree,key);
                if(tree == NULL)
                    printf("\nTree is empty\n");
                free(key);
                break;
            case 5:
                printf("***\nOutput tree\n***\n");
                if(tree == NULL){
                    printf("\nTree is empty\n");
                }
                else {
                    print_tree(tree, 0);
                }
                break;
            case 6:
                printf("***\nFind key is similar by value\n***\n");
                printf("Enter key please->\n");
                key1 = get_str();
                search = find_next(tree,key1);
                search2 = find_prev(tree,key1);
                chose = choose(search,search2,key1);
                if(chose == NULL)
                    printf("Element didn't find!\n");
                else{
                    if(chose->item->next != NULL){
                        printf("Element founded and has versoins\n");
                        printf("What version would you want see? ->");
                        int_input1(&num);
                        result = output_element(chose,num);
                        if(result == -1)
                            printf("There is no such version!");
                    }
                    else{
                        printf("Element founded and has one version\n");
                        output_element(chose,chose->item->version);
                    }
                }
                free(key1);
                break;
            case 7:
                printf("***\nLoad from file\n***\n");
                result = loading(&tree);
                if(result == -1)
                    printf("Error");
                break;
            case 8:
                printf("***\nTiming\n***\n");
                D_Timing();
                break;
            case 9:
                printf("***\nGraphviz to file\n***\n");
                char one[12] = {"digraph G {"};
                char two[2] = {"}"};
                output = fopen("C:\\Users\\79885\\CLionProjects\\output.txt", "w");
                if(output == NULL)
                    return -1;
                else
                    fprintf(output,"%s\n",one);
                    output_tree(tree,output);
                    fprintf(output,"%s",two);
                fclose(output);
                break;
        }
        }while(c != 0);
    return 0;
}

int D_Timing()
{
    Tree *EList = NULL;
    Tree *root = EList;
    char *key[100000];
    char s[90];
    int p;

    for(int h = 0; h < 100000; h++)
        key[h] = (char *)calloc(90,sizeof(char));
    int n = 10,cnt = 10000, i, m;
    clock_t first, last;
    srand(time(NULL));
    while (n-- > 0){
        for(int k = 0; k < 100000; k++){
            for(p = 0; p < 89; p++)
                s[p] = rand()%26+'a';
            s[p] = '\0';
            strcpy(key[k],s);
        }
        for (i = 0; i < cnt; ){
            if (add_element_to_tree(&root,key[i],"hello",1))
                ++i;
        }
        m = 0;
        first = clock();
        for (i = 0; i < 100000; ++i) {
            if (search_element(root, key[i])) {
                m++;
            }
        }
        last = clock();
        printf("%d items was found\n", m);
        printf("test #%d, number of nodes = %d, time = %lf\n", 10 - n, (10 - n)*cnt, (double)(last - first)/CLK_TCK);
    }
    for(int h = 0; h < 100000; h++)
        free(key[h]);
    free_tree(root);
    return 1;
}
