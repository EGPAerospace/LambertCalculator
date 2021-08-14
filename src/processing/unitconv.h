#ifndef UNITCONV_H_INCLUDED
#define UNITCONV_H_INCLUDED

#include <math.h>

#define _USE_MATH_DEFINES
#define radToDeg(angleInRadians) ((angleInRadians) * (180.0 / M_PI))
#define degToRad(angleInDegrees) ((angleInDegrees) * (M_PI / 180.0))
#define arcsecToDeg(angleInArcsec) ((angleInArcsec) * (1.0 / 3600.0))
#define arcsecToRad(angleInArcsec) ((angleInArcsec) * (M_PI / (180.0 * 3600.0)))

#endif // UNITCONV_H_INCLUDED
