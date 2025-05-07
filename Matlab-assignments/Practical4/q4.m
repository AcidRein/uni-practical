clear
clc
%% White to Black Horizontal image

% Initialize image data
imageData = []; % 2D array
imSize = 100;
numRows = imSize;
numCols = imSize;

% Populate imageData
for row = [1:numRows]
    imageRow = []; % Empty array to populate each row
    for col = [1:numCols]
        % Determine each color by current col
        % Inverse of q3 using 1 - ans.
        pixelVal = uint8((1 - (col/numCols)) * 255); % Transform each pixel to range 0 - 255 in uint8 Form
        imageRow = [imageRow, pixelVal];
    end
    imageData = [imageData; imageRow]; % Concatenate new row to imageData
end


% display as an image
imshow(imageData);

% save as an image
imwrite(imageData,'test4.png');

