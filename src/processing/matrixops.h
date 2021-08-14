#ifndef MATRIXOPS_H_INCLUDED
#define MATRIXOPS_H_INCLUDED

#include <stdlib.h>

/* Calculate length of an array */
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(*array))

double *addVecScal(double vec[],
                   double scal,
                   int len);



double *multVecScal(double vec[],
                    double scal,
                    int len);

double *addVector(double vec1[],
                  double vec2[],
                  int len);


double *multVector(double vec1[],
                   double vec2[],
                   int len);

double dotProduct(double vec1[],
                  double vec2[],
                  int len);

double *crossProduct(double vec1[],
                     double vec2[]);

void matMul(size_t rM1,
            size_t cM1,
            size_t rM2,
            size_t cM2,
            double m1[rM1][cM1],
            double m2[rM2][cM2],
            double resMat[rM1][cM2]);


#endif // MATRIXOPS_H_INCLUDED
