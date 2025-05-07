clear
clc
%% Flipped and Flopped image of the Kandinsky painting
    
% load an image
imageData = imread('Kand.png'); % Array of the kand image data

% Initialize image information
[numRows, numCols] = size(imageData);
newImageData = uint8(zeros(numRows, numCols)); % Initalize uint8 zeros to save memory 
% and make the array a 'uint8' value

% Transforming image
for row = 1:numRows
    for col = 1:numCols
        % Flipping image Horizontally and Vertically
        % we use numRows/Cols to inverse the array, and we use '-1' to
        % start indexing from 0 (to avoid any non-positive integers)
        flippedRow = numRows - (row - 1); % Inverse number of rows
        flippedCol = numCols - (col - 1); % Inverse number of cols
        newImageData(row, col) = uint8(imageData(flippedRow, flippedCol));
    end
end

% display as an image
imshow(newImageData);

% save as an image
imwrite(newImageData,'KandFlipped.png');

