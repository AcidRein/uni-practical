clear
clc
clearvars fig
%% recursive backtracking Map generation #2 (evidence of learning)
%{
% RULES: 
% Select a random cell to start.
% Choose a random adjacent cell. Only create a passage if that cell has not been visited yet.
% Repeat the process until there are no more adjacent cells to choose from.
% Start backtracking until you can choose a cell again.
% The algorithm is done when you return to the starting cell (original call of function).
%}

% Source for the map generation: https://aryanab.medium.com/maze-generation-recursive-backtracking-5981bc5cc766
%% Utility Function
function newMap = mapGenAlgo(posX, posY, curMap, showMapLoad)
    global newMap % Make newMap a global variable so it is not constrained to the function
    newMap = curMap;
    newMap(posY, posX) = 0.5; % Mark the current area visited
    
    % if the grid after next grid is already visited / does NOT exist (Prevents from leaving the maze)  
    fprintf('(%d, %d)\n', posX, posY);
    if (newMap(posY - 2, posX)) == 0.5 && (newMap(posY + 2, posX)) == 0.5 && (newMap(posY, posX - 2)) == 0.5 && (newMap(posY, posX + 2)) == 0.5
        % Do nothing but go to the end of the function

    else
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
            if newMap(newY, newX) ~= 0.5
                % If the grid after the next is NOT occupied (i.e color white/black),
                newMap(mewY, mewX) = 0.5;
                
                % BETWEEN THE /* CODE */ WAS FOUND ONLINE AND NOT MY OWN!
                % (its only used to display the a   lgorithm after every move, and only has visual impact);
                %/*
                if showMapLoad == true
                    
                    % Find existing figure or create a new one
                    fig = findobj('Type', 'Figure', 'Name', 'Map Display');
                    if isempty(fig)
                        fig = figure('Name', 'Map Display', 'Units', 'normalized', 'OuterPosition', [0 0 0.25 1]); % Fullscreen
                    else
                        figure(fig); % Bring figure to front
                        clf(fig); % Clear figure
                    end
                    
                    % Display updated map
                    ax = axes(fig);
                    imagesc(ax, newMap);
                    axis equal;
                    axis tight;
                    colormap(gray);
                    drawnow;
                end
                %*/

                % Continue the travel through recursive Call 
                mapGenAlgo(newX, newY, newMap, showMapLoad);
            end
        end

    end
    % If can no longer find a path, retrace to a previous function recursion 
    % which had options to make a turn
    fprintf('Back tracking\n');
end


%% Main Function
% Initialize a map
function newMapArray = mapInit(mapArray, showMapLoad) 
    [MAPROW, MAPCOL] = size(mapArray);
    % outterWidth represent the size of the surrounding maze. (1
    outterWidth = 3; % MUST BE ODD NUMBER! AND GREATER THAN 1;

    % Mark outside of map as visited, and border it so our algo doesnt go
    % out of bounds.

    for i = 1:length(mapArray)
        for j = 1:length(mapArray)
            % If outside the border, make it already discovered
            if (i < outterWidth || i > MAPROW - outterWidth + 1) || (j < outterWidth || j > MAPCOL - outterWidth + 1)
                mapArray(i, j) = 0.5;
            % If is in range of border, make wall 
            elseif (i == outterWidth || i == MAPROW - outterWidth + 1) || (j == outterWidth || j == MAPCOL - outterWidth + 1)
                mapArray(i, j) = 0;
            % Make all odd part of the map wall, even part a path
            elseif mod(i, 2) == 0 || mod(j, 2) == 0
                mapArray(i, j) = 1;
            end
        end
    end
    
    % Random math to determine the minimum/maximum starting point
    
    min = floor(MAPROW/2) - floor(MAPROW/4);
    max = ceil(MAPROW/2) + ceil(MAPROW/4);
    fprintf('min: %d, max; %d\n', min, max);

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
    

    % Start the recursive algorithm
    newMapArray = mapGenAlgo(mapInitX, mapInitY, mapArray, showMapLoad);

    fprintf('Completed map Generation\n');

    % Turn all unvisited path to walls, and all visited path to paths
    for i = 1:MAPROW
        for j = 1:MAPCOL
            if newMapArray(i, j) == 1
                newMapArray(i, j) = 0;
            elseif newMapArray(i, j) == 0.5
                newMapArray(i, j) = 1;
            end
        end
    end

end

%% Main %%

% Map size (Constant)
MAPROW = 51; % MUST BE ODD NUMBER!
MAPCOL = 51; % MUST BE ODD NUMBER! LAST DIGIT MUST BE 1
mapArrayTemplate = zeros(MAPROW, MAPCOL);

newMapArray = mapInit(mapArrayTemplate, true);

% Display Final Result
figure;
imshow(newMapArray);

% Save final image
imwrite(newMapArray, 'backtracking_Maze.jpeg');





