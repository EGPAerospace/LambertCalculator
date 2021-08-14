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
