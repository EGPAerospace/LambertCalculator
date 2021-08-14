%%%%%%%%%%%%%%%%%%%%% FUNCTION IMPORT INPUT DATA %%%%%%%%%%%%%%%%%%%%%%%%

function[DataInputStruct] = functionImportInputData(fileName)

fileID = fopen(fileName,'r');
rawData = fscanf(fileID, '%c');
DataInput = strsplit(rawData,'\t');

% Store in struct
DataInputStruct.planetDep    = convertCharsToStrings(DataInput{1});
DataInputStruct.planetArr    = convertCharsToStrings(DataInput{2});
DataInputStruct.day          = str2double(DataInput{3});
DataInputStruct.month        = str2double(DataInput{4});
DataInputStruct.year         = str2double(DataInput{5});
DataInputStruct.hour         = str2double(DataInput{6});
DataInputStruct.minutes      = str2double(DataInput{7});
DataInputStruct.sec          = str2double(DataInput{8});
DataInputStruct.transferTmin = str2double(DataInput{9});
DataInputStruct.transferTmax = str2double(DataInput{10});
DataInputStruct.elapsedDep   = str2double(DataInput{11});
DataInputStruct.timeStep     = str2double(DataInput{12});