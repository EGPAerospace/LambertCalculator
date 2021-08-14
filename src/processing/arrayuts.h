#ifndef ARRAYUTS_H_INCLUDED
#define ARRAYUTS_H_INCLUDED

#include <stdlib.h>

void pntToArr(double *pnt,
              double arr[],
              int len);

void getMatCol(size_t row,
               size_t col,
               double mat[row][col],
               int colNum,
               double arr[col]);

void arrToMat(int len,
              double arr[len],
              size_t row,
              size_t col,
              double mat[row][col]);

void arrCpy(int len,
            double orig[len],
            double cpy[len]);

#endif // ARRAYUTS_H_INCLUDED
