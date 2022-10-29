#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "kd_tree.h"

const char *MSGS[] = {"0.Quit", "1.Add new element","2.Find element",
                      "3.Delete element","4.Output keys and info","5.Output tree",
                      "6.Finding the key of the most distant","7.Load from file","8.Timing!","9.Graphviz to file"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);



int main() {
    int c = 0;
    int key1,key2,num,k,result;
    char *str = NULL;
    Tree *tree = NULL;
    Tree *search = NULL;
    int def = 0;
    FILE *output;
    do {
        c = dialog1(MSGS, MSGS_SIZE);
        switch(c) {
            case 0:
                fre_tree(tree);
                break;
            case 1:
                printf("***\nAdd new element\n***\n");
                printf("Enter key1 please->\n");
                int_input(&key1);
                printf("Enter key2 please->\n");
                int_input(&key2);
                printf("Enter two integer numbers:");
                do{
                    int_input(&num);
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
                result = add_element(&tree,key1,key2,num,str);
                if(result == 0)
                    printf("\nElement added!\n");
                else
                    printf("Error,this item exits!");
                free(str);
                break;
            case 2:
                printf("***\nFind element\n***\n");
                printf("Enter key1 please->\n");
                int_input(&key1);
                printf("Enter key2 please->\n");
                int_input(&key2);
                search = search_element(tree,key1,key2);
                if(search == NULL)
                    printf("This element not found!");
                else
                    output_element(search);
                break;
            case 3:
                printf("***\nDelete element\n***\n");
                printf("Enter key1 please->\n");
                int_input(&key1);
                printf("Enter key2 please->\n");
                int_input(&key2);
                search = search_element(tree,key1,key2);
                if(search == NULL)
                    printf("This element not found!");
                else {
                    delete_element(&tree,search);
                    printf("Item deleted!");
                }
                break;
            case 4:
                printf("***\nOutput keys and info\n***\n");
                result = output_keys(tree);
                if(result == 0){
                    printf("Tree is empty");
                }
                break;
            case 5:
                printf("***\nOutput tree\n***\n");
                if(tree == NULL){
                    printf("\nTree is empty\n");
                }
                else {
                    print(tree, 0);
                }
                break;
            case 6:
                printf("***\nFinding the key of the most distant\n***\n");
                if(tree == NULL){
                    printf("Table is empty");
                }else {
                    search = find_biggest(tree);
                    output_element(search);
                }
                break;
            case 7:
                printf("***\nLoad from file\n***\n");
                result = loadingg(&tree);
                if(result == -1)
                    printf("\nError\n");
                else
                    def = result;
                break;
            case 8:
                printf("***\nTiming\n***\n");
                D_Timing();
                break;
            case 9:
                printf("***\nGraphviz to file\n***\n");
                char one[12] = {"digraph G {"};
                char two[2] = {"}"};
                output = fopen("C:\\Users\\79885\\CLionProjects\\Laba4BBB\\graphiz.txt", "w");
                if(output == NULL) {
                    printf("Error");
                    return -1;
                }
                else{
                      fprintf(output, "%s\n", one);
                      grapvhiz(tree, output);
                      fprintf(output, "%s", two);
                }
                fclose(output);
                break;
        }
    } while (c != 0);

    return 0;
}


int D_Timing()
{
    Tree *EList = NULL;
    Tree *root = EList;
    int keys1[10000];
    int keys2[10000];
    int key1,key2;
    int n = 10,cnt = 10000, i, m;
    clock_t first, last;
    srand(time(NULL));
    while (n-- > 0){
        for(i = 0;i < 10000;i++){
            keys1[i] = rand()/100;
            keys2[i] = rand()/10;
        }

        for (i = 0; i < 10000; ){
            key1 = rand()/100;
            key2 = rand()/10;
            if (add_element(&root,key1,key2,11,"hello") == 0) {
                ++i;
            }
        }
        m = 0;
        first = clock();
        for (i = 0; i < 10000; ++i) {
            if (search_element(root,keys1[i],keys2[i]) != NULL) {
                m++;
            }
        }
        last = clock();
        printf("%d items was found\n", m);
        printf("test #%d, number of nodes = %d, time = %lf\n", 10 - n, (10 - n)*cnt, (double)(last - first));
    }
    fre_tree(root);

    return 1;
}