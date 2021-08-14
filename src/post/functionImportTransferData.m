%%%%%%%%%%%%%%%%%%%%% FUNCTION IMPORT TRANSFER DATA %%%%%%%%%%%%%%%%%%%%%

function[DataTransferStruct] = functionImportTransferData(fileName)

fileID = fopen(fileName,'r');
rawData = fscanf(fileID, '%c');
DataInput = strsplit(rawData,'\t');

% Store in struct
DataTransferStruct.planetDep    = convertCharsToStrings(DataInput{1});
DataTransferStruct.planetArr    = convertCharsToStrings(DataInput{2});
DataTransferStruct.dayDep       = str2double(DataInput{3});
DataTransferStruct.monthDep     = str2double(DataInput{4});
DataTransferStruct.yearDep      = str2double(DataInput{5});
DataTransferStruct.dayArr       = str2double(DataInput{6});
DataTransferStruct.monthArr     = str2double(DataInput{7});
DataTransferStruct.yearArr      = str2double(DataInput{8});
