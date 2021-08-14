%%%%%%%%%%%%%%%%%%%%%%%% FUNCTION IMPORT DATA %%%%%%%%%%%%%%%%%%%%%%%%%%

function[rawData] = functionImportData(fileName, formatSpec)

fileID = fopen(fileName,'r');
rawData = fscanf(fileID,formatSpec);