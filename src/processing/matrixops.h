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

#ifndef MATRIXOPS_H_INCLUDED
#define MATRIXOPS_H_INCLUDED

#include <stdlib.h>

/* Calculate length of an array */
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(*array))

double *addVecScal(double vec[],
                   double scal,
                   int len);



double *multVecScal(double vec[],
                    double scal,
                    int len);

double *addVector(double vec1[],
                  double vec2[],
                  int len);


double *multVector(double vec1[],
                   double vec2[],
                   int len);

double dotProduct(double vec1[],
                  double vec2[],
                  int len);

double *crossProduct(double vec1[],
                     double vec2[]);

void matMul(size_t rM1,
            size_t cM1,
            size_t rM2,
            size_t cM2,
            double m1[rM1][cM1],
            double m2[rM2][cM2],
            double resMat[rM1][cM2]);


#endif // MATRIXOPS_H_INCLUDED
