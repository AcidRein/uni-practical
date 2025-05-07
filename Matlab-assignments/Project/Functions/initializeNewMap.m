%% Script handles generating the structure map of the maze

%% Main Map function
function [newMapArray, playerX, playerY, flagX, flagY] = initializeNewMap(curLevel, MAZEPATHCOLOR, PLAYERCOLOR)

    fprintf('\nLoading Level %d...\n', curLevel)
    % Get the difficulty of the next maze from the current level.
    [width, height] = difficultyAlgo(curLevel);

    % Generate a map template grid with given width and height
    mapTemplate = mapArrayTemplate(width, height, MAZEPATHCOLOR);
    OUTTERWIDTH = 3;
    
    % Rule to Choosinng where to start map generation 
    % Starting at a random even-numbered array that is:
    % within the maze boundary
    % and not starting on a wall (must be even)

    % Random math to determine the minimum/maximum starting point
    min = floor(height/2) - floor(height/4);
    max = ceil(width/2) + ceil(width/4);

    % Choose where to start map generation 
    % Starting at a random even-numbered array that is:
    % within the maze boundary
    % and not starting on a wall (must be even)
    mapInitX = randi([min, max]); % (Col)
    mapInitY = randi([min, max]); % (Row)
    
     % Make the initial spawn point of algorithm even so it spawns on a
     % path
    if mod(mapInitX, 2) ~= 0
        mapInitX = mapInitX - 1;
    end
    if mod(mapInitY, 2) ~= 0
        mapInitY = mapInitY - 1;
    end

    %fprintf('Starting: %d, %d\nSize: %d, %d\n', mapInitX, mapInitY, width, height);
    
    % Begin recursive algorithm
    newMapArray = recursiveBacktracking(mapInitX, mapInitY, mapTemplate);

    fprintf('Completed Maze generation for size (%dx%d). Spawning Objects...\n', width, height);
    % Turn all unvisited path to walls, and all visited path to paths
    for i = 1:height
        for j = 1:width
            if newMapArray(i, j) == MAZEPATHCOLOR
                newMapArray(i, j) = 0;
            elseif newMapArray(i, j) == 0.5
                newMapArray(i, j) = MAZEPATHCOLOR;
            end
        end
    end

    % Adding player spawn and Flag spawn
    % Player spawns in a random quadrant
    playerQuadrant = randi([1, 4]);
    % Call the function to generate a random position for Player
    [playerX, playerY] = spawnPoints(playerQuadrant, newMapArray, MAZEPATHCOLOR);
    newMapArray(playerY, playerX) = PLAYERCOLOR;

    %Flag Spawn in the opposite quadrant from player
    flagQuadrant = 5 - playerQuadrant;
    % Call the function to generate a random position for Flag
    [flagX, flagY] = spawnPoints(flagQuadrant, newMapArray, MAZEPATHCOLOR);
    newMapArray(flagY, flagX) = 0.7; % Flag color;

    %fprintf('Successfully loaded level %d!\n', curLevel);
end

%% Difficulty calculator (Size of maze)
function [mapWidth, mapHeight] = difficultyAlgo(curLevel) 
    % Ups the difficulty of the maze every RAMP_LEVEL level.
    RAMP_LEVEL = 1; 
    difficulty = ceil(curLevel / RAMP_LEVEL) - 1; % -1 so difficulty starts at 0;
    
    mapWidth = 21; % Initial map width 
    mapHeight = 21; % Initial map height

    for i = 1:difficulty % Increase map width nd height as the difficulty increases
        if mod(i, 2) == 1
            mapWidth = mapWidth + 2;
        else
            mapHeight = mapHeight + 2;
        end
    end
    return
end

% Player and Flag addition
function [posX, posY] = spawnPoints(quadrant, mazeArray, MAZEPATHCOLOR)
    % Small math to find minimum and maximum position 
    [MAPROW, MAPCOL] = size(mazeArray);

    % If Even number, make Odd
    if mod(MAPROW, 2) == 0
        MAPROW = MAPROW - 1;
    end
    if mod(MAPCOL, 2) == 0
        MAPCOL = MAPCOL - 1;
    end

    PLAYERHEIGHTMID = ((MAPROW-1)/2); 
    PLAYERWIDTHMID = ((MAPCOL-1)/2);

    % If Odd number, make even
    if mod(PLAYERHEIGHTMID, 2) == 1
        PLAYERHEIGHTMID = PLAYERHEIGHTMID - 1;
    end
    if mod(PLAYERWIDTHMID, 2) == 1
        PLAYERWIDTHMID = PLAYERWIDTHMID - 1;
    end

    for i = 1:100 % For loop instead of while loop to in case there's absolutely no space
        % Set 4 as minimum boundary to prevent spawning out of bounds
        % Use math to randomize a spawn that is furthest away from the
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
    
            otherwise % DEFAULT TO TOP LEFT (corners are always free from walls*)
                posY = 4;
                posX = 4;
                fprintf('Error randomizing spawnPoint, defaulting to corner\n');
        end

        if (mazeArray(posY, posX) == MAZEPATHCOLOR) % Prevent from spawning inside a wall
            break
        end

    end
end

%% Maze generation Utility
% Initialize a new template of the map
function newMapTemplate = mapArrayTemplate(width, height, MAZEPATHCOLOR) 

    newMapTemplate = zeros(height, width);
    % OUTTERWIDTH - Mark outside of map as visited, so our algo doesnt go
    % out of bounds.
    OUTTERWIDTH = 3; % DO NOT TOUCH!    
    % Create a grid-template of the maze to prepare our algorithm.
    for row = 1:height
        for col = 1:width
            % If outside the border, make it already discovered (grey color)
            if (row < OUTTERWIDTH || row > height - OUTTERWIDTH + 1) || (col < OUTTERWIDTH || col > width - OUTTERWIDTH + 1)
                newMapTemplate(row, col) = 0.5;
            % Creating the border that surrounds the maze (black color) 
            elseif (row == OUTTERWIDTH || row == height - OUTTERWIDTH + 1) || (col == OUTTERWIDTH || col == width - OUTTERWIDTH + 1)
                newMapTemplate(row, col) = 0;
            % Leave all odd parts inside the maze a wall (black), and even part of the map
            % a path (white)
            elseif mod(row, 2) == 0 || mod(col, 2) == 0
                newMapTemplate(row, col) = MAZEPATHCOLOR;
            end
        end
    end
    return    
end

% The backtracking Algorithm was Heavily inspired from the source: https://aryanab.medium.com/maze-generation-recursive-backtracking-5981bc5cc766
% However, I took the principal of the algorithm and put it into matlab by myself.
%{ 
% backtracking Algorithm RULES: 
% Select a random cell to start.
% Choose a random adjacent cell. Only create a passage if that cell has not been visited yet.
% Repeat the process until there are no more adjacent cells to choose from.
% Start backtracking until you can choose a cell again.
% The algorithm is done when you return to the starting cell.
%}
function finalMaze = recursiveBacktracking(posX, posY, mapVector)
    global finalMaze % Make finalMaze a global variable so it is not constrained to the function
    finalMaze = mapVector;
    finalMaze(posY, posX) = 0.5; % Mark the current area visited
    
    % if the grid after next grid is already visited / does NOT exist (Prevents from leaving the maze)  
    if (finalMaze(posY - 2, posX)) == 0.5 && (finalMaze(posY + 2, posX)) == 0.5 && (finalMaze(posY, posX - 2)) == 0.5 && (finalMaze(posY, posX + 2)) == 0.5
        % Do nothing but go to the end of the function
    else % Otherwise
        % Possible movement where
        % 1 = LEFT
        % 2 = RIGHT
        % 3 = UP
        % 4 = DOWN
        movementPos = [1, 2, 3, 4];

        % Loop through to check available movements
        while ~(isempty(movementPos))
            % Chooses a random movement
            randIndex = randi([1, length(movementPos)]);
            randMovement = movementPos(randIndex);
            % Remove the random movement from the list
            movementPos(randIndex) = []; 
            
            % Creates a looking position where newXY looks 2 grids ahead,
            % and we move those 2 grids if available

            if randMovement == 1 % If left movement
                newX = posX - 2;
                mewX = posX - 1;
            elseif randMovement == 2 % If Right movement
                newX = posX + 2;
                mewX = posX + 1;
            else
                newX = posX;
                mewX = posX;
            end

            if randMovement == 3 % If Up movement
                newY = posY - 2;
                mewY = posY - 1;
            elseif randMovement == 4 % If Down movement
                newY = posY + 2;
                mewY = posY + 1;
            else % If something went wrong
                newY = posY;
                mewY = posY;
            end

            % Check if grid is already occupied
            if finalMaze(newY, newX) ~= 0.5
                % If the grid after the next is NOT occupied (i.e color white/black),
                finalMaze(mewY, mewX) = 0.5;
                % Continue the travel through recursive Call 
                recursiveBacktracking(newX, newY, finalMaze);
            end
        end

    end
end
