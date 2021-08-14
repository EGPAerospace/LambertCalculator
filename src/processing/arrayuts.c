#include "arrayuts.h"

void pntToArr(double *pnt,
              double arr[],
              int len){

    register int i;

    for(i = 0; i < len; ++i){
        arr[i] = *(pnt + i);
    }

}

void getMatCol(size_t row,
               size_t col,
               double mat[row][col],
               int colNum,
               double arr[col]){

    register int i;

    for(i = 0; i < row; ++i){
        arr[i] = mat[i][colNum];
    }
}

void arrToMat(int len,
              double arr[len],
              size_t row,
              size_t col,
              double mat[row][col]){

    register int i, j;

    for(i = 0; i < row; ++i){
        for(j = 0; j < col; ++j){
            mat[i][j] = arr[col * i + j];
        }
    }
}

void arrCpy(int len,
            double orig[len],
            double cpy[len]){

    register int i;

    for(i = 0; i < len; ++i){
        cpy[i] = orig[i];
    }
}
