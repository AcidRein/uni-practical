clear
clc
%% Star image

% Initialize image data
imageData = []; % 2D array
imSize = 100;
numRows = imSize;
numCols = imSize;

% Populate imageData
for row = [1:numRows]
    imageRow = []; % Empty array to populate each row
    for col = [1:numCols]
        % Decrease color intensity as it approaches middle
        colMiddle = abs(col-(numCols/2)); % The distance between col and middle of col size.
        rowMiddle = abs(row-(numRows/2)); % The distance between row and middle of row size.
        pixelVal = uint8(((colMiddle/imSize) + (rowMiddle/imSize)) * 255); % add the middle distance from row and column and Convert to uint8
        imageRow = [imageRow, pixelVal];
    end
    imageData = [imageData; imageRow]; % Concatenate new row to imageData
end


% display as an image
imshow(imageData);

% save as an image
imwrite(imageData,'test5.png');

