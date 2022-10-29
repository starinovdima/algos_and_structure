#include <stdio.h>
#include <stdlib.h>


int getInt(int* a)
{
    int n;
    do
    {
        n = scanf_s("%d", a);

        if (n == 0)
        {
            printf("Error, try again: ");
            scanf_s("%*c");
        }
    } while (n == 0);
    return n < 0 ? 0 : 1;
}

int getposint(int *a){

    int n = getInt(a);
    while (n > 0 && *a <= 0){
        printf("Enter natural int: ");
        n = getInt(a);
    }
    return 1;
}

void output(int *array, int num)
{
    for (int i = 0; i < num; i++)
        if (array[i] != 0)
            printf("%d ", array[i]);
        else
            printf("Null ");       //What i have to print when i get "0"
    printf("\n");
}

void delete(int *b)
{
    int  k = 0;

    while (*b != 0) {
        if ((*b % 10 != 0) && (*b % 10 != 1)) {
            k = k * 10 + *b % 10;
        }
        *b /= 10;

    }
    while (k != 0) {
        *b = *b * 10 + k % 10;
        k /= 10;
    }

}

int nu(int r)
{
    int count = 0;
    if (r == 0)
        return 0;
    while (r != 0)
    {
        count += 1;
        r /= 10;
    }
    return count;
}

int sort(int *numb, int size)
{

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = (size - 1); j > i; j--)
        {
            if (nu(numb[j - 1]) > nu(numb[j])) {

                int temp = numb[j - 1];
                numb[j - 1] = numb[j];
                numb[j] = temp;
            }
        }
    }
    return *numb;
}

void chistka(int *array, int num)
{
    int i;
    for (i = 0; i < num; i++)
        delete(&array[i]);
    sort(array,num);

}
int *input(int num)
{
    int i;
    int *array = (int*)malloc(num * sizeof(int));
    printf("Enter row of numbers:  ");
    for (i = 0; i < num; i++)
        getposint(&array[i]);
    return array;
}

int main()
{
    int num;
    printf("Enter the size:  ");

    getposint(&num);
    int *array = input(num);
    output(array, num);

    chistka(array,num);
    output(array,num);

    free(array);
    return 0;
}


