#include <iostream>
#include "lab1.h"


namespace Lab1{

    using std::cin;
    using std::cout;
    using std::endl;

    Matrix *input(){

        const char *mes1 = "Please number of rows --> ";
        const char *mes2 = "Please number of lines -->";

        int height = get_size(mes1,1);
        int width = get_size(mes2,1);

        Matrix *matrix = nullptr;

        int *all = nullptr;

        try{
            all = new int[height*width];

        }
        catch (const std::bad_alloc &bd) {

            cout << bd.what() << endl;
            return nullptr;
        }

        cout << "Please, enter valume for matrix :" << endl;
        const char *mes3 = "";
        int amount = 0;
        for(int i = 0;i < height*width; i++){
            all[i] = get_size(mes3,0);
            if(all[i] != 0)
                amount ++;
        }
        matrix = memory(amount);
        matrix->height = height;
        matrix->width = width;
        matrix->amount = amount;

        int number = 0;
        for (int i = 0;i < height*width;i++){
            if(all[i] != 0){
                matrix->valume[number] = all[i];
                int j = i % width;
                int k = i / width;
                matrix->x[number] = j;
                matrix->y[number] = k;

                number++;

            }
        }
        delete [] all;

        return matrix;
    }

    void output(Matrix *mat){
        int count = 0;
        for(int i = 0; i < mat->width*mat->height; i++){
            if(mat->y[i] != mat->y[i-1])
                cout << endl;
            if(mat->x[count] + mat->y[count] * mat->width == i){
                cout << mat->valume[count] << " ";
                count ++;
            }else
                cout << "0" << " ";
        }
        cout << endl;

    }


    Matrix *memory(int amount){

        try{
            Matrix *matrix = new Matrix;
            matrix->valume = new int[amount];
            matrix->x = new int[amount];
            matrix->y = new int[amount];

            return matrix;
        }
        catch (const std::bad_alloc &x) {

            cout << x.what() << endl;

        }
    }

    int get_size(const char *say, int limit){
        int num;
        const char *mes1 = "";
        do {
            cout << mes1;
            cout << say;
            mes1 = "\nInvalid value!\n";
            if(getInt(num)<0){
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                num = -1;
            }
        }while(num < limit);

        return num;

    }

    void erase(Matrix *mat){
        delete [] mat->valume;
        delete [] mat->x;
        delete [] mat->y;
        delete mat;
    }

    Matrix *work_with_matrix(Matrix *mat){
        Matrix *new_mat = nullptr;
        int old_size = 0;
        int x = 0;
        int *one = nullptr;
        try{
            one = new int[mat->height];

        }
        catch (const std::bad_alloc &bd) {

            cout << bd.what() << endl;
            return nullptr;
        }


        for(int i = 0; i < mat->amount; i++){
            if(mat->y[i] != mat->y[i-1])
                x = 0;
            for(int j = i; j < mat->amount; j++){
                if(mat->y[i] != mat->y[j]) {
                    break;
                }
                if(mat->valume[i] == mat->valume[j]){
                    if(new_mat == nullptr)
                        new_mat = new Matrix;
                    new_mat->valume = realloc(new_mat->valume,mat->valume[j],old_size);
                    new_mat->x = realloc(new_mat->x,x,old_size);
                    new_mat->y = realloc(new_mat->y,mat->y[j],old_size);
                    if(one[i] < 0)
                        one[i] = 1;
                    else
                        one[i] = one[i] + 1;
                    x ++;
                }

            }
        }
        output_new(new_mat,one);

        return new_mat;
    }

    int *realloc(int *old, int new_number,int old_size){
        int *new_mas = nullptr;
        try{
            new_mas  = new int[old_size+1];

        }
        catch (std::bad_alloc &bd) {

            cout << bd.what() << endl;
            return nullptr;
        }

        for(int i = 0;i < old_size;i++){
            new_mas[i] = old[i];
        }
        new_mas[old_size] = new_number;
        return new_mas;
    }

    void output_new(Matrix *mat, int *how_it_input){

        int k = 0;
        for(int i = 0; i < mat->height; i++){
            for(int j = 0;j < how_it_input[i]; i++){
                cout << mat->valume[k] << " ";
                k++;
            }
            cout << endl;
        }

    }

}