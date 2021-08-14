#include "lambert.h"


void universalLambert(double r0[3],
                      double r[3],
                      double deltaT,
                      int tm,
                      double mu,
                      lamberts *Lambert,
                      orbits **OrbLamb){

    roots NRresult;
    int turn, maxIters;
    double r0X, r0Y, r0Z, r0dist;
    double rX, rY, rZ, rdist;
    double *rcross, rcrossArr[3], deltaTheta, A;
    double zInit, zFinal, minErr, dataFunc[6], dataDer[4];
    double *stumpffPnt, stumpffArr[2], sz, cz, f, gDot, g;
    double yz, yzT1, yzT2, yzT3;
    double *v, *vT1, vT1Arr[3], *vT2, vT2Arr[3], *vT3, vT3Arr[3];
    double *v0, *v0T1, v0T1Arr[3], *v0T2, v0T2Arr[3];
    double v0Arr[3], vArr[3];


    /* Initial radius data */
    r0X = r0[0];
    r0Y = r0[1];
    r0Z = r0[2];
    r0dist = sqrt(dotProduct(r0, r0, 3));

    /* Final radius data */
    rX = r[0];
    rY = r[1];
    rZ = r[2];
    rdist = sqrt(dotProduct(r, r, 3));

    /* Set long way or short way trajectory*/
    rcross = crossProduct(r0, r);
    pntToArr(rcross, rcrossArr, 3);

    switch(tm){
        case (1):
            deltaTheta = acos(dotProduct(r0, r, 3) / (r0dist * rdist));
            if (rcrossArr[2] >= 0){
                turn = 1; /* Prograde trajectory */
            }
            else{
                turn = 0; /* Retrograde trajectory */
            }
            break;

        case (-1):
            deltaTheta = 2.0 * M_PI - acos(dotProduct(r0, r, 3) / (r0dist * rdist));
            if (rcrossArr[2] < 0){
                turn = 1; /* Prograde trajectory */
            }
            else{
                turn = 0; /* Retrograde trajectory */
            }
            break;

    }

    A = sin(deltaTheta) * sqrt((r0dist * rdist) / (1 - cos(deltaTheta)));


    /* Starting iteration phase */
    zInit = 35.0;
    minErr = 1E-10;
    maxIters = 10000;

    dataFunc[0] = zInit;
    dataFunc[1] = r0dist;
    dataFunc[2] = rdist;
    dataFunc[3] = A;
    dataFunc[4] = mu;
    dataFunc[5] = deltaT;

    dataDer[0] = zInit;
    dataDer[1] = r0dist;
    dataDer[2] = rdist;
    dataDer[3] = A;

    /* Newton-Raphson iterative method */
    newtonRhapsonMethod(functionFz,
                        functionDerFz,
                        dataFunc,
                        dataDer,
                        minErr,
                        maxIters,
                        &NRresult);

    zFinal = NRresult.x;

    /* Get Stumpff coefficients for final z value*/
    stumpffPnt = stumpff(zFinal);
    pntToArr(stumpffPnt, stumpffArr, 2);
    sz = stumpffArr[0];
    cz = stumpffArr[1];
    yz = functionYz(zFinal, r0dist, rdist, A, cz, sz);

    /* Calculate Lagrange functions */
    f = 1.0 - (yz / r0dist);
    gDot = 1.0 - (yz / rdist);
    g = A * sqrt(yz / mu);

    /* Calculate velocities */
    v0T1 = multVecScal(r0, -1.0 * f, 3);
    pntToArr(v0T1, v0T1Arr, 3);
    v0T2 = addVector(r, v0T1Arr, 3);
    pntToArr(v0T2, v0T2Arr, 3);
    v0 = multVecScal(v0T2Arr, 1.0 / g, 3);
    pntToArr(v0, v0Arr, 3);

    vT1 = multVecScal(r, gDot, 3);
    pntToArr(vT1, vT1Arr, 3);
    vT2 = multVecScal(r0, -1.0, 3);
    pntToArr(vT2, vT2Arr, 3);
    vT3 = addVector(vT1Arr, vT2Arr, 3);
    pntToArr(vT3, vT3Arr, 3);
    v = multVecScal(vT3Arr, 1.0 / g, 3);
    pntToArr(v, vArr, 3);

    arrCpy(3, v0Arr, Lambert->velDeparture);
    arrCpy(3, vArr, Lambert->velArrival);

    /* Accounting only arrival velocities for orbit determination*/
    orbitElements(r, vArr, *OrbLamb, mu);
}




