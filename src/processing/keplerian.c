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

#include "keplerian.h"

double *stumpff(double z){

    double stumpffPar[2];
    double sz, cz;
    double *res;

    if (z > 0.0){
        sz = (sqrt(z) - sin(sqrt(z))) / pow(sqrt(z), 3);
        cz = (1.0 - cos(sqrt(z))) / z;
    }

    else if (z < 0.0){
        sz = (sinh(sqrt(-1.0*z)) - sqrt(-z)) / pow(sqrt(-1.0*z), 3);
        cz = (cosh(sqrt(-1.0*z)) - 1.0) / (-1.0*z);
    }

    else{
        sz = 1.0 / 6.0;
        cz = 0.5;
    }

    stumpffPar[0] = sz;
    stumpffPar[1] = cz;
    res = &stumpffPar;
    return res;


}


double functionYz(double z,
                  double r0dist,
                  double rdist,
                  double A,
                  double cz,
                  double sz){

    double yz, yzT1, yzT2, yzT3;

    yzT1 = r0dist + rdist;
    yzT2 = A * ((z * sz) - 1.0);
    yzT3 = sqrt(cz);
    yz = yzT1 + (yzT2 / yzT3);

    return yz;
}


double functionFz(double data[6]){

    double z, r0dist, rdist, A, mu, deltaT;
    double yz, yzT1, yzT2, yzT3;
    double *stumpffPnt, stumpffArr[2], cz, sz;
    double fz, fzT1, fzT2, fzT3;

    z      = data[0];
    r0dist = data[1];
    rdist  = data[2];
    A      = data[3];
    mu     = data[4];
    deltaT = data[5];

    stumpffPnt = stumpff(z);
    pntToArr(stumpffPnt, stumpffArr, 2);
    sz = stumpffArr[0];
    cz = stumpffArr[1];

    yz = functionYz(z, r0dist, rdist, A, cz, sz);


    fzT1 = pow((yz / cz), 1.5) * sz;
    fzT2 = A * sqrt(yz);
    fzT3 = sqrt(mu) * deltaT;
    fz = fzT1 + fzT2 - fzT3;

    return fz;
}


double functionDerFz(double data[4]){

    double z, r0dist, rdist, A;
    double yz, yzT1, yzT2, yzT3;
    double *stumpffPnt, stumpffArr[2], cz, sz;
    double fzDer, fzDerT1, fzDerT2, fzDerT3;
    double fzDerT4, fzDerT5, fzDerT6, fzDerT7;

    z      = data[0];
    r0dist = data[1];
    rdist  = data[2];
    A      = data[3];

    if (z != 0.0){

        stumpffPnt = stumpff(z);
        pntToArr(stumpffPnt, stumpffArr, 2);
        sz = stumpffArr[0];
        cz = stumpffArr[1];
        yz = functionYz(z, r0dist, rdist, A, cz, sz);

        fzDerT1 = pow((yz / cz), 1.5);
        fzDerT2 = 1.0 / (2.0 * z);
        fzDerT3 = cz - (1.5 * (sz / cz));
        fzDerT4 = (3.0 / 4.0) * (pow(sz, 2) / cz);
        fzDerT5 = A / 8.0;
        fzDerT6 = 3.0 * (sz / cz) * sqrt(yz);
        fzDerT7 = A * sqrt(cz / yz);
        fzDer = fzDerT1 * (fzDerT2 * fzDerT3 + fzDerT4) + fzDerT5 * (fzDerT6 + fzDerT7);
    }

    else{

        stumpffPnt = stumpff(z);
        pntToArr(stumpffPnt, stumpffArr, 2);
        sz = stumpffArr[0];
        cz = stumpffArr[1];
        yz = functionYz(z, r0dist, rdist, A, cz, sz);

        fzDerT1 = (sqrt(2.0) / 40.0) * pow(yz, 1.5);
        fzDerT2 = A / 8.0;
        fzDerT3 = sqrt(yz);
        fzDerT4 = A * sqrt(1.0 / (2.0 * yz));
        fzDer = fzDerT1 + fzDerT2 * (fzDerT3 + fzDerT4);
    }

    return fzDer;
}


double functionXi(double data[6]){

    double xi, r0, vr0, mu, alpha, deltaT;
    double *stumpffPnt, stumpffArr[2], z, cz, sz;
    double fXiT1, fXiT2, fXiT3, fXiT4, fXi;

    xi = data[0];
    r0 = data[1];
    vr0 = data[2];
    mu = data[3];
    alpha = data[4];
    deltaT = data[5];

    z = alpha * pow(xi, 2);
    stumpffPnt = stumpff(z);
    pntToArr(stumpffPnt, stumpffArr, 2);
    sz = stumpffArr[0];
    cz = stumpffArr[1];

    fXiT1 = ((r0 * vr0) / sqrt(mu)) * pow(xi, 2) * cz;
    fXiT2 = (1.0 - alpha * r0) * pow(xi, 3) * sz;
    fXiT3 = r0 * xi;
    fXiT4 = sqrt(mu) * deltaT;
    fXi = fXiT1 + fXiT2 + fXiT3 - fXiT4;

    return fXi;
}


double functionXiDer(double data[6]){

    double xi, r0, vr0, mu, alpha, deltaT;
    double *stumpffPnt, stumpffArr[2], z, cz, sz;
    double fXiDerT1, fXiDerT2, fXiDerT3, fXiDer;

    xi = data[0];
    r0 = data[1];
    vr0 = data[2];
    mu = data[3];
    alpha = data[4];
    deltaT = data[5];

    z = alpha * pow(xi, 2);
    stumpffPnt = stumpff(z);
    pntToArr(stumpffPnt, stumpffArr, 2);
    sz = stumpffArr[0];
    cz = stumpffArr[1];

    fXiDerT1 = ((r0 * vr0) / sqrt(mu));
    fXiDerT2 = xi * (1.0 - alpha * pow(xi, 2) * sz);
    fXiDerT3 = (1.0 - alpha * r0) * pow(xi, 2) * cz + r0;
    fXiDer = fXiDerT1 * fXiDerT2 + fXiDerT3;

    return fXiDer;
}


double universalAnomaly(double r0,
                        double vr0,
                        double mu,
                        double alpha,
                        double deltaT){

    double xi0, dataFuncXi[6], dataFuncDerXi[6];
    double minError, xiFinal;
    double maxIters;
    roots NRData;

    xi0 = sqrt(mu) * fabs(alpha) * deltaT;

    dataFuncXi[0] = xi0;
    dataFuncXi[1] = r0;
    dataFuncXi[2] = vr0;
    dataFuncXi[3] = mu;
    dataFuncXi[4] = alpha;
    dataFuncXi[5] = deltaT;

    arrCpy(6, dataFuncXi, dataFuncDerXi);

    minError = 1E-8;
    maxIters = 1000.0;

    newtonRhapsonMethod(functionXi,
                        functionXiDer,
                        dataFuncXi,
                        dataFuncDerXi,
                        minError,
                        maxIters,
                        &NRData);

    xiFinal = NRData.x;

    return xiFinal;
}


double angleQuadrantChange(double ang){

    double angNew;

    if (ang > 2.0 * M_PI){
        angNew = remainder(ang, 2.0 * M_PI);
    }

    else if (ang < 0.0){
        angNew = 2.0 * M_PI + ang;
    }

    else{
        angNew = ang;
    }

    return angNew;
}


double eccentricAnomalyIsolated(double data[3]){

    double f, M, E, e;

    E = data[0];
    M = data[1];
    e = data[2];
    f = E - e * sin(E) - M;

    return f;
}


double eccentricAnomalyDerivative(double data[2]){

    double f, E, e;

    E = data[0];
    e = data[1];
    f = 1.0 - e * cos(E);

    return f;
}


void orbitElements(double rArr[3],
                   double vArr[3],
                   orbits *Orbit,
                   double mu){

    double r, v, vr;
    double *h, hArr[3], hMag;
    double inc;
    double *n, nArr[3], nMag;
    double kAxis[3] = {0.0, 0.0, 1.0};
    double omega;
    double scal1, scal2;
    double *ecc, eccArr[3], eccMag;
    double eccT1, *eccT2, eccT2Arr[3], *eccT3, eccT3Arr[3], *eccT4, eccT4Arr[3];
    double argPe;
    double trueAnom;
    double rPeri, rApo, a;

    /* Distance, speed, radial velocity */
    r = sqrt(dotProduct(rArr, rArr, 3));
    v = sqrt(dotProduct(vArr, vArr, 3));
    vr = dotProduct(rArr, vArr, 3) / r;

    /* Angular momentum calculations */
    h = crossProduct(rArr, vArr);
    pntToArr(h, hArr, 3);
    hMag = sqrt(dotProduct(hArr, hArr, 3));

    /* Orbit inclination */
    inc = acos(hArr[2] / hMag);

    /* Node line calculation */
    n = crossProduct(kAxis, hArr);
    pntToArr(n, nArr, 3);
    nMag = sqrt(dotProduct(nArr, nArr, 3));

    /* Right Ascension of Ascending Node */
    if (nArr[1] >= 0.0){
        omega = acos(nArr[0] / nMag);
    }
    else{
        omega = 2.0 * M_PI - acos(nArr[0] / nMag);
    }

    /* Eccentricity vector */
    eccT1 = 1.0 / mu;
    scal1 = (pow(v, 2) - mu / r);
    eccT2 = multVecScal(rArr, scal1, 3);
    pntToArr(eccT2, eccT2Arr, 3);

    scal2 = -1.0 * (r * vr);
    eccT3 = multVecScal(vArr, scal2, 3);
    pntToArr(eccT3, eccT3Arr, 3);

    eccT4 = addVector(eccT2Arr, eccT3Arr, 3);
    pntToArr(eccT4, eccT4Arr, 3);

    ecc = multVecScal(eccT4Arr, eccT1, 3);
    pntToArr(ecc, eccArr, 3);

    eccMag = sqrt(dotProduct(eccArr, eccArr, 3));

    /* Argument of perigee */
    if (eccArr[2] >= 0.0){
        argPe = acos(dotProduct(nArr, eccArr, 3) / (nMag * eccMag));
    }
    else{
        argPe = 2.0 * M_PI - acos(dotProduct(nArr, eccArr, 3) / (nMag * eccMag));
    }

    /* True Anomaly */
    if (vr >= 0.0){
        trueAnom = acos(dotProduct(eccArr, rArr, 3) / (eccMag * r));
    }
    else{
        trueAnom = 2.0 * M_PI - acos(dotProduct(eccArr, rArr, 3) / (eccMag * r));
    }

    /* Semi-major axis */
    rPeri = (pow(hMag, 2) / mu) * (1.0 / (1 + eccMag * cos(0.0)));
    rApo  = (pow(hMag, 2) / mu) * (1.0 / (1 + eccMag * cos(M_PI)));
    a = 0.5 * (rPeri + rApo);

    /* Store orbit elements in array */
    arrCpy(3, rArr, Orbit -> rPos);
    arrCpy(3, vArr, Orbit -> vel);
    Orbit -> a = a;
    Orbit -> h = hMag;
    Orbit -> inc = inc;
    Orbit -> omega = omega;
    Orbit -> ecc = eccMag;
    Orbit -> argPe = argPe;
    Orbit -> trueAnom = trueAnom;

}


void perifToGeoMat(double inc,
                    double omega,
                    double argPe,
                    double qMat[3][3]){

    double co, so, ci, si, cw, sw;

    co = cos(omega);
    so = sin(omega);
    ci = cos(inc);
    si = sin(inc);
    cw = cos(argPe);
    sw = sin(argPe);

    qMat[0][0] = (co * cw) - (so * sw * ci);
    qMat[0][1] = -(co * sw) - (so * ci * cw);
    qMat[0][2] = so * si;

    qMat[1][0] = (so * cw) + (co * ci * sw);
    qMat[1][1] = -(so * sw) + (co * ci * cw);
    qMat[1][2] = -(co * si);

    qMat[2][0] = si * sw;
    qMat[2][1] = si * cw;
    qMat[2][2] = ci;
}


void stateVecGeoFrame(double h,
                      double ecc,
                      double inc,
                      double omega,
                      double argPe,
                      double trueAnom,
                      double mu,
                      double rGeoArr[3],
                      double vGeoArr[3]){

    double *rPerif, rPerifArr[3], rPerifT1, rPerifMat[3][1];
    double rPerifT2[3];
    double *vPerif, vPerifArr[3], vPerifT1, vPerifMat[3][1];
    double vPerifT2[3];
    double qMat[3][3];
    double rGeoMat[3][1], vGeoMat[3][1];

    rPerifT2[0] = cos(trueAnom);
    rPerifT2[1] = sin(trueAnom);
    rPerifT2[2] = 0.0;

    vPerifT2[0] = -1.0 * sin(trueAnom);
    vPerifT2[1] = ecc + cos(trueAnom);
    vPerifT2[2] = 0.0;

    /* Position vector in perifocal coordinates*/
    rPerifT1 = (pow(h, 2) / mu) * (1.0 / (1.0 + ecc * cos(trueAnom)));
    rPerif = multVecScal(rPerifT2, rPerifT1, 3);
    pntToArr(rPerif, rPerifArr, 3);
    arrToMat(3, rPerifArr, 3, 1, rPerifMat);

    /* Velocity vector in perifocal coordinates*/
    vPerifT1 = mu / h;
    vPerif = multVecScal(vPerifT2, vPerifT1, 3);
    pntToArr(vPerif, vPerifArr, 3);
    arrToMat(3, vPerifArr, 3, 1, vPerifMat);

    /* Perifocal to geocentric rotation matrix */
    perifToGeoMat(inc, omega, argPe, qMat);

    /* Position vector in geocentric coordinates*/
    matMul(3, 3, 3, 1, qMat, rPerifMat, rGeoMat);
    getMatCol(3, 1, rGeoMat, 0, rGeoArr);

    /* Position vector in geocentric coordinates*/
    matMul(3, 3, 3, 1, qMat, vPerifMat, vGeoMat);
    getMatCol(3, 1, vGeoMat, 0, vGeoArr);
}


void planetEphemerides(planets *Planet,
                       dates **Date,
                       orbits *Orbit,
                       double mu){

    roots NRresult;
    double a, aD, ec, ecD, in, inD, om, omD, aP, aPD, mL, mLD;
    double jD, t0;
    double aJD, ecJD, inJD, omJD, aPJD, mLJD;
    double h, argPe, M;
    double minError, maxIters, dataFuncNR[3], dataDerNR[2];
    double E, trueAnom, trueAnomT1, trueAnomT2;
    double posArr[3], velArr[3];

    /* Short name variable assignment */
    a   = AUToMeters(Planet -> a);
    aD  = AUToMeters(Planet -> aDot);
    ec  = Planet -> ecc;
    ecD = Planet -> eccDot;
    in  = degToRad(Planet -> inc);
    inD = degToRad(Planet -> incDot);
    om  = degToRad(Planet -> omega);
    omD = degToRad(Planet -> omegaDot);
    aP  = degToRad(Planet -> argPe);
    aPD = degToRad(Planet -> argPeDot);
    mL  = degToRad(Planet -> mLong);
    mLD = degToRad(Planet -> mLongDot);

    /* Julian date */
    jD = julianDate(*Date);

    /* Number of Julian centuries */
    t0 = (jD - 2451545.0) / 36525.0;

    /* Orbital elements for Julian Date */
    aJD  = a + aD * t0;
    ecJD = ec + ecD * t0;
    inJD = in + inD * t0;
    omJD = om + omD * t0;
    aPJD = aP + aPD * t0;
    mLJD = mL + mLD * t0;

    inJD = fabs(inJD);
    omJD = angleQuadrantChange(omJD);
    aPJD = angleQuadrantChange(aPJD);
    mLJD = angleQuadrantChange(mLJD);

    h = sqrt(mu * aJD * (1.0 - pow(ecJD, 2)));
    argPe = aPJD - omJD;
    M = mLJD - aPJD;

    argPe = angleQuadrantChange(argPe);
    M = angleQuadrantChange(M);

    /* Calculating eccentric anomaly E */
    minError = 1E-6;
    maxIters = 1000.0;
    dataFuncNR[0] = M_PI; /* Eccentric anomaly initial guess */
    dataFuncNR[1] = M;
    dataFuncNR[2] = ecJD;
    dataDerNR[0]  = M_PI; /* Eccentric anomaly initial guess */
    dataDerNR[1]  = ecJD;
    newtonRhapsonMethod(eccentricAnomalyIsolated,
                        eccentricAnomalyDerivative,
                        dataFuncNR,
                        dataDerNR,
                        minError,
                        maxIters,
                        &NRresult);

    E = NRresult.x;
    E = angleQuadrantChange(E);

    trueAnomT1 = sqrt((1.0 + ecJD) / (1.0 - ecJD));
    trueAnomT2 = tan(E / 2.0);
    trueAnom = 2.0 * atan(trueAnomT2 * trueAnomT1);
    trueAnom = angleQuadrantChange(trueAnom);

    /* Calculating position and velocity vector */
    stateVecGeoFrame(h, ecJD, inJD, omJD, argPe, trueAnom, mu, posArr, velArr);

    /* Store data into Orbit struct*/
    arrCpy(3, posArr, Orbit -> rPos);
    arrCpy(3, velArr, Orbit -> vel);
    Orbit -> a = aJD;
    Orbit -> h = h;
    Orbit -> inc = inJD;
    Orbit -> omega = omJD;
    Orbit -> ecc = ecJD;
    Orbit -> argPe = argPe;
    Orbit -> trueAnom = trueAnom;

}


void orbitTrajectoryTime(double r0[3],
                         double v0[3],
                         double mu,
                         double deltaT,
                         double rArr[3]){

    double r0Mag, v0Mag;
    double vr0, alpha;
    double xi;
    double *stumpffPnt, stumpffArr[2], z, cz, sz;
    double f, g, fDot, gDot;
    double *rT1Pnt, rT1Arr[3], *rT2Pnt, rT2Arr[3], *rPnt;
    double *vT1Pnt, vT1Arr[3], *vT2Pnt, vT2Arr[3], *vPnt, vArr[3];

    r0Mag = sqrt(dotProduct(r0, r0, 3));
    v0Mag = sqrt(dotProduct(v0, v0, 3));
    vr0 = dotProduct(r0, v0, 3) / r0Mag;
    alpha = (2.0 / r0Mag) - (pow(v0Mag, 2) / mu);

    xi = universalAnomaly(r0Mag, vr0, mu, alpha, deltaT);

    z = alpha * pow(xi, 2);
    stumpffPnt = stumpff(z);
    pntToArr(stumpffPnt, stumpffArr, 2);
    sz = stumpffArr[0];
    cz = stumpffArr[1];

    f = 1.0 - (pow(xi, 2) / r0Mag) * cz;
    g = deltaT - (1.0 / sqrt(mu)) * pow(xi, 3) * sz;


    rT1Pnt = multVecScal(r0, f, 3);
    pntToArr(rT1Pnt, rT1Arr, 3);
    rT2Pnt = multVecScal(v0, g, 3);
    pntToArr(rT2Pnt, rT2Arr, 3);
    rPnt = addVector(rT1Arr, rT2Arr, 3);
    pntToArr(rPnt, rArr, 3);

}


double deltaVCalc(double v1[3],
                  double v2[3]){

    double *v2NegPtr, v2NegArr[3];
    double *vInfPtr, vInfArr[3];
    double vInfMod;

    v2NegPtr = multVecScal(v2, -1.0, 3);
    pntToArr(v2NegPtr, v2NegArr, 3);

    vInfPtr = addVector(v1, v2NegArr, 3);
    pntToArr(vInfPtr, vInfArr, 3);

    vInfMod = sqrt(dotProduct(vInfArr, vInfArr, 3));

    return vInfMod;
}
