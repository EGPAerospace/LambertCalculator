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
