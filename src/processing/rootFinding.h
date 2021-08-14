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
