clear
clc
%% Volume of a 3D Rectangle

% Input
rectHeight = input("Rectangle Height: ");
rectWidth = input("Rectangle Width: ");
rectDepth = input("Rectangle Depth: ");

% Verify Input by making all values positive
if rectHeight < 0
    rectHeight = abs(rectHeight);
end

if rectWidth < 0
    rectWidth = abs(rectWidth);
end

if rectDepth < 0
    rectDepht = abs(rectDepth);
end 

% Calculate
rectVolume = rectHeight * rectWidth * rectDepth;

% Print Case
fprintf('%d\n', rectVolume);
