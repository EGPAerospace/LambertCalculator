/*

The MIT License (MIT)

Copyright (c) 2021 EGPAerospace

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

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
