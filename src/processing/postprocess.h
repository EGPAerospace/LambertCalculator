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

#ifndef POSTPROCESS_H_INCLUDED
#define POSTPROCESS_H_INCLUDED

#include <stdio.h>
#include "inputs.h"
#include "ephem.h"
#include "keplerian.h"
#include "lambert.h"

void printInputData(FILE *ptrFileInput,
                    inputs *Input);


void printTransferDates(FILE *ptrFileTransfer,
                        dates *TransferDep,
                        dates *TransferArr,
                        inputs *Inputs);


void printPlanetsData(FILE *ptrFilePlanet,
                     dates *DatePlanetDep,
                     dates *DatePlanetArr,
                     orbits *OrbitPlanetDep,
                     orbits *OrbitPlanetArr);

void printCompleteLambertResults(FILE *ptrFileComplete,
                                 dates *Date1,
                                 dates *Date2,
                                 orbits *Orbit,
                                 lamberts *Lambert);

void printShortLambertResults(FILE *ptrFileShort,
                              double shortDepDate,
                              double shortArrDate,
                              lamberts *Lambert);

void printTrajectoryPoints(FILE *ptrFileTrajectory,
                           double rPos[3]);

#endif // POSTPROCESS_H_INCLUDED
