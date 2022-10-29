#include <stdio.h>
#include <stdlib.h>

int min_heapify(int *S, int i, int n){
    int l,r,largest, q;
    l = 2*i + 1;
    r = 2*i + 2;
    if(l >= n)
        return 0;
    else if(r >= n){
            if(S[i] <= S[l])
                largest = i;
            else
                largest = l;
    }
    else {
        if (S[i] <= S[r] && S[i] <= S[l])
            largest = i;
        else if (S[r] < S[l])
            largest = r;
        else
            largest = l;
    }
    if(largest != i){
        q = S[i];
        S[i] = S[largest];
        S[largest] = q;
        min_heapify(S, largest,n);
    }
    return 0;
}

int increase_key(int *S, int i, int k, int n){
    int q;
    if(S[i] < k)
        return 1;
    S[i] = k;
    while(i>0 && S[(i-1)/2] > S[i]){
        q = S[i];
        S[i] = S[(i-1)/2];
        S[(i-1)/2] = q;
        i = (i-1)/2;
    }
    return 0;
}

int extract_min(int *S, int *n){
    int res;
    if(!S)
        return -1;
    res = S[0];
    S[0] = S[*n-1];
    S = (int *) realloc(S, (*n-1)*sizeof(int));
    *n = *n-1;
    min_heapify(S,0,*n);
    return res;
}

int main(){
    int *S, n,k;
    scanf("%d",&n);
    S = (int *) calloc(n, sizeof(int));
    for(int i=0; i<n; i++) {
        S[i] = n - i;
        printf("%d ", S[i]);
    }
    printf("\n");
    int i=n/2;
    while(i>=0){
        min_heapify(S,i,n);
        --i;
    }
    for(i=0; i<n; i++) {
        printf("%d ", S[i]);
    }
    increase_key(S,n/2, 0, n);
    printf("\n");
    for(i=0; i<n;printf("%d ", S[i]), i++);
    k = extract_min(S,&n);
    printf("\n%d\n", k);
    for(i=0; i<n;printf("%d ", S[i]), i++);
    free(S);
    return 0;
}