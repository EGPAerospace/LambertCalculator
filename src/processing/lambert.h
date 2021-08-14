#ifndef LAMBERT_H_INCLUDED
#define LAMBERT_H_INCLUDED

#include <math.h>
#include "matrixops.h"
#include "arrayuts.h"
#include "unitconv.h"
#include "rootFinding.h"
#include "keplerian.h"

typedef struct LambertVel{

    double velDeparture[3];
    double velArrival[3];
    double deltaV;

} lamberts;


void universalLambert(double r0[3],
                      double r[3],
                      double deltaT,
                      int tm,
                      double mu,
                      lamberts *Lambert,
                      orbits **OrbLamb);

#endif // LAMBERT_H_INCLUDED
