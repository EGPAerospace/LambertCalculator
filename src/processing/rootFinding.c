#include "rootFinding.h"

void newtonRhapsonMethod(double (*func)(double *),
                         double (*funcDer)(double *),
                         double dataFunc[],
                         double dataDer[],
                         double minErr,
                         int maxIters,
                         roots *RootData){

    double x, xOld;
    double err = 1.0;
    double iters = 0.0;
    double res;
    register int i;

    xOld = dataFunc[0];

    for (i = 0; i <= maxIters; ++i){

        if (err > minErr){
            x = xOld - ((*func)(dataFunc) / (*funcDer)(dataDer));
        } else {
            break;
        }

        err = fabs(x - xOld);
        xOld = x;
        dataFunc[0] = x;
        dataDer[0] = x;
        iters += 1.0;
    }

    RootData -> x = x;
    RootData -> iters = iters;
    RootData -> err = err;
}


void halleyMethod(double (*func)(double *),
                  double (*funcDer)(double *),
                  double (*funcDer2)(double *),
                  double dataFunc[],
                  double dataDer[],
                  double dataDer2[],
                  double minErr,
                  int maxIters,
                  double HMresult[3]){

    double x, xOld;
    double err = 1.0;
    double iters = 0.0;
    unsigned int i;

    xOld = dataFunc[0];

    for (i = 0; i <= maxIters; i++){
        if (err > minErr){
            x = xOld - ((2 * (*func)(dataFunc) * (*funcDer)(dataDer)) /
                        (2 * pow((*funcDer)(dataDer), 2) - (*func)(dataFunc)
                         * (*funcDer2)(dataDer2)));
        } else {
            break;
        }

        err = fabs(x - xOld);
        xOld = x;
        dataFunc[0] = x;
        dataDer[0] = x;
        dataDer2[0] = x;
        iters += 1.0;
    }

    HMresult[0] = x;
    HMresult[1] = iters;
    HMresult[2] = err;
}


void fixedPointMethod(double (*func)(double *),
                      double dataFunc[],
                      double minErr,
                      int maxIters,
                      double FPresult[3]){

    double x, xOld;
    double err = 1.0;
    double iters = 0.0;
    unsigned int i;

    for (i = 0; i <= maxIters; i++){
        if (err > minErr){
            x = (*func)(dataFunc);

        } else {
            break;
        }

        err = fabs(x - xOld);
        xOld = x;
        dataFunc[0] = x;
        iters += 1.0;
    }

    FPresult[0] = x;
    FPresult[1] = iters;
    FPresult[2] = err;
}
