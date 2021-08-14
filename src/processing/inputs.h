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
