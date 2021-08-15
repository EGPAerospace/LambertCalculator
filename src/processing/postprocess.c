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

#include "postprocess.h"

void printInputData(FILE *ptrFileInput,
                    inputs *Input){

    fprintf(ptrFileInput, "%s \t"
                          "%s \t"
                          "%g \t"
                          "%g \t"
                          "%g \t"
                          "%g \t"
                          "%g \t"
                          "%g \t"
                          "%g \t"
                          "%g \t"
                          "%g \t"
                          "%g \t"
                          "%d \n",
            Input -> planetDep   , Input -> planetArr , Input -> day,
            Input -> month       , Input -> year      , Input -> hour,
            Input -> minutes     , Input -> sec       , Input -> transferTmin,
            Input -> transferTmax, Input -> elapsedDep, Input -> timeStep,
            Input -> problemType);
}


void printTransferDates(FILE *ptrFileTransfer,
                        dates *TransferDep,
                        dates *TransferArr,
                        inputs *Input){

    fprintf(ptrFileTransfer, "%s \t"
                             "%s \t"
                             "%g \t"
                             "%g \t"
                             "%g \t"
                             "%g \t"
                             "%g \t"
                             "%g \t"
                             "%d \n",
            Input -> planetDep, Input -> planetArr,
            TransferDep -> day, TransferDep -> month, TransferDep -> year,
            TransferArr -> day, TransferArr -> month, TransferArr -> year,
            Input -> problemType);

}


void printPlanetsData(FILE *ptrFilePlanet,
                     dates *DatePlanetDep,
                     dates *DatePlanetArr,
                     orbits *OrbitPlanetDep,
                     orbits *OrbitPlanetArr){

    fprintf(ptrFilePlanet, "%g \t"
                           "%g \t"
                           "%g \t"
                           "%g \t"
                           "%g \t"
                           "%g \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \t"
                           "%f \n",
            DatePlanetDep  -> day     , DatePlanetDep  -> month  , DatePlanetDep  -> year,
            DatePlanetArr  -> day     , DatePlanetArr  -> month  , DatePlanetArr  -> year,
            OrbitPlanetDep -> a       , OrbitPlanetDep -> h      , OrbitPlanetDep -> inc ,
            OrbitPlanetDep -> omega   , OrbitPlanetDep -> ecc    , OrbitPlanetDep -> argPe,
            OrbitPlanetDep -> trueAnom, OrbitPlanetDep -> rPos[0], OrbitPlanetDep -> rPos[1],
            OrbitPlanetDep -> rPos[2] , OrbitPlanetDep -> vel[0] , OrbitPlanetDep -> vel[1],
            OrbitPlanetDep -> vel[2],
            OrbitPlanetArr -> a       , OrbitPlanetArr -> h      , OrbitPlanetArr -> inc ,
            OrbitPlanetArr -> omega   , OrbitPlanetArr -> ecc    , OrbitPlanetArr -> argPe,
            OrbitPlanetArr -> trueAnom, OrbitPlanetArr -> rPos[0], OrbitPlanetArr -> rPos[1],
            OrbitPlanetArr -> rPos[2] , OrbitPlanetArr -> vel[0] , OrbitPlanetArr -> vel[1],
            OrbitPlanetArr -> vel[2]);
}


void printCompleteLambertResults(FILE *ptrFileComplete,
                                 dates *Date1,
                                 dates *Date2,
                                 orbits *Orbit,
                                 lamberts *Lambert){

    fprintf(ptrFileComplete, "%g \t"
                             "%g \t"
                             "%g \t"
                             "%g \t"
                             "%g \t"
                             "%g \t"
                             "%f \t"
                             "%f \t"
                             "%f \t"
                             "%f \t"
                             "%f \t"
                             "%f \t"
                             "%f \t"
                             "%f \t"
                             "%f \t"
                             "%f \t"
                             "%f \n",
            Date1 -> day     , Date1   -> month, Date1 -> year,
            Date2 -> day     , Date2   -> month, Date2 -> year,
            Orbit -> a       , Orbit   -> h    , Orbit -> inc,
            Orbit -> omega   , Orbit   -> ecc  , Orbit -> argPe,
            Orbit -> trueAnom, Lambert -> velDeparture[0],
            Lambert -> velDeparture[1], Lambert -> velDeparture[2],
            Lambert -> deltaV);

}

void printShortLambertResults(FILE *ptrFileShort,
                              double shortDepDate,
                              double shortArrDate,
                              lamberts *Lambert){

    fprintf(ptrFileShort, "%.0f \t"
                          "%.0f \t"
                          "%f \n",
            shortDepDate, shortArrDate, Lambert -> deltaV);


}

void printTrajectoryPoints(FILE *ptrFileTrajectory,
                           double rPos[3]){

    fprintf(ptrFileTrajectory, "%f \t"
                               "%f \t"
                               "%f \n",
                        rPos[0], rPos[1], rPos[2]);
}
