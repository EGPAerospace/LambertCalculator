#include "inputs.h"

void getUserData(inputs *Input){

    printf("INPUT LAMBERT PROBLEM PARAMETERS\n\n");

    printf("Enter departure planet: ");
    scanf("%s", Input->planetDep);

    printf("Enter arrival planet: ");
    scanf("%s", Input->planetArr);

    printf("Enter departure day: ");
    scanf("%lf", &Input->day);

    printf("Enter departure month: ");
    scanf("%lf", &Input->month);

    printf("Enter departure year: ");
    scanf("%lf", &Input->year);

    printf("Enter departure hour (24h): ");
    scanf("%lf", &Input->hour);

    printf("Enter departure minute: ");
    scanf("%lf", &Input->minutes);

    printf("Enter departure second: ");
    scanf("%lf", &Input->sec);

    printf("Enter minimum transfer time (days): ");
    scanf("%lf", &Input->transferTmin);

    printf("Enter maximum transfer time (days): ");
    scanf("%lf", &Input->transferTmax);

    printf("Enter maximum elapsed time from departure (days): ");
    scanf("%lf", &Input->elapsedDep);

    printf("Enter time step (days): ");
    scanf("%lf", &Input->timeStep);

    printf("Enter problem type: ");
    scanf("%d", &Input->problemType);

}

void getUserInputDataFile(inputs *Input,
                          FILE *ptrInputDataFile){

    char planetDep[50], planetArr[50];
    double day, month, year, hour, minutes, sec;
    double transferTmin, transferTmax, elapsedDep, timeStep, problemType;

    fscanf(ptrInputDataFile, "%s"
                             "%s"
                             "%lf"
                             "%lf"
                             "%lf"
                             "%lf"
                             "%lf"
                             "%lf"
                             "%lf"
                             "%lf"
                             "%lf"
                             "%lf"
                             "%d"
                             "\n",
             planetDep, planetArr, &day, &month, &year, &hour,
            &minutes, &sec, &transferTmin, &transferTmax,
            &elapsedDep, &timeStep, &problemType);

            strncpy(Input -> planetDep, planetDep, 50);
            strncpy(Input -> planetArr, planetArr, 50);
            Input -> day = day;
            Input -> month = month;
            Input -> year = year;
            Input -> hour = hour;
            Input -> minutes = minutes;
            Input -> sec = sec;
            Input -> transferTmin = transferTmin;
            Input -> transferTmax = transferTmax;
            Input -> elapsedDep = elapsedDep;
            Input -> timeStep = timeStep;
            Input -> problemType = problemType;
}

void getTransferDates (dates *TransferDep,
                       dates *TransferArr,
                       inputs *Input){

    printf("GET PARTICULAR DATE TRAJECTORY\n\n");

    printf("Enter departure planet: ");
    scanf("%s", Input -> planetDep);

    printf("Enter arrival planet: ");
    scanf("%s", Input -> planetArr);

    printf("Enter departure day: ");
    scanf("%lf", &TransferDep->day);

    printf("Enter departure month: ");
    scanf("%lf", &TransferDep->month);

    printf("Enter departure year: ");
    scanf("%lf", &TransferDep->year);

    printf("Enter arrival day: ");
    scanf("%lf", &TransferArr->day);

    printf("Enter arrival month: ");
    scanf("%lf", &TransferArr->month);

    printf("Enter arrival year: ");
    scanf("%lf", &TransferArr->year);

    printf("Enter problem type: ");
    scanf("%d", &Input->problemType);

    /* Set other date data to defalult */

    TransferDep -> hour = 12.0;
    TransferDep -> minutes = 0.0;
    TransferDep -> sec = 0.0;
    TransferArr -> hour = 12.0;
    TransferArr -> minutes = 0.0;
    TransferArr -> sec = 0.0;

}



void getFileCompleteLambert(dates *TransferDep,
                            dates *TransferArr,
                            orbits *Orbit,
                            FILE *ptrDataFile){

    double dD, mD, yD;
    double dA, mA, yA;
    double dayDepBuf, monthDepBuf, yearDepBuf;
    double dayArrBuf, monthArrBuf, yearArrBuf;
    double a, h, inc, omega, ecc, argPe, trueAnom, vel[3], deltaV;

    dD = TransferDep -> day;
    mD = TransferDep -> month;
    yD = TransferDep -> year;
    dA = TransferArr -> day;
    mA = TransferArr -> month;
    yA = TransferArr -> year;


    while(fscanf(ptrDataFile,  "%lf"
                               "%lf"
                               "%lf"
                               "%lf"
                               "%lf"
                               "%lf"
                               "%lf"
                               "%lf"
                               "%lf"
                               "%lf"
                               "%lf"
                               "%lf"
                               "%lf"
                               "%lf"
                               "%lf"
                               "%lf"
                               "%lf"
                               "\n",
                       &dayDepBuf, &monthDepBuf, &yearDepBuf,
                       &dayArrBuf, &monthArrBuf, &yearArrBuf,
                       &a, &h, &inc, &omega, &ecc, &argPe,
                       &trueAnom, &vel[0], &vel[1], &vel[2], &deltaV) != EOF ){

        if ((dayDepBuf == dD) && (monthDepBuf == mD) && (yearDepBuf == yD)){

            if ((dayArrBuf == dA) && (monthArrBuf == mA) && (yearArrBuf == yA)){

                Orbit -> a        = a;
                Orbit -> h        = h;
                Orbit -> inc      = inc;
                Orbit -> omega    = omega;
                Orbit -> ecc      = ecc;
                Orbit -> argPe    = argPe;
                Orbit -> trueAnom = trueAnom;
                arrCpy(3, vel, Orbit -> vel);

                printf("Date find successfully in PCP.\n");
                break;
            }
        } else {

        }
    }
}


void getFilePlanetData(dates *TransferDep,
                       dates *TransferArr,
                       orbits *OrbitPlanetDep,
                       orbits *OrbitPlanetArr,
                       FILE *ptrDataFile){

    double dD, mD, yD;
    double dA, mA, yA;
    double dayDepBuf, monthDepBuf, yearDepBuf;
    double dayArrBuf, monthArrBuf, yearArrBuf;
    double aDep, hDep, incDep, omegaDep, eccDep, argPeDep, trueAnomDep, rPosDep[3], velDep[3];
    double aArr, hArr, incArr, omegaArr, eccArr, argPeArr, trueAnomArr, rPosArr[3], velArr[3];

    dD = TransferDep -> day;
    mD = TransferDep -> month;
    yD = TransferDep -> year;
    dA = TransferArr -> day;
    mA = TransferArr -> month;
    yA = TransferArr -> year;


    while(fscanf(ptrDataFile, "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "%lf"
                              "\n",
                       &dayDepBuf, &monthDepBuf, &yearDepBuf,
                       &dayArrBuf, &monthArrBuf, &yearArrBuf,
                       &aDep, &hDep, &incDep, &omegaDep, &eccDep, &argPeDep,
                       &trueAnomDep, &rPosDep[0], &rPosDep[1], &rPosDep[2],
                       &velDep[0], &velDep[1], &velDep[2],
                       &aArr, &hArr, &incArr, &omegaArr, &eccArr, &argPeArr,
                       &trueAnomArr, &rPosArr[0], &rPosArr[1], &rPosArr[2],
                       &velArr[0], &velArr[1], &velArr[2]) != EOF ){

        if (dayDepBuf == dD && monthDepBuf == mD && yearDepBuf && yD){

            if (dayArrBuf == dA && monthArrBuf == mA && yearArrBuf && yA){

                /* Copying departure planet data */
                OrbitPlanetDep -> a        = aDep;
                OrbitPlanetDep -> h        = hDep;
                OrbitPlanetDep -> inc      = incDep;
                OrbitPlanetDep -> omega    = omegaDep;
                OrbitPlanetDep -> ecc      = eccDep;
                OrbitPlanetDep -> argPe    = argPeDep;
                OrbitPlanetDep -> trueAnom = trueAnomDep;
                arrCpy(3, rPosDep, OrbitPlanetDep -> rPos);
                arrCpy(3, velDep, OrbitPlanetDep -> vel);

                /* Copying arrival planet data */
                OrbitPlanetArr -> a        = aArr;
                OrbitPlanetArr -> h        = hArr;
                OrbitPlanetArr -> inc      = incArr;
                OrbitPlanetArr -> omega    = omegaArr;
                OrbitPlanetArr -> ecc      = eccArr;
                OrbitPlanetArr -> argPe    = argPeArr;
                OrbitPlanetArr -> trueAnom = trueAnomArr;
                arrCpy(3, rPosArr, OrbitPlanetArr -> rPos);
                arrCpy(3, velArr, OrbitPlanetDep -> vel);

                break;
                }
            }
            else {

            }
        }
}
