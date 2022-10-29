#include <iostream>
#include "lab1.h"

using namespace Lab1;



int main() {

    std::cout << "Lab1" << std::endl;

    Matrix *mat = input();;
    Matrix *new_mat = nullptr;
    output(mat);
    new_mat = work_with_matrix(mat);
    erase(mat);
    erase(new_mat);


    return 0;
}
