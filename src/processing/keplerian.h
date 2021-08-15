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

#ifndef KEPLERIAN_H_INCLUDED
#define KEPLERIAN_H_INCLUDED

#include <math.h>
#include "ephem.h"
#include "rootFinding.h"
#include "matrixops.h"
#include "arrayuts.h"
#include "unitconv.h"

typedef struct OrbitData{

    double rPos[3];
    double vel[3];
    double a;
    double h;
    double inc;
    double omega;
    double ecc;
    double argPe;
    double trueAnom;

    } orbits;

double *stumpff(double z);


double functionYz(double z,
                  double r0dist,
                  double rdist,
                  double A,
                  double cz,
                  double sz);

double functionFz(double data[6]);


double functionDerFz(double data[4]);


double functionXi(double data[6]);


double functionXiDer(double data[6]);


double universalAnomaly(double r0,
                        double vr0,
                        double mu,
                        double aplpha,
                        double deltaTMax);


double angleQuadrantChange(double ang);


double eccentricAnomalyIsolated(double data[3]);


double eccentricAnomalyDerivative(double data[2]);


void orbitElements(double rArr[3],
                   double vArr[3],
                   orbits *Orbit,
                   double mu);


void perifToGeoMat(double inc,
                    double omega,
                    double argPe,
                    double qMat[3][3]);


void stateVecGeoFrame(double h,
                      double ecc,
                      double inc,
                      double omega,
                      double argPe,
                      double trueAnom,
                      double mu,
                      double rGeoArr[3],
                      double vGeoArr[3]);


void planetEphemerides(planets *Planet,
                       dates **Date,
                       orbits *Orbit,
                       double mu);


void orbitTrajectoryTime(double r0[3],
                         double v0[3],
                         double mu,
                         double deltaT,
                         double rArr[3]);


double deltaVCalc(double v1[3],
                  double v2[3]);



#endif // KEPLERIAN_H_INCLUDED
