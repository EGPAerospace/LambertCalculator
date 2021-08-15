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

#ifndef EPHEM_H_INCLUDED
#define EPHEM_H_INCLUDED

#include <math.h>
#include "arrayuts.h"

#define AU_DIST 149597870700.0 /* AU in meters*/
#define AUToMeters(distAU) ((distAU) * AU_DIST)
#define MU_SUN 1.32712440042E20 /* sun gravitational parameter m3s-2 */
#define MU_EARTH 3.986004418E5
#define Remainder(x, y) (x - (floor((x / y)) * y)) /* calculates modulus for float numbers*/


typedef struct PlanetData{

        double a;
        double aDot;
        double ecc;
        double eccDot;
        double inc;
        double incDot;
        double omega;
        double omegaDot;
        double argPe;
        double argPeDot;
        double mLong;
        double mLongDot;

    } planets;

typedef struct DateData{

        double day;
        double month;
        double year;
        double hour;
        double minutes;
        double sec;

    } dates;


void problemTypeSet(int problemType,
                    planets *Planet);

double julianDate(dates *Date);

void getPlanetData(char namePlanet[30],
                   planets *Planet);

void fillDateData(double datesDataArr[6],
                  dates *Date);

void julianToGregorian(double julianDay,
                       dates **Date);

#endif // EPHEM_H_INCLUDED
