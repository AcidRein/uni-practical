clear
clc
%% Movement Handling #1 (evidence of learning)
% Takes an input from the keypad ['up', 'down', 'left', 'right'] and makes
% a block move.

%% Utility Functions
% Source:
% https://au.mathworks.com/matlabcentral/answers/335596-how-to-make-matlab-detect-keyboard-stroke
function [newPlrX, newPlrY] = movePlayer(movement, gameSize, oldPlrX, oldPlrY)
    [gameHeight, gameWidth] = size(gameSize);
    % Check type of movement
    % 28 leftarrow
    % 29 rightarrow
    % 30 uparrow
    % 31 downarrow

    % Init
    newPlrX = oldPlrX;
    newPlrY = oldPlrY;
    if movement == 28
        % Check if valid movement
        if (oldPlrX - 1) > 0
            newPlrX = oldPlrX - 1;
        end
    % Repeat above for all input
    elseif movement == 29
        if (oldPlrX + 1) <= gameWidth
            newPlrX = oldPlrX + 1;
        end

    elseif movement == 30
        % Check if valid movement
        if (oldPlrY - 1) > 0
            newPlrY = oldPlrY - 1;
        end
    % Repeat above for all input
    elseif movement == 31
        if (oldPlrY + 1) <= gameHeight
            newPlrY = oldPlrY + 1;
        end
    end
    
    %fprintf('New Pos: (%d, %d)\n', oldPlrX, oldPlrY);
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
while 1
    % Clear Player Location
    gameSize(playerY, playerX) = 0.9; % Player trail color

    % Wait for input
    keyPress = waitforbuttonpress;
    if ~(keyPress == 1) % keyPress = keyboard Input when 1, or mouse Input when 0
        continue
    end
    keyValue = double(get(gcf,'CurrentCharacter'));
    fprintf('%d\n', keyValue);

    % Update Player Movement
    [playerX, playerY] = movePlayer(keyValue, gameSize, playerX, playerY);
    
    % Update player position
    gameSize(playerY, playerX) = 0.5;
    
    % Keep full screen
    imshow(gameSize, 'InitialMagnification', 'fit');

    % Check if Player has Won
    fprintf('plr(%d, %d), win(%d, %d)\n', playerX, playerY, goalX, goalY);
    if (playerX == goalX) && (playerY == goalY)
        fprintf('Player Won!\n');
        break
    end
end