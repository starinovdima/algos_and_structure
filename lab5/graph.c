#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
        scanf("%d", &choice);
        while (getchar() != '\n') {}
    } while (choice < 0 || choice >= n);
    return choice;
}

void free_graph(graph *gr,int size){
    for(int i = 0; i < size; i++){
        if(gr[i].list != NULL)
            while(gr[i].list != NULL){
                gr[i].list = list_delete_head(gr[i].list);
        }
    }
    free(gr);
}

void question(int *answer){
    int num;
    do{
        int_input1(answer);
        if(*answer < 1 || *answer > 2){
            printf("Please, enter correctly -> ");
            num = 0;
        }
        else
            num = 1;
    }while(num == 0);
}

void float_input1(float *a){
    int n;
    do
    {
        n = scanf("%f", a);
        if (n == 0)
        {
            printf("Error, try again: ");
            scanf("%*s");
        }
    } while (n <= 0);
}

void int_input1(int *a){
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

float find_weight(graph *a, graph *b){
    float weight = sqrtf(((a->x-b->x)*(a->x-b->x) + (a->y-b->y)*(a->y-b->y)));
    return weight;
}

int output_to_file(graph *gr,int size){
    FILE *output;
    graph *ptr = gr;

    output = fopen("C:\\Users\\79885\\CLionProjects\\Laba5\\input.txt","w");
    if(output == NULL)
        return -1;
    else if(gr != NULL) {
        fprintf(output, "%d\n", size);
        for (int i = 0; i < size; i++) {
            fprintf(output, "%d\n", ptr[i].name);
            fprintf(output, "%f\n", ptr[i].x);
            fprintf(output, "%f\n", ptr[i].y);

        }
        for (int i = 0; i < size; i++) {
            list *str = ptr[i].list;
            if (str != NULL) {
                while (str != NULL) {
                    fprintf(output, "%d\n", ptr[i].name);
                    fprintf(output, "%d\n", str->name);
                    str = str->next;
                }
            }
        }
    }
    fclose(output);
    return 0;
}


int loading(graph **gr,int *size){
    FILE *input;
    int index,name1,name2,coin,i = 0;
    float x,y;
    input = fopen("C:\\Users\\79885\\CLionProjects\\Laba5\\input.txt","r");
    if(input == NULL)
        return -1;
    else{
        fscanf(input,"%d\n",&coin);
        while(i < coin){
            fscanf(input, "%d\n", &index);
            fscanf(input, "%f\n", &x);
            fscanf(input, "%f\n", &y);
            add_vertex(gr,index,x,y,size);
            i += 1;
        }
        while(!feof(input)){
            fscanf(input,"%d\n",&name1);
            fscanf(input,"%d\n",&name2);
            add_edge(gr,name1,name2,*size);
        }
    }
    fclose(input);
    return 0;
}

int print_graph(graph *gr,int size){
    graph *ptr = gr;
    list *str;
    if(ptr == NULL)
        return -1;
    else{
        for(int i = 0; i < size; i++){
            printf("%d",ptr[i].name);
            if(ptr[i].list != NULL){
                printf("->");
                str = ptr[i].list;
                while (str->next != NULL){
                    printf("%d,",str->name);
                    str = str->next;
                }
                printf("%d\n",str->name);
            }else printf("\n");
        }
    }
    return 0;
}

void create_item(graph **gr,int name,float x, float y,int size){

    if(*gr == NULL)
        *gr = (graph *) calloc(1, sizeof(graph));
    else
        *gr = (graph*)realloc(*gr,(size + 1)*sizeof(graph));

    (*gr)[size].name = name;
    (*gr)[size].x = x;
    (*gr)[size].y = y;
    (*gr)[size].list = NULL;

}

int searching(graph *gr,int name,int size){
    graph *ptr = gr;
    for(int i = 0; i < size; i++){
        if(ptr[i].name == name)
            return i;
    }
    return -1;
}


int add_vertex(graph **gr,int name,float x,float y,int *size){

    if(*gr == NULL) {
        create_item(gr,name,x,y,*size);
        *size += 1;
    }
    else{
        int result = searching(*gr,name,*size);
        if(result != -1)
            return -1;
        else{
            create_item(gr,name,x,y,*size);
            *size += 1;
        }
    }
    return 0;
}

float add_edge(graph **grc,int name1,int name2,int size){
    graph *gr = *grc;
    if(name1 == name2)
        return -1;
    int i1 = searching(*grc,name1,size);
    if(i1 == -1)
        return -1;
    int i2 = searching(*grc,name2,size);
    if(i2 == -1)
        return -1;
    int result = proverka(gr,i1,name2);
    if(result == -1)
        return -2;
    float weight = find_weight(&gr[i1],&gr[i2]);
    if(gr[i1].list == NULL) {
        gr[i1].list = create_list(name2, weight);
        gr[i1].list->index = i2;
    }
    else {
        gr[i1].list = add_to_list(name2, weight, gr[i1].list);
        gr[i1].list->index = i2;
    }

    if(gr[i2].list == NULL) {
        gr[i2].list = create_list(name1, weight);
        gr[i2].list->index = i1;
    }
    else {
        gr[i2].list = add_to_list(name1, weight, gr[i2].list);
        gr[i2].list->index = i1;
    }
    return weight;
}

int delete_vertex(graph **gr,int name,int *size){
    graph *ptr = *gr;
    graph *cd;
    list *str = NULL;
    int name_last = ptr[*size-1].name;
    int i1 = searching(*gr,name,*size);
    if(i1 == -1)
        return -1;
    else if(*size == 1){
        cd = *gr;
        *gr =  NULL;
        free(cd);
        *size -= 1;
        return 0;
    }
    else{
        while(ptr[i1].list != NULL){
            ptr[i1].list = list_delete_head(ptr[i1].list);
        }
        for(int i = 0;i < *size;i++){
            str = ptr[i].list;
            while(str != NULL){
                if(str->name == name) {
                    if(str == ptr[i].list) {
                        ptr[i].list = list_delete_head(ptr[i].list);
                        str = ptr[i].list;
                    }
                    else {
                        ptr[i].list = list_delete_el(ptr[i].list, str);
                        str = ptr[i].list;
                    }
                }
                else if(str->name == name_last){
                    str->index = i1;
                    str = str->next;
                }
                else
                    str = str->next;
            }
        }

        ptr[i1] = ptr[(*size)-1];
        }
        *gr = (graph*)realloc(*gr,((*size)-1)*sizeof(graph));
        *size -= 1;

    return 0;
}

int delete_edge(graph **gr,int name1,int name2,int size){
    graph *ptr = *gr;
    int count = 0;
    list *str;
    int i1 = searching(*gr,name1,size);
    if(i1 == -1)
        return -1;
    int i2 = searching(*gr,name2,size);
    if(i2 == -1)
        return -1;
    str = ptr[i1].list;
    while(str != NULL){
        if(str->name == name2){
            count += 1;
            if(str == ptr[i1].list) {
                ptr[i1].list = list_delete_head(ptr[i1].list);
                break;
            }
            else {
                ptr[i1].list = list_delete_el(ptr[i1].list, str);
                break;
            }
        }else str = str->next;
    }
    str = ptr[i2].list;
    while(str != NULL){
        if(str->name == name1){
            count += 1;
            if(str == ptr[i2].list) {
                ptr[i2].list = list_delete_head(ptr[i2].list);
                break;
            }
            else {
                ptr[i2].list = list_delete_el(ptr[i2].list, str);
                break;
            }
        }else str = str->next;
    }
    if(count == 0)
        return -2;

    return 0;

}

int find_way(graph *gr,int name1,int name2,int size){

    int ind1,ind2;
    int *colour = (int*)calloc(size,sizeof(int));//-3 white;-2 grey;
    int *prev = (int*)calloc(size,sizeof(int));

    ind1 = searching(gr,name1,size);
    if(ind1 == -1)
        return -1;
    ind2 = searching(gr,name2,size);
    if(ind2 == -1)
        return -1;
    for(int i = 0;i < size;i++){
        colour[i] = -3;
        prev[i] = -1;
    }
    for(int i = 0;i<size;i++) {
        if(colour[i] == -3)
            DFS_1(gr, i, colour, prev, i);
    }
    if(colour[ind1] != colour[ind2])  {
        free(colour);
        free(prev);
        return -2;
    }

    free(colour);
    free(prev);

    return 0;
}

int DFS_1(graph *gr,int i,int *colour,int *prev,int color){
    colour[i] = -2;
    list *ptr;
    ptr = gr[i].list;
    while(ptr != NULL){
        if(colour[ptr->index] == -3){
            DFS_1(gr,ptr->index,colour,prev,color);
            prev[ptr->index] = ptr->name;
            ptr = ptr->next;
        }
        else ptr = ptr->next;
    }
    colour[i] = color;

    return 0;
}




int find_shortest_way(graph *gr,int name1,int name2,int size){ //Дейкстер

    int ind1 = searching(gr,name1,size);
    if(ind1 == -1)
        return -1;
    int ind2 = searching(gr,name2,size);
    if(ind2 == -1)
        return -1;

    float *d = (float*)calloc(size,sizeof(float));      //weight
    int *v = (int*)calloc(size,sizeof(int));            //метки
    int *prev = (int*)calloc(size,sizeof(int));         // родитель
    int k = size,index = 0;
    graph *ptr = gr;

    for(int i = 0; i < size; i++){
        d[i] = 100000;
        v[i] = -1;
        prev[i] = -1;
    }
    d[ind1] = 0;
    prev[ind1] = -1;
    while(k != 0){
        index = find_index(size,v,d);
        list *str = ptr[index].list;
        while(str != NULL){
            if(d[str->index] > d[index] + str->weight){
                d[str->index] = d[index] + str->weight;
                prev[str->index] = index;
            }
            str = str->next;
        }
        v[index] = 1;
        k -= 1;
    }
    if(d[ind2] == 100000)
        return -2;
    else{
        printf("Path found, shortest path weight = %f\n",d[ind2]);
    }
    free(prev);
    free(v);
    free(d);

    return 0;
}

int decomposition(graph *gr,int size){

    int *colour = (int*)calloc(size,sizeof(int));//0 white;-1 grey;1 black
    int *mas = (int*)calloc(size,sizeof(int));
    int *tim = (int*)calloc(size,sizeof(int));
    int *v = (int*)calloc(size,sizeof(int));

    int count = 0;

    for(int i = 0;i < size;i++){
        colour[i] = 0;
        mas[i] = -1;
        v[i] = -1;
        tim[i] = -1;
    }
    int time = 0;
    for(int i = 0;i<size;i++) {
        if(colour[i] == 0){
            DFS_2(gr, i, colour,&time,v);
            tim[count] = time;
            put_in_mas(mas,v,size);
            count += 1;
        }
    }

    printf("\nThe graph has %d connectivity components",count);
    output_interisting_graph(tim,size,count,mas);

    free(colour);
    free(tim);
    free(mas);
    free(v);

    return 0;

}

int DFS_2(graph *gr,int i,int *colour,int *time,int *v){

    colour[i] = -1;
    list *ptr;
    ptr = gr[i].list;
    while(ptr != NULL){
        if(colour[ptr->index] == 0){
            DFS_2(gr,ptr->index,colour,time,v);
            ptr = ptr->next;
        }
        else ptr = ptr->next;
    }
    colour[i] = 1;
    v[i] = gr[i].name;
    *time = *time + 1;

    return 0;
}

void put_in_mas(int *mas,int *v,int size){

    for(int i = 0;i < size;i++){
        if(v[i] != -1){
            for(int j = 0;j < size;j++){
                if(mas[j] == -1) {
                    mas[j] = v[i];
                    break;
                }
            }
        }
    }
    for(int k = 0;k < size;k++)
        v[k] = -1;

}

void output_interisting_graph(const int *tim,int size,int count,const int *mas){

    int k = 0;
    for(int i = 0;i < count;i++){
        printf("\n\nConnectivity component:  ");
        while(k != tim[i]-1){
            printf("%d--",mas[k]);
            k++;
        }
        printf("%d\n",mas[k]);
        k = tim[i];
    }
}

int random_graph(graph **gr,int num_size,int *size){
    if(num_size == 0)
        return -1;
    int i = 0;
    int name,name1,name2,c;
    float x,y;
    while(i < num_size){
        name = i + 1;
        x = rand()%100 + 1;
        y = rand() % 100 + 1;
        add_vertex(gr,name,x,y,size);
        i += 1;
    }
    if(num_size > 3){
        c = rand()%10;
        int k = c + num_size;
        while(k != 0){
            name1 = rand()%num_size + 1;
            name2 = rand()%num_size ;
            add_edge(gr,name1,name2,*size);
            k -= 1;
        }
    }
    else if(num_size == 1)
        return 0;

    else if(num_size == 2){
        c = rand() % 2;
        if(c != 0){
            add_edge(gr,1,2,*size);
        }
    }
    else if(num_size == 3){
        c = rand() % 3;
        while(c != 0){
            name1 = rand()%3 + 1;
            name2 = rand()%3 + 1;
            add_edge(gr,name1,name2,*size);
            c -= 1;
        }
    }

    return 0;
}



int find_index(int size,const int *v,const float *d){
    float min = 100000;
    int index;
    for(int i = 0; i < size; i++) {
        if (v[i] == -1 && min > d[i]) {
            min = d[i];
            index = i;
        }
    }
    return index;
}

int proverka(graph *gr,int i1,int name1){
    graph *ptr = gr;
    list *str;
    str = ptr[i1].list;
    while(str != NULL){
        if(str->name == name1)
            return -1;
        else str = str->next;
    }
    return 0;
}

list *create_list(int name,float weight){
    list *List = (list*)calloc(1,sizeof(list));
    List->name = name;
    List->weight = weight;
    List->next = NULL;
    return List;
}
list *add_to_list(int name,float weight,list *last){
    list *List = (list*)calloc(1,sizeof(list));
    List->name = name;
    List->weight = weight;
    List->next = last;
    return List;
}
list *list_delete_el(list *head,list *el){
    list * temp = head;
    while (temp->next != el){
        temp = temp->next;
    }
    temp->next = el->next;
    free(el);

    return head;
}
list *list_delete_head(list *head){
    list* temp = head->next;
    free(head);
    return temp;
}
int graphiz(graph *gr,int size){
    int count = 0;
    FILE *GR;
    char one[12] = {"Graph G {"};
    char two[2] = {"}"};
    GR =  fopen("C:\\Users\\79885\\CLionProjects\\Laba5\\graphiz.txt", "w");
    if(GR == NULL)
        return -1;

    fprintf(GR,"%s\n",one);

    for(int k = 0; k < size; k++){
        list *ptr = gr[k].list;
        fprintf(GR,"\n%d",gr[k].name);
        while(ptr != NULL){
            if(k > ptr->index) {
                if (count == 0) {
                    fprintf(GR, "--");
                    count += 1;
                }
                if (ptr->next == NULL)
                    fprintf(GR, "%d", ptr->name);
                else
                    fprintf(GR, "%d,", ptr->name);
            }
            ptr = ptr->next;
        }
        count = 0;
    }

    fprintf(GR,"\n%s",two);

    fclose(GR);
    return 0;
 }
