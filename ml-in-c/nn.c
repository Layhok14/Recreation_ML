#include <math.h>
#include "nn.h"
#include <stdio.h>
#define ROWS 4
#define COLS 3

float rand_float(){
    return (float) rand()/ (float) RAND_MAX;
}
Matrix initailize_weight(Matrix m){
    for(size_t i = 0; i< m.rows;++i){
        for(size_t j=0; j< m.cols;++j){
            MatrixAt(m,i*m.cols,j) = rand_float();
        }
    }
    return m;
}


int main(){
    srand(67);
    Matrix m = allocateMatrix(ROWS, COLS); 
    m = initailize_weight(m);
    printf("%zu\n", _Alignof(Matrix));
    printMatrix(m);
    //free the memory
    deallocateMatrix(m.content);
    return 0; 
}

