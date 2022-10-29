#ifndef LABA1_LAB1_H
#define LABA1_LAB1_H

namespace Lab1{

    struct Matrix{

        int height;
        int width;
        int amount;

        int *valume;
        int *x;
        int *y;
    };


    template <typename X>

    int getInt(X &num){
        std::cin >> num;
        if(!std::cin.good())
            return -1;
        return 1;
    }


    Matrix *input();
    void output(Matrix *mat);
    void erase(Matrix *mat);
    Matrix *work_with_matrix(Matrix *mat);
    int get_size(const char *say,int limit);
    int *input_all_elements();
    Matrix *memory(int amount);
    int *realloc(int *old, int new_number,int old_size);
    void output_new(Matrix *mat, int *how_it_input);
}

#endif //LABA1_LAB1_H
