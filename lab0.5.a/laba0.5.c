#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


char *get_str(int *n) {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
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
            if (res == NULL)
            {
                printf("not enough memory (realloc returned NULL)\n");
                free(res);
            }
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = (char *)calloc(1, sizeof(char));
        if (res == NULL)
        {
            printf("not enough memory (realloc returned NULL)\n");
            free(res);
        }
    }

    return res;
}

void remove_double_space(char* str){
    int x = 0;
    for(int i = 0; str[i]; ++i){
        // isspace is working for all white space chars
        //  ' ' - space, '\t' -  hor tab, '\n' - newline, '\v' - vert tab
        //  '\f' - form feed, '\r' - carraige return
        //clearing double space and double tabs

        if (str[i] == '\t')
            str[i] = ' ';

        if (!isspace(str[i]) || (i >= 0 && !isspace(str[i+1]))){
            x++;
            str[x] = str[i];
        }
    }
    str[x] = '\0';
}


void remove_leading_space(char* str){
    char punctuations[] = ",;.!?";
    int x = 0;
    for(int i = 0; str[i]; ++i){
        if(!isspace(str[i]) ||  strchr(punctuations, str[i+1]) == NULL) {
            str[x++] = str[i];
        }
    }
    str[x] = '\0';
}


void output(char *str)
{
    printf("\nRedacted string is:\n");

    for (int i = 0; str[i]; ++i){
        printf("%c",str[i]);
        if (str[i] == ',' || str[i] == ':' || str[i] == ';')
            printf(" ");
        if ((str[i] == '.' || str[i] == '?' || str[i] == '!')  && str[i + 1] != NULL )
            printf("\n");
    }

}

int main()
{
    char *str = NULL;
    int n;
    do {
        printf("\nType your string:\n");
        str = get_str(&n);
        remove_double_space(str);
        remove_leading_space(str);
        output(str);
        free(str);
    }while (n != EOF);

    return 0;
}
