#ifndef NN_H_
#define NN_H_

#include<stddef.h>
#include<stdio.h>

#ifndef NN_ASSERT 
#include<assert.h>
#define NN_ASSERT assert
#endif

#ifndef NN_MALLOC 
#include<stdlib.h>
#define NN_MALLOC malloc
#endif

#ifndef MatrixAt
#define MatrixAt(matrix,i, j) ((matrix).content[(i)+(j)])
#endif

typedef struct{
    size_t rows;
    size_t cols;
    float *content;
} Matrix;
// Note for struct definiiton: if there are mixed type: int, float, char, size_t,
// Write in order from biggest algnment size to smallest. Ex: float, int, chat. check with alignof() function.
Matrix allocateMatrix(size_t rows, size_t cols){
    // allocate the memory space 
    Matrix m;
    NN_ASSERT(rows>0 && cols>0);
    m.content = malloc(sizeof(float)* rows* cols);
    m.rows =rows;
    m.cols = cols;
    return m;
}

void deallocateMatrix(Matrix m){ 
    NN_ASSERT(m.content != NULL);
    free(m.content);
}

Matrix addMatrices(Matrix a, Matrix b){
    NN_ASSERT(a.rows == b.rows && a.cols == b.cols); 
    NN_ASSERT(a.content!=NULL && b.content!=NULL);
    Matrix c = allocateMatrix(a.rows, a.cols);
    size_t common_shape = a.cols;
    for(size_t i = 0; i< a.rows; ++i){
        for(size_t j = 0; j< a.cols;++j){
            MatrixAt(c,i*common_shape,j) = MatrixAt(a,i*common_shape,j)+ MatrixAt(b,i*common_shape,j); 
        }
    }
    return c;
}
void printMatrix(Matrix m){
    printf("Shape  of matrix is (%zu,%zu)\n", m.rows, m.cols);
    printf("------------------------------------------------\n");
    size_t index = 0;
    for(size_t i = 0; i< m.rows;++i){
        for(size_t j = 0; j< m.cols;++j){
            printf("%f ", MatrixAt(m, index,j));
        }
        printf("\n");
        index +=m.cols;
    }
    printf("------------------------------------------------\n");
}
void multiplyMatrices(Matrix a, Matrix b){
    NN_ASSERT(a.cols==b.rows);
    Matrix c = allocateMatrix(a.rows, b.cols);
    size_t index = 0;
    size_t common_shape = a.cols;
    for(size_t i = 0; i< a.rows;++i){
        float temp = 0.0;
        for(size_t j = 0; j< a.cols;++j){
            for(size_t k = 0; k< b.rows;++k){
                temp += MatrixAt(a,i*common_shape,k) * MatrixAt(b,j,k*common_shape); 
            }
            MatrixAt(c,index,j)= temp;
        }
    }
}
    
