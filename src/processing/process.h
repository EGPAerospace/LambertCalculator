#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "inputs.h"
#include "rootFinding.h"
#include "keplerian.h"
#include "lambert.h"
#include "matrixops.h"
#include "arrayuts.h"
#include "ephem.h"
#include "unitconv.h"
#include "postprocess.h"

void computePCPData();

void computeTrajectoryData();




#endif // PROCESS_H_INCLUDED
