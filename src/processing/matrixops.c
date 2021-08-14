#include "matrixops.h"

double *addVecScal(double vec[],
                   double scal,
                   int len){

    register int i;
    double add[len];
    double *resAdd;

    for (i = 0; i < len; i++){
        add[i] = scal + vec[i];
    }

    resAdd = &add;
    return resAdd;
}


double *multVecScal(double vec[],
                    double scal,
                    int len){

    register int i;
    double mult[len];
    double *resMult;

    for (i = 0; i < len; i++){
        mult[i] = (scal) * (vec[i]);
    }

    resMult = &mult;
    return resMult;
}


double *addVector(double vec1[],
                  double vec2[],
                  int len){

    register int i;
    double add[len];
    double *resAdd;

    for (i = 0; i < len; i++){
        add[i] = vec1[i] + vec2[i];
    }

    resAdd = &add;
    return resAdd;
}


double *multVector(double vec1[],
                   double vec2[],
                   int len){

    register int i;
    double mult[len];
    double *resMult;

    for (i = 0; i < len; i++){
        mult[i] = (vec1[i]) * (vec2[i]);
    }

    resMult = &mult;
    return resMult;
}


double dotProduct(double vec1[],
                  double vec2[],
                  int len){

    register int i;
    double prod, result;

    result = 0.0;

    for(i = 0; i < len; i++){
        prod = (vec1[i]) * (vec2[i]);
        result = result + prod;
    };

    return result;
}


double *crossProduct(double vec1[], double vec2[]){

    register int i;
    double vec10, vec11, vec12, vec20, vec21, vec22;
    double cross[3];
    double *crossRes;

    vec10 = vec1[0];
    vec11 = vec1[1];
    vec12 = vec1[2];

    vec20 = vec2[0];
    vec21 = vec2[1];
    vec22 = vec2[2];

    cross[0] = (vec11) * (vec22) - (vec12) * (vec21);
    cross[1] = (vec12) * (vec20) - (vec10) * (vec22);
    cross[2] = (vec10) * (vec21) - (vec11) * (vec20);

    crossRes = &cross;
    return crossRes;

}


void matMul(size_t rM1,
            size_t cM1,
            size_t rM2,
            size_t cM2,
            double m1[rM1][cM1],
            double m2[rM2][cM2],
            double resMat[rM1][cM2]){

    double sum;
    register int i, j, k;

    for(i = 0; i < rM1; i++){
        for (j = 0; j < cM2; j++){
            sum = 0.0;
            for(k = 0; k < rM2; k++){
                sum = sum + (m1[i][k]) * (m2[k][j]);
            }
            resMat[i][j] = sum;
        }
    }
}
