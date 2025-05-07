clear
clc
%% White to Black Vertical Image

% Initialize image data
imageData = []; % 2D array
imSize = 100;
numRows = imSize;
numCols = imSize;

% Populate imageData
for row = [1:numRows]
    imageRow = []; % Empty array to populate each row
    for col = [1:numCols]
        % Determine each color by current row
        % As row/100 provides image going from 0 - 1, (Black to white)
        % We can reverse this by minusing 1 so we get 1 - 0 (White to
        % black)
        
        pixelVal = uint8((1 - (row/100)) * 255); % Transform each pixel to range 0 - 255 in uint8 Form
        imageRow = [imageRow, pixelVal];
    end
    imageData = [imageData; imageRow]; % Concatenate new row to imageData
end


% display as an image
imshow(imageData);

% save as an image
imwrite(imageData,'test2.png');
