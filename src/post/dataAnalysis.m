%%%%%%%%%%%%%%%%%%%%%% LAMBERT PROJECT ANALYZER %%%%%%%%%%%%%%%%%%%%%%%

clc;
clear all;
close all;

%%%%%%%%%%%%%%%%%%%%%%%%% Importing .txt files %%%%%%%%%%%%%%%%%%%%%%%%  
fileNameInputs = '\LambertCalculator\data\InputData.txt';
fileNameLambert = '\LambertCalculator\data\LambertSolutionDataShort.txt';
fileNameTrajectory = '\LambertCalculator\data\TrajectoryPoints.txt';
fileNameTransferDates = '\LambertCalculator\data\TransferData.txt';

DataInputStruct = functionImportInputData(fileNameInputs);
rawDataLambert = functionImportData(fileNameLambert, '%f');
rawDataTrajectories = functionImportData(fileNameTrajectory, '%f');
DataTransferStruct = functionImportTransferData(fileNameTransferDates);
numCols = 3;

%_____________________________________________________________________%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%% PORK CHOP PLOT %%%%%%%%%%%%%%%%%%%%%%%%%%%

% Configuration of the program
stepDep = DataInputStruct.timeStep;
maxDep = DataInputStruct.elapsedDep;
departure = 0:stepDep:maxDep;

stepTrans = DataInputStruct.timeStep;
minTrans = DataInputStruct.transferTmin;
maxTrans = DataInputStruct.transferTmax;
transfer = minTrans:stepTrans:maxTrans;
width = (maxTrans - minTrans) / stepTrans;


% Reordering columns in original format
j = 1;
for i = 1:numCols:length(rawDataLambert)
    sortedData(j, 1) = rawDataLambert(i, 1);
    sortedData(j, 2) = rawDataLambert(i + 1, 1);
    sortedData(j, 3) = rawDataLambert(i + 2, 1);
    j = j + 1;
end

[X, Y] = meshgrid(transfer, departure);


% Set a meshgride-like departure date format
posNew = 1;
posFinal = width + 1; 
maxLength = (maxDep / stepDep)+1;
for i = 1:maxLength

    deltaV(:, i) = sortedData(posNew:posFinal, 3); 
    posNew = posFinal + 1;
    posFinal = posNew + width;
    
end

% Delta V in km/s
deltaV = deltaV ./ 1000;

%%%%%%%%%%%%%%%%%%%%%%%%%%%% Plotting data %%%%%%%%%%%%%%%%%%%%%%%%%%%%
pDep = DataInputStruct.planetDep;
pArr = DataInputStruct.planetArr;
day = DataInputStruct.day;
month = DataInputStruct.month;
year = DataInputStruct.year;

figure(1)
contourf(X, Y, deltaV', 200, 'edgecolor', 'none');
title(sprintf('%s to %s transfer starting at %g/%g/%g',...
    pDep, pArr, day, month, year), 'FontSize', 14, 'Interpreter', 'latex');
xlabel('Transfer time (days)', 'FontSize', 14, 'Interpreter', 'latex');
ylabel('Elapsed days from departure', 'FontSize', 14, 'Interpreter', 'latex');

% Additional on contourf plot
shading interp
colormap jet
hcb=colorbar;
hcb.Label.Interpreter = 'latex';
hcb.Label.String = 'Km / s';
hcb.Label.FontSize = 14;

%_____________________________________________________________________%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%% TRAJECTORY DATA %%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Sorting trajectory data
j = 1;
for i = 1:numCols:length(rawDataTrajectories)
    sortedDataTrajectories(j, 1) = rawDataTrajectories(i, 1);
    sortedDataTrajectories(j, 2) = rawDataTrajectories(i + 1, 1);
    sortedDataTrajectories(j, 3) = rawDataTrajectories(i + 2, 1);
    j = j + 1;
end
sortedDataTrajectories = sortedDataTrajectories / 149597870700.0;

xTraj = sortedDataTrajectories(:, 1);
yTraj = sortedDataTrajectories(:, 2);
zTraj = sortedDataTrajectories(:, 3);

pDep = DataTransferStruct.planetDep;
pArr = DataTransferStruct.planetArr;
dayDep = DataTransferStruct.dayDep;
monthDep = DataTransferStruct.monthDep;
yearDep = DataTransferStruct.yearDep;
dayArr = DataTransferStruct.dayArr;
monthArr = DataTransferStruct.monthArr;
yearArr = DataTransferStruct.yearArr;

figure(2)
plot3(xTraj, yTraj, zTraj, 'k', 'LineWidth', 2); 
% Drawing sun
hold on
scatter3(0, 0, 0, 200, 'y', 'filled');
% Drawing departure planet
hold on
scatter3(xTraj(1, 1), yTraj(1, 1), zTraj(1, 1), 50, 'b', 'filled');
% Drawing arrival planet
hold on
scatter3(xTraj(end, 1), yTraj(end, 1), zTraj(end, 1), 50, 'r', 'filled');

grid on;
xlabel('x-axis [AU]', 'FontSize', 14, 'Interpreter', 'latex');
ylabel('y-axis [AU]', 'FontSize', 14, 'Interpreter', 'latex');
zlabel('z-axis [AU]', 'FontSize', 14, 'Interpreter', 'latex');
legend('Transfer', 'Sun', pDep, pArr);
title(sprintf('%s to %s \n (%g/%g/%g) - (%g/%g/%g)',...
    pDep, pArr, dayDep, monthDep, yearDep, dayArr, monthArr, yearArr),...
    'FontSize', 14, 'Interpreter', 'latex');


