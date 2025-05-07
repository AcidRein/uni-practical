clear
clc
%% random Walk Map generation #1

% How it works:
% Starts from the middle, walking around randomly to generate a map
% Only constraints are the border of the game

% Map size
mapRow = 50;
mapCol = 50;
mapSize = zeros(mapRow, mapCol);

% Start in the middle
startX = ceil(mapCol/2);
startY = ceil(mapRow/2);

% Number of random walk bots
walkBots = randi([2, 3]);

% Number of walks available
minWalk = (mapCol + mapRow)/2;
maxWalk = mapCol + mapRow;
numWalks = randi([minWalk, maxWalk]);

%% Utility Function
% Returns an array of movement
function canMove = checkBounds(mapSize, posX, posY)
    canMove = [];
    [mapRow, mapCol] = size(mapSize);
    % Check movement availability
    if (posX - 1) > 1 % If can turn left
        canMove(length(canMove) + 1) = 1;
    end
    if (posX - 1) < mapCol % If can turn right
        canMove(length(canMove) + 1) = 2;
    end
    if (posY - 1) > 1 % If can go up
        canMove(length(canMove) + 1) = 3;
    end
    if (posX + 1) < mapRow % If can go down
        canMove(length(canMove) + 1) = 4;
    end
end

% Moves bot in a random direction (Recursive function)
function newMap = botWalk(mapSize, posX, posY, walksLeft)
    % If the bot can no longer walk, finish
    if walksLeft == 0
        mapSize(posY, posX) = 1;
        newMap = mapSize;
        fprintf('No more WALKS\n')
        return
    end
    
    % Check which turn the bot can make
    canMove = checkBounds(mapSize, posX, posY);
    if length(canMove) < 1
        % No available movements
        mapSize(posY, posX) = 1;
        newMap = mapSize;
        fprintf('No available movement\n')
        return
    end

    % Randomly turn Left (1), Right (2), Up (3), Down (4)
    % Based on the movement available
    randomChoice = randi([1, length(canMove)]);
    fprintf('R%d: %d\n', walksLeft, randomChoice);
    turnSignal = canMove(randomChoice);
    
    if turnSignal == 1 % Left turn
        posX = posX - 1;
    elseif turnSignal == 2 % Right turn
        posX = posX + 1;
    elseif turnSignal == 3 % Up turn
        posY = posY - 1;
    elseif turnSignal == 4 % Down turn
        posY = posY + 1;
    end
    

    mapSize(posY, posX) = 1;
    newMap = mapSize;
    walksLeft = walksLeft - 1;
    imshow(newMap);
    newMap = botWalk(newMap, posX, posY, walksLeft);
end

newMap = mapSize;
for i = 1:walkBots
    newMap = botWalk(newMap, startX, startY, numWalks);
end

% display result
imshow(newMap);
% Save result
imwrite(newMap, 'botWalk.jpeg');