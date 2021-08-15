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

#ifndef ROOTFINDING_H_INCLUDED
#define ROOTFINDING_H_INCLUDED

#include <math.h>

typedef struct RootData{

        double x;
        double iters;
        double err;

    } roots;

void newtonRhapsonMethod(double (*func)(double *),
                         double (*funcDer)(double *),
                         double dataFunc[],
                         double dataDer[],
                         double minErr,
                         int maxIters,
                         roots *RootData);

void halleyMethod(double (*func)(double *),
                     double (*funcDer)(double *),
                     double (*funcDer2)(double *),
                     double dataFunc[],
                     double dataDer[],
                     double dataDer2[],
                     double minErr,
                     int maxIters,
                     double HMresult[3]);

void fixedPointMethod(double (*func)(double *),
                      double dataFunc[],
                      double minErr,
                      int maxIters,
                      double FPresult[3]);

#endif // ROOTFINDING_H_INCLUDED
