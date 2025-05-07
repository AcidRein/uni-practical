clear
clc
%% Movement Handling #1 (evidence of learning)
% Takes an input from the keypad ['up', 'down', 'left', 'right'] and makes
% a block move.

%% Utility Functions
% Source:
% https://au.mathworks.com/matlabcentral/answers/335596-how-to-make-matlab-detect-keyboard-stroke
function newData = movePlayer(movement, gameSize, oldPlrX, oldPlrY)
    [gameHeight, gameWidth] = size(gameSize);
    % Check type of movement
    % 28 leftarrow
    % 29 rightarrow
    % 30 uparrow
    % 31 downarrow
    if movement == 28
        oldPlrX = oldPlrX - 1;
    elseif movement == 29
        oldPlrX = oldPlrX + 1;
    elseif movement == 30
        oldPlrY = oldPlrY - 1;
    elseif movement == 31
        oldPlrY = oldPlrY + 1;
    end
    
    %fprintf('New Pos: (%d, %d)\n', oldPlrX, oldPlrY);
    % Send new data 
    newData.oldPlrX = oldPlrX;
    newData.oldPlrY = oldPlrY;
end

%% Initialization
% Game Initialization
gameWidth = 50;
gameHeight = 50;
gameSize = ones(gameWidth, gameHeight) * 0.9;
% gameShow = (gameSize * 4);

% Player Initialization
playerX = randi([1,10]); % Where player spawns on X-axis (column) 
playerY = randi([1,50]); % Where player spawns on Y-axis (row)
roundVictory = false; % If the player has/hasn't beaten the current map
roundsWon = 0; % Number of rounds the player has won

% Randomly spawn Winning area (more towards the right side of the map)
goalX = randi([1, 50]);
goalY = randi([30, 50]);
gameSize(goalY, goalX) = 0.2;

% Create and show map
gameSize(playerY, playerX) = 0.5;
figure;
imshow(gameSize);

% Keyboard input source: https://au.mathworks.com/matlabcentral/answers/335596-how-to-make-matlab-detect-keyboard-stroke
while ~(roundVictory)
    % Clear Player Location
    gameSize(playerY, playerX) = 0.9; % Player trail color

    % Wait for input
    keyPress = waitforbuttonpress;
    keyValue = double(get(gcf,'CurrentCharacter'));
    fprintf('%d\n', keyValue);

    % Update Player Movement
    plrUpdate = movePlayer(keyValue, gameSize, playerX, playerY);
    playerX = plrUpdate.oldPlrX;
    playerY = plrUpdate.oldPlrY;
    
    % Update player position
    gameSize(playerY, playerX) = 0.5;
    
    % Keep full screen
    imshow(gameSize, 'InitialMagnification', 'fit');

    % Check if Player has Won
    fprintf('plr(%d, %d), win(%d, %d)\n', playerX, playerY, goalX, goalY);
    if (playerX == goalX) && (playerY == goalY)
        fprintf('Player Won!\n');
        roundVictory = true;
    end
end