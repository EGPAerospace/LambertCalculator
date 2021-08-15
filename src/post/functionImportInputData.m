%{

The MIT License (MIT)

Copyright (c) 2021 EGPAerospace

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

%}

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