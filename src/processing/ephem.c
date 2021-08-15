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

#include "ephem.h"

const double mercuryEphem[12] = {0.38709927  ,  0.00000037, \
                                 0.20563593  ,  0.00001906, \
                                 7.00497902  , -0.00594749, \
                                 48.33076593 , -0.12534081, \
                                 77.45779628 ,  0.16047689, \
                                 252.2503235 ,  149472.67411175};

const double venusEphem[12] = {0.72333566  ,  0.00000390, \
                               0.00677672  , -0.00004107, \
                               3.39467605  , -0.00078890, \
                               76.67984255 , -0.27769418, \
                               131.60246718,  0.00268329, \
                               181.97909950,  58517.81538729};

const double earthEphem[12] = {1.00000261  ,  0.00000562, \
                               0.01671123  , -0.00004392, \
                              -0.00001531  , -0.01294668, \
                               0.0         ,  0.0       , \
                               102.93768193,  0.32327364, \
                               100.46457166,  35999.37244981};

const double marsEphem[12] = {1.5237104  ,  0.0001847, \
                              0.09339410 ,  0.00007882, \
                              1.84969142 , -0.00813131, \
                              49.55953891, -0.29257343, \
                              23.94362959,  0.44441088, \
                             -4.55343205 ,  19140.30268499};

const double jupiterEphem[12] = {5.20288700  , -0.00011607, \
                                 0.04838624  ,  0.00013253, \
                                 1.30439695  , -0.00183714, \
                                 100.47390909,  0.20469106, \
                                 14.72847983 ,  0.21252668, \
                                 34.39644501 ,  3034.74612775};

const double saturnEphem[12] =  {9.53667594  , -0.00125060, \
                                 0.05386179  , -0.00050991, \
                                 2.48599187  ,  0.00193609, \
                                 113.66242448, -0.28867794, \
                                 92.59887831 , -0.41897216, \
                                 49.95424423 ,  1222.49362201};

const double uranusEphem[12] =  {19.18916464 , -0.00196176, \
                                 0.04725744  , -0.00004397, \
                                 0.77263783  , -0.00242939, \
                                 74.01692503 ,  0.04240589, \
                                 170.95427630,  0.40805281, \
                                 313.23810451,  428.48202785};

const double neptuneEphem[12] = {30.06992276 ,  0.00026291, \
                                 0.00859048  ,  0.00005105, \
                                 1.77004347  ,  0.00035372, \
                                 131.78422574, -0.00508664, \
                                 44.96476227 , -0.32241464, \
                                -55.12002969 ,  218.45945325};

const double plutoEphem[12]   = {39.48211675 , -0.00031596, \
                                 0.24882730  ,  0.00005170, \
                                 17.14001206 ,  0.00004818, \
                                 110.30393684, -0.01183482, \
                                 224.06891629, -0.04062942, \
                                 238.92903833,  145.20780515};

void problemTypeSet(int problemType,
                    planets *Planet){

    switch(problemType){

        case 1:
            /* Do nothing */
            break;

        case 2:
            /* Remove inclination */
            Planet -> inc = 0.0;
            Planet -> incDot = 0.0;
            break;

        case 3:
            /* Remove inclination and eccentricity */
            Planet -> inc = 0.0;
            Planet -> incDot = 0.0;
            Planet -> ecc = 0.0;
            Planet -> eccDot = 0.0;
            break;
    }
}


double julianDate(dates *Date){

    double dd, mm, yy, hr, min, sec;
    double j0, j0T1, j0T2, j0T3, j0T4;
    double jD, uT;

    dd  = Date -> day;
    mm  = Date -> month;
    yy  = Date -> year;
    hr  = Date -> hour;
    min = Date -> minutes;
    sec = Date -> sec;

    j0T1 = 367.0 * yy;
    j0T2 = floor((7.0 * (yy + floor((mm + 9.0) / 12.0))) / 4.0);
    j0T3 = floor((275.0 * mm) / 9.0);
    j0T4 = dd + 1721013.5;
    j0 = j0T1 - j0T2 + j0T3 + j0T4;

    uT = hr + (min / 60.0) + (sec / 3600.0);
    jD = j0 + (uT / 24.0);

    return jD;
}

void getPlanetData(char namePlanet[30],
                   planets *Planet){

    double planetDataArr[12];
    double a, aDot;
    double ecc, eccDot;
    double inc, incDot;
    double omega, omegaDot;
    double argPe, argPeDot;
    double mLong, mLongDot;

    if (strcmp(namePlanet, "Mercury") == 0){
        arrCpy(12, mercuryEphem, planetDataArr);
    }
    else if (strcmp(namePlanet, "Venus") == 0){
        arrCpy(12, venusEphem, planetDataArr);
    }
    else if (strcmp(namePlanet, "Earth") == 0) {
        arrCpy(12, earthEphem, planetDataArr);
    }
    else if (strcmp(namePlanet, "Mars") == 0){
        arrCpy(12, marsEphem, planetDataArr);
    }
    else if (strcmp(namePlanet, "Jupiter") == 0){
        arrCpy(12, jupiterEphem, planetDataArr);
    }
    else if (strcmp(namePlanet, "Saturn") == 0){
        arrCpy(12, saturnEphem, planetDataArr);
    }
    else if (strcmp(namePlanet, "Uranus") == 0){
        arrCpy(12, saturnEphem, planetDataArr);
    }
    else if (strcmp(namePlanet, "Neptune") == 0){
        arrCpy(12, saturnEphem, planetDataArr);
    }
    else if (strcmp(namePlanet, "Pluto") == 0){
        arrCpy(12, saturnEphem, planetDataArr);
    }
    else{

    }


    Planet -> a        = planetDataArr[0];
    Planet -> aDot     = planetDataArr[1];
    Planet -> ecc      = planetDataArr[2];
    Planet -> eccDot   = planetDataArr[3];
    Planet -> inc      = planetDataArr[4];
    Planet -> incDot   = planetDataArr[5];
    Planet -> omega    = planetDataArr[6];
    Planet -> omegaDot = planetDataArr[7];
    Planet -> argPe    = planetDataArr[8];
    Planet -> argPeDot = planetDataArr[9];
    Planet -> mLong    = planetDataArr[10];
    Planet -> mLongDot = planetDataArr[11];
}

void fillDateData(double datesDataArr[6],
                  dates *Date){

    double day, month, year;
    double hour, minutes, sec;

    day     = datesDataArr[0];
    month   = datesDataArr[1];
    year    = datesDataArr[2];
    hour    = datesDataArr[3];
    minutes = datesDataArr[4];
    sec     = datesDataArr[5];

    Date -> day     = day;
    Date -> month   = month;
    Date -> year    = year;
    Date -> hour    = hour;
    Date -> minutes = minutes;
    Date -> sec     = sec;
}


void julianToGregorian(double JD,
                       dates **Date){

    double day, month, year;
    double hour, minutes, sec;
    double N;
    double g, gT1;
    double a;
    double dPrime, dPrimeT1;
    double m, mT1;
    double d, dT1, dT2;
    double datesDataArr[6];

    hour = 12.0;
    minutes = 0.0;
    sec = 0.0;

    gT1 = floor((JD - 4479.5) / 36524.25);
    g = floor(gT1 * 0.75 + 0.5) - 37.0;
    N = JD + g;
    a = floor(N / 365.25) - 4712.0;
    dPrimeT1 = N - 59.25;
    dPrime = floor(Remainder(dPrimeT1, 365.25));
    mT1 = floor((dPrime + 0.5) / 30.6) + 2.0;
    m = Remainder(mT1, 12.0) + 1.0;
    dT1 = (dPrime + 0.5);
    d =  floor(Remainder(dT1, 30.6)) + 1.0;

    year = a;
    month = m;
    day = d;

    datesDataArr[0] = day;
    datesDataArr[1] = month;
    datesDataArr[2] = year;
    datesDataArr[3] = hour;
    datesDataArr[4] = minutes;
    datesDataArr[5] = sec;

    fillDateData(datesDataArr, *Date);

}
