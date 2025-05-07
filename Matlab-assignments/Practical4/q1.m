clear
clc
%% Black to White Vertical Image

% Initialize image data
imageData = []; % 2D array
imSize = 100;
numRows = imSize;
numCols = imSize;

% Populate imageData
for row = [1:numRows]
    imageRow = []; % Empty array to populate each row
    for col = [1:numCols]
        % If we want to achieve vertical, we determine each pixelVal by the
        % current Row
        pixelVal = uint8(row/100 * 255); % Transform each pixel to range 0 - 255 in uint8 Form
        imageRow = [imageRow, pixelVal];
    end
    imageData = [imageData; imageRow]; % Concatenate new row to imageData
end


% display as an image
imshow(imageData);

% save as an image
imwrite(imageData,'test1.png');
