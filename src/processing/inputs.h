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

#ifndef INPUTS_H_INCLUDED
#define INPUTS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arrayuts.h"
#include "ephem.h"
#include "keplerian.h"


typedef struct inputData{

    char   planetDep[30];
    char   planetArr[30];
    double day;
    double month;
    double year;
    double hour;
    double minutes;
    double sec;
    double transferTmin;
    double transferTmax;
    double elapsedDep;
    double timeStep;
    int    problemType;

} inputs;


void getUserData(inputs *Input);

void getUserInputDataFile(inputs *Input,
                          FILE *ptrInputDataFile);

void getTransferDates (dates *TransferDep,
                       dates *TransferArr,
                       inputs *Input);


void getFileCompleteLambert(dates *TransferDep,
                            dates *TransferArr,
                            orbits *Orbit,
                            FILE *ptrDataFile);

void getFilePlanetData(dates *TransferDep,
                       dates *TransferArr,
                       orbits *OrbitPlanetDep,
                       orbits *OrbitPlanetArr,
                       FILE *ptrDataFile);



#endif // INPUTS_H_INCLUDED
