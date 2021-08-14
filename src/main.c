#include <stdio.h>
#include <stdlib.h>
#include "processing/process.h"

int main()
{

   /////////////////////////* ASK FOR PROBLEM *////////////////////////
   char problem[50];
   printf("**************************************\n");
   printf("PORK CHOP PLOT AND TRAJECTORY ANALYSIS\n\n");
   printf("**************************************\n\n\n");
   printf("Enter desired analysis: (PCP / Trajectory): ");
   scanf("%s", problem);
   printf("\n\n\n");

   if (strcmp(problem, "PCP") == 0){

          //////////////////////////* LAMBERT SOLVER *//////////////////////////

       computePCPData();
    }

    else if (strcmp(problem, "Trajectory") == 0){

        //////////////////////////* TRAJECTORY CALCULATION *//////////////////////////

        computeTrajectoryData();
    }

 /* Command to keep .exe open */
    getchar();

    return 0;
}

