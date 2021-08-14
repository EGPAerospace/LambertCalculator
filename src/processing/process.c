#include "process.h"

void computePCPData(){

    /* Input block declaration */
    inputs Input;
    planets PlanetDep, PlanetArr;
    dates DateDepOrig, DateArr;
    dates *ptrDDepOrig = &DateDepOrig, *ptrDArr = &DateArr;
    dates **ptrDDepOrig2 = &ptrDDepOrig, **ptrDArr2 = &ptrDArr;
    char planetDeparture[30], planetArrival[30];
    double depOrigDataArray[6];

    /* Lambert solver block declaration */
    lamberts LambertShort, LambertLong;
    orbits OrbitPlanetDep, OrbitPlanetArr;
    orbits OrbitLambertShort, OrbitLambertLong;
    orbits *ptrOrbLambShort = &OrbitLambertShort, *ptrOrbLambLong = &OrbitLambertLong;
    orbits **ptrOrbLambShort2 = &ptrOrbLambShort, **ptrOrbLambLong2 = &ptrOrbLambLong;
    double initialjDDeparture, jDDeparture, jDArrival;
    double transferTmin, transferTmax, elapsedDep;
    double actualDepartureTime, timeStepDeparture;
    double actualArrivalTime, actualArrivalTimeSeconds, timeStepArrival;
    double rPlanetDep[3], rPlanetArr[3], vTransferDep[3], vTransferArr[3];
    double mu = MU_SUN;
    double deltaVDepShort, deltaVArrShort, deltaVTotShort;
    double deltaVDepLong, deltaVArrLong, deltaVTotLong;
    FILE *dataInput, *in, *in2, *pFile;


    /* Ask for user inputs */
    getUserData(&Input);

    /* Store names of planets */
    strcpy(planetDeparture, Input.planetDep);
    strcpy(planetArrival, Input.planetArr);

    /* Get planets Ephemeris */
    getPlanetData(planetDeparture, &PlanetDep);
    getPlanetData(planetArrival, &PlanetArr);

    /* Modify planets Ephemeris according to problem type */
    problemTypeSet(Input.problemType, &PlanetDep);
    problemTypeSet(Input.problemType, &PlanetArr);

    /* Store departure date */
    depOrigDataArray[0] = Input.day;
    depOrigDataArray[1] = Input.month;
    depOrigDataArray[2] = Input.year;
    depOrigDataArray[3] = Input.hour;
    depOrigDataArray[4] = Input.minutes;
    depOrigDataArray[5] = Input.sec;
    fillDateData(depOrigDataArray, &DateDepOrig);

    /* Opening file to store results */
    dataInput = fopen("data/InputData.txt", "w");
    in = fopen("data/LambertSolutionDataLong.txt", "w");
    in2 = fopen("data/LambertSolutionDataShort.txt", "w");
    pFile = fopen("data/PlanetsData.txt", "w");

    /* Print Input data on a file */
    printInputData(dataInput, &Input);
    fclose(dataInput);

    /* Calculation of Original Julian Day departure */
    initialjDDeparture = julianDate(&DateDepOrig);

    /* The other departure dates are ellapsed from original one*/
    actualDepartureTime =  0.0;
    timeStepDeparture = Input.timeStep;
    timeStepArrival = Input.timeStep;

    while(actualDepartureTime <= Input.elapsedDep){

        /* Calculating Julian date number and Gregorian calendar for each iteration*/
        jDDeparture = initialjDDeparture + actualDepartureTime;
        julianToGregorian(jDDeparture, ptrDDepOrig2);

        /* Orbit parameters of departure planet */
        planetEphemerides(&PlanetDep, ptrDDepOrig2, &OrbitPlanetDep, mu);

        /* Fix a departure and calculate for all the transfer times*/
        actualArrivalTime = Input.transferTmin;

        while(actualArrivalTime <= Input.transferTmax){

            jDArrival = jDDeparture + actualArrivalTime;
            julianToGregorian(jDArrival, ptrDArr2);

            /* Orbit parameters of arrival planet */
            planetEphemerides(&PlanetArr, ptrDArr2, &OrbitPlanetArr, mu);

            /* Printing data of both departure and arrival planets*/
            printPlanetsData(pFile, &DateDepOrig, &DateArr, &OrbitPlanetDep, &OrbitPlanetArr);

            /* Calculating Lambert transfer orbit for long and short ways */
            arrCpy(3, OrbitPlanetDep.rPos, rPlanetDep);
            arrCpy(3, OrbitPlanetArr.rPos, rPlanetArr);
            actualArrivalTimeSeconds = actualArrivalTime * 86400.0;


            universalLambert(rPlanetDep, rPlanetArr,
                             actualArrivalTimeSeconds, 1, mu,
                             &LambertShort, ptrOrbLambShort2);

            universalLambert(rPlanetDep, rPlanetArr,
                             actualArrivalTimeSeconds, -1, mu,
                             &LambertLong, ptrOrbLambLong2);

            /* Calculating deltaV */
            deltaVDepShort = deltaVCalc(LambertShort.velDeparture, OrbitPlanetDep.vel);
            deltaVArrShort = deltaVCalc(LambertShort.velArrival, OrbitPlanetArr.vel);
            LambertShort.deltaV = deltaVArrShort + deltaVDepShort;

            deltaVDepLong = deltaVCalc(LambertLong.velDeparture, OrbitPlanetDep.vel);
            deltaVArrLong = deltaVCalc(LambertLong.velArrival, OrbitPlanetArr.vel);
            LambertLong.deltaV = deltaVArrLong + deltaVDepLong;

            /* Printing results on file */

            if(LambertShort.deltaV <= LambertLong.deltaV){

                if (isnan(LambertShort.deltaV)||(LambertShort.deltaV >= 50000.0)){
                     LambertShort.deltaV = 50000.0;
                }

                printCompleteLambertResults(in, &DateDepOrig, &DateArr, &OrbitLambertShort, &LambertShort);
                printShortLambertResults(in2, actualDepartureTime, actualArrivalTime, &LambertShort);

            } else{

                if (isnan(LambertLong.deltaV)||(LambertLong.deltaV >= 50000.0)){
                    LambertLong.deltaV = 50000.0;
                }

                printCompleteLambertResults(in, &DateDepOrig, &DateArr, &OrbitLambertLong, &LambertLong);
                printShortLambertResults(in2, actualDepartureTime, actualArrivalTime, &LambertLong);
           }

            /* Calculating new transfer time in arrival */
            actualArrivalTime = actualArrivalTime + timeStepArrival;
        }

        /* Calculating new transfer time in departure */
        actualDepartureTime = actualDepartureTime + timeStepDeparture;
     }

     /* Closing data files */
     fclose(in);
     fclose(in2);
     fclose(pFile);
}


void computeTrajectoryData(){

    inputs InputTrajectory;
    dates TransferDep, TransferArr;
    planets PlanetDep, PlanetArr;
    dates DateDepOrig, DateArr;
    dates *ptrDDepOrig = &DateDepOrig, *ptrDArr = &DateArr;
    dates **ptrDDepOrig2 = &ptrDDepOrig, **ptrDArr2 = &ptrDArr;
    lamberts LambertShort, LambertLong, LambertFinal;
    orbits OrbitPlanetDep, OrbitPlanetArr;
    orbits OrbitLambertShort, OrbitLambertLong, OrbitLambertFinal;
    orbits *ptrOrbLambShort = &OrbitLambertShort, *ptrOrbLambLong = &OrbitLambertLong;
    orbits **ptrOrbLambShort2 = &ptrOrbLambShort, **ptrOrbLambLong2 = &ptrOrbLambLong;

    double jDTransDep, jDTransArr;
    double deltaTTrans;
    double timeStep;
    double rArr[3];
    double mu = MU_SUN;
    double rPlanetDep[3], rPlanetArr[3], vTransferDep[3], vTransferArr[3];
    double deltaVDepShort, deltaVArrShort, deltaVTotShort;
    double deltaVDepLong, deltaVArrLong, deltaVTotLong;
    FILE *fileTransfers, *fileOrbitTransferData, *fileTrajectory;

    fileTransfers = fopen("data/TransferData.txt", "w");
    fileOrbitTransferData = fopen("data/TransferOrbitalData.txt", "w");

    /* Get user input data */
    getTransferDates (&TransferDep, &TransferArr, &InputTrajectory);
    printTransferDates(fileTransfers, &TransferDep, &TransferArr, &InputTrajectory);

    fclose(fileTransfers);

    /* Get initial planet Ephemeris */
    getPlanetData(InputTrajectory.planetDep, &PlanetDep);
    getPlanetData(InputTrajectory.planetArr, &PlanetArr);

    /* Modify planets Ephemeris according to problem type */
    problemTypeSet(InputTrajectory.problemType, &PlanetDep);
    problemTypeSet(InputTrajectory.problemType, &PlanetArr);

    /* Calculating Julian dates */
    jDTransDep = julianDate(&TransferDep);
    jDTransArr = julianDate(&TransferArr);

    /* Conversion of days to seconds */
    deltaTTrans = (jDTransArr - jDTransDep) * 86400.0;

    /* Orbit parameters of departure planet */
    julianToGregorian(jDTransDep, ptrDDepOrig2);
    planetEphemerides(&PlanetDep, ptrDDepOrig2, &OrbitPlanetDep, mu);

    /* Orbit parameters of arrival planet */
    julianToGregorian(jDTransArr, ptrDArr2);
    planetEphemerides(&PlanetArr, ptrDArr2, &OrbitPlanetArr, mu);

    /* Calculating Lambert transfer orbit for long and short ways */
    arrCpy(3, OrbitPlanetDep.rPos, rPlanetDep);
    arrCpy(3, OrbitPlanetArr.rPos, rPlanetArr);

    universalLambert(rPlanetDep, rPlanetArr, deltaTTrans, 1, mu,
                     &LambertShort, ptrOrbLambShort2);

    universalLambert(rPlanetDep, rPlanetArr, deltaTTrans, -1, mu,
                     &LambertLong, ptrOrbLambLong2);

    /* Calculating deltaV */
    deltaVDepShort = deltaVCalc(LambertShort.velDeparture, OrbitPlanetDep.vel);
    deltaVArrShort = deltaVCalc(LambertShort.velArrival, OrbitPlanetArr.vel);
    LambertShort.deltaV = deltaVArrShort + deltaVDepShort;

    deltaVDepLong = deltaVCalc(LambertLong.velDeparture, OrbitPlanetDep.vel);
    deltaVArrLong = deltaVCalc(LambertLong.velArrival, OrbitPlanetArr.vel);
    LambertLong.deltaV = deltaVArrLong + deltaVDepLong;


    if(LambertShort.deltaV <= LambertLong.deltaV){

        LambertFinal = LambertShort;
        OrbitLambertFinal = OrbitLambertShort;
    }

    else{

        LambertFinal = LambertLong;
        OrbitLambertFinal = OrbitLambertLong;
    }

    /* Printing tranfer orbit elements */
    printCompleteLambertResults(fileOrbitTransferData,
                                &TransferDep,
                                &TransferArr,
                                &OrbitLambertFinal,
                                &LambertFinal);

    timeStep = 0.0;
    fileTrajectory = fopen("data/TrajectoryPoints.txt", "w");

    while (timeStep <= deltaTTrans){

        orbitTrajectoryTime(OrbitPlanetDep.rPos,
                            LambertFinal.velDeparture,
                            mu, timeStep, rArr);

        printTrajectoryPoints(fileTrajectory, rArr);
        timeStep = timeStep + 1.0 * 86400.0;
    }

    fclose(fileOrbitTransferData);
    fclose(fileTrajectory);


}


