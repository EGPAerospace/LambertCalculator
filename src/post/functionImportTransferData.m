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
