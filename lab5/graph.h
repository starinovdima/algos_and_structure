#ifndef LABA5_GRAPH_H
#define LABA5_GRAPH_H

typedef struct list {
    int name;
    int index;
    float weight;
    struct list *next;
}list;

typedef struct graph {
    int name;
    float x;
    float y;
    list *list;
}graph;



void int_input1(int *a);
void float_input1(float *a);
int dialog(const char *msgs[], int n);
int add_vertex(graph **gr,int name,float x,float y,int *size);
void question(int *answer);
int output_to_file(graph *gr,int size);
float add_edge(graph **grc,int name1,int name2,int size);
int delete_vertex(graph **gr,int name,int *size);
int delete_edge(graph **gr,int name1,int name2,int size);
int print_graph(graph *gr,int size);
int find_way(graph *gr,int name1,int name2,int size);
int find_shortest_way(graph *gr,int name1,int name2,int size);
int decomposition(graph *gr,int size);
int DFS_2(graph *gr,int i,int *colour,int *time,int *v);
int loading(graph **gr,int *size);
void create_item(graph **gr,int name,float x, float y,int size);
int searching(graph *gr,int name,int size);
list *create_list(int name,float weight);
list *add_to_list(int name,float weight,list *last);
list *list_delete_el(list *head,list *el);
list *list_delete_head(list *head);
float find_weight(graph *a,graph *b);
void free_graph(graph *gr,int size);
int random_graph(graph **gr,int num_size,int *size);
int proverka(graph *gr,int i1,int name1);
int DFS_1(graph *gr,int i,int *colour,int *prev,int color);
int graphiz(graph *gr,int size);
int find_index(int size,const int *v,const float *d);
void output_way(int ind2,const int *prev,int name2,int size,graph *gr);
void output_interisting_graph(const int *tim, int size,int count,const int *mas);
void put_in_mas(int *mas,int *v,int size);
int D_Timing();

#endif //LABA5_GRAPH_H
