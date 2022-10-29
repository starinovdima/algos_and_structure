#include <stdio.h>
#include <time.h>
#include "graph.h"
#include <stdlib.h>

const char *MSGS[] = {"0.Quit", "1.Adding a new vertex to the graph","2.Adding a new edge to the graph ",
                      "3.Removing a given vertex from a graph","4.Removing a given edge from the graph","5.Print graph",
                      "6.Search for some given vertex from another given vertex","7.Finding the shortest path between two given vertices of the graph",
                      "8.Graph decomposition","9.Load from file","10.Random graph","11.Timing!1","12.Graphiz to file","13.Save this?"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main(){
    graph *gr = NULL;
    graph **ptr = &gr;
    int c;
    int name,result,quest,num,size = 0;
    int name1,name2;
    float x,y,weight;
    FILE *GR;
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch(c) {
            case 0:
                printf("***\nQuit\n***\n");
                free_graph(gr,size);
                break;
            case 1:
                printf("***\nAdding a new vertex to the graph\n***\n");
                printf("Enter the name of the graph:\n");
                int_input1(&name);
                printf("Enter x->");
                float_input1(&x);
                printf("Enter y->");
                float_input1(&y);
                result = add_vertex(&gr,name,x,y,&size);
                if(result == -1)
                    printf("\nError, such a peak exists\n");
                else {
                    printf("\nElement added!\n");
                }
                break;
            case 2:
                printf("***\nAdding a new edge to the graph \n***\n");
                printf("Enter the name of the graph1:\n");
                int_input1(&name1);
                printf("Enter the name of the graph2:\n");
                int_input1(&name2);
                weight = add_edge(&gr,name1,name2,size);
                if(weight == -1)
                    printf("\nError, such a peak exists\n");
                else if(weight == -2)
                    printf("\nThis edge already exists!\n");
                else {
                    printf("\nElement added!\n");
                    printf("\nRib weight = %f \n",weight);
                }
                break;
            case 3:
                printf("***\nRemoving a given vertex from a graph\n***\n");
                printf("Enter the name of the graph:\n");
                int_input1(&name);
                result = delete_vertex(&gr,name,&size);
                if(result == -1)
                    printf("\nError, such a peak exists\n");
                else {
                    printf("\nElement deleted!\n");
                }
                break;
            case 4:
                printf("***\nRemoving a given edge from the graph;\n***\n");
                printf("Enter the name of the graph1:\n");
                int_input1(&name1);
                printf("Enter the name of the graph2:\n");
                int_input1(&name2);
                result = delete_edge(&gr,name1,name2,size);
                if(result == -1)
                    printf("\nError, such a peak exists\n");
                else if(result == -2)
                    printf("\nVertices are not adjacent!\n");
                else {
                    printf("\nElement deleted!\n");
                }
                break;
            case 5:
                printf("***\nPrint graph\n***\n");
                result = print_graph(gr,size);
                if(result == -1)
                    printf("Empty!\n");
                break;
            case 6:
                printf("***\nSearch for some given vertex from another given vertex\n***\n");
                printf("Enter the name of the graph1:\n");
                int_input1(&name1);
                printf("Enter the name of the graph2:\n");
                int_input1(&name2);
                result = find_way(gr,name1,name2,size);
                if(result == -1)
                    printf("\nError, such a peak exists\n");
                else if(result == -2)
                    printf("\nThere is no way\n");
                else{
                    printf("\nPath found!\n");
                }
                break;
            case 7:
                printf("***\nFinding the shortest path between two given vertices of the graph\n***\n");
                printf("Enter the name of the graph1:\n");
                int_input1(&name1);
                printf("Enter the name of the graph2:\n");
                int_input1(&name2);
                result = find_shortest_way(gr,name1,name2,size);
                if(result == -1)
                    printf("\nError, such a peak exists\n");
                else if(result == -2)
                    printf("\nThere is no way!\n");
                break;
            case 8:
                printf("***\nGraph decomposition\n***\n");
                decomposition(gr,size);

                break;
            case 9:
                printf("***\nLoad from file\n***\n");
                result = loading(&gr,&size);
                if(result == -1)
                    printf("Error");
                break;
            case 10:
                printf("***\nRandom graph\n***\n");
                printf("Enter size graph's->");
                int_input1(&num);
                random_graph(&gr,num,&size);
                printf("\nThe graph was built!\n");
                break;
            case 11:
                printf("***\nTiming!\n***\n");
                D_Timing();
                break;
            case 12:
                printf("***\nGraphiz to file\n***\n");

                result = graphiz(gr,size);
                if(result == -1)
                    printf("ERROR");
                break;
            case 13:
                printf("***\nSave this\n***\n");
                output_to_file(gr,size);
                break;
        }
    }while(c != 0);
    return 0;
}

int D_Timing(){

    graph *EList = NULL;
    graph *root = EList;
    int size = 0;
    int ind1[1000],ind2[1000];
    int n = 20,i, m;
    clock_t first, last;
    int k = 100;

    srand(time(NULL));

    while (n-- > 0){

        random_graph(&root,k,&size);
        k += 100;

        for(i = 0;i < 1000;i++){
            ind1[i] = rand()%1000;
            ind2[i] = rand()%1000;
        }
        m = 0;
        first = clock();

        for (i = 0; i < 1000; ++i) {
            int p = find_way(root,ind1[i],ind2[i],size);
            if (p != -2 && p != -1 ) {
                m++;
            }
        }
        last = clock();
        printf("%d items was found\n", m);
        printf("test #%d,\t time = %g\n", 20 - n, (double)(last - first)/CLK_TCK);
        free_graph(root,size);
        size = 0;
        root = NULL;
    }

    return 1;
}
