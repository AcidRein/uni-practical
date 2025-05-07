clear
clc
%% Adds player and Flag to maze
% This function will take the maze size as an input, and show all 4
% quadrants, with white image being areas the player/flag can spawn

% Player and Flag addition
function [res] = criticalSpawn(MAPROW, MAPCOL)

    % Small math to find minimum and maximum position 
    % Find the row and column of the maze

    % Find the row that is in the middle of the maze
    PLAYERHEIGHTMID = ((MAPROW-1)/2); 
    % Find the column that is in the middle of the maze
    PLAYERWIDTHMID = ((MAPCOL-1)/2);
    res = zeros(MAPROW, MAPCOL);

    % If Odd number, make even to easily divide
    if mod(PLAYERHEIGHTMID, 2) == 1
        PLAYERHEIGHTMID = PLAYERHEIGHTMID - 1;
    end
    if mod(PLAYERWIDTHMID, 2) == 1
        PLAYERWIDTHMID = PLAYERWIDTHMID - 1;
    end

    for i = 1:1000 % For loop instead of while loop for easier break
        % Choose a random Quadrant
        quadrant = randi([1,4]);

        % Set 4 as minimum boundary to prevent spawning out of bounds
        % Use math to randomize a spawn that is a bit further away from the
        % middle in a given quadrant.

        switch quadrant
            case 1 % (TOP LEFT)

                posY = randi([4, PLAYERHEIGHTMID/2]); 
                posX = randi([4, PLAYERWIDTHMID/2]); 
            
            case 2 % (TOP RIGHT)

                posY = randi([4, PLAYERHEIGHTMID/2]); 
                posX = randi([PLAYERWIDTHMID + PLAYERWIDTHMID/2, MAPCOL - 4]); 
    
            case 3 % (BOTTOM LEFT)

                posY = randi([PLAYERHEIGHTMID + PLAYERHEIGHTMID/2, MAPROW - 4]); 
                posX = randi([4, PLAYERWIDTHMID/2]); 
    
            case 4 % (BOTTOM RIGHT)

                posY = randi([PLAYERHEIGHTMID + PLAYERHEIGHTMID/2, MAPROW - 4]); 
                posX = randi([PLAYERWIDTHMID + PLAYERWIDTHMID/2, MAPCOL - 4]); 
        end

        % Change color to white to show it is accessible
        res(posY, posX) = 1;

    end
end

% Display possible player/flag spawn in each quadrant for a 51x51 maze
possibleSpawn = criticalSpawn(51, 51);
imshow(possibleSpawn);
imwrite(possibleSpawn, 'possible_playerFlagSpawn.jpeg');