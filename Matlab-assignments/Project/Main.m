clear
clc
%% Main

%% Controls
% W = 119
% A = 97
% S = 115
% D = 100
% Left Arrow = 28
% Right Arrow = 29
% Up Arrow= 30
% Down Arrow = 31
% Q = 113 ( Shop )
% X = 120 ( Close Game )

% All Credit
% BGM1: https://www.chosic.com/download-audio/59619/
% BGM2: https://www.chosic.com/download-audio/59620/
% Beating a level sfx: https://pixabay.com/sound-effects/search/level/

%% Game
function [] = main()
    global plrTrail plrGhost currentLevel;
     msgfig = msgbox({'-- How to play --'; ...
        'You (white) must traverse the maze to reach the flag (grey)'; ...
        'Controls:'; ...
        'Move with WASD or ARROWS_KEY'; ...
        'Q to access the shop'; ...
        'X to quit SAFELY'; ...
        ''; ...
        'Note: If the game is not responding to key presses, click on the maze window to focus!'; ...
        '== Have Fun!! =='},'How to Play','modal');
    uiwait(msgfig)
    
    fprintf('Move with WASD or arrows Key\n"Q" for shop access\n"X" to safely close game\n');
    % Toggle game close
    forceQuit = false;

    % Initialize 
    % Fun shop stuff 
    plrTrail = false;
    plrGhost = false;

    currentLevel = 1; % Level counter
    soundPlayer('bgmPlay');  %Start bgm
    shopFunc(); % Open the Shop initially

    
    while ~(forceQuit)
        % Start a new Level
        [forceQuit] = newLevel();
        currentLevel = currentLevel + 1;
    end
    % Display goodbye message
    msgfig = msgbox({sprintf('You made it to level %d!', currentLevel - 1); ...
        '-- Thank you for playing! --'},'Finish','modal');
    uiwait(msgfig);
    fprintf('Successfully and safely quit the program! You made it to level [%d]\n', currentLevel - 1);


    % Close all figures and turn of all music
    close all force;
    clear all;
end

function [forceQuit] = newLevel()
    global autoComplete currentLevel;
    autoComplete = false; % default to false
    
    % Constants
    MAZEPATHCOLOR = 0.4;
    PLAYERCOLOR = 1;
    
    % Allowed keyboard inputs
    allowedControls = [119, 97, 115, 100, 28, 29, 30, 31, 98, 113, 120];

    % Initialize Toggle
    forceQuit = false;

    % Initialize player location and maze
    % Create maze
    [newMaze, initPlayerX, initPlayerY, flagX, flagY] = initializeNewMap(currentLevel, MAZEPATHCOLOR, PLAYERCOLOR);

    % Display maze initially
    imshow(newMaze, 'InitialMagnification', 'fit');
    % Rename new maze figure
    set(gcf, 'Name', sprintf('Current Level - %d', currentLevel), 'NumberTitle', 'off');
    % gcf = get figure in hand

    % Initialize player's location to match the one shown on the maze
    currPlrX = initPlayerX;
    currPlrY = initPlayerY;
    %fprintf('Map information: player spawn (%d, %d). Flag spawn (%d, %d)\n', initPlayerX, initPlayerY, flagX, flagY);
    
    % Loop for input until the game has been quit or finished
    while (~forceQuit)
        
        % Wait for input
        keyPress = waitforbuttonpress; % 1 When keyboard input, 0 when mouseClick input
        if keyPress ~= 1 % Disallow mouseClick inputs
            continue
        end

        keyValue = double(get(gcf, 'CurrentCharacter'));
        
        % Ignore invalid inputs (empty or non-scalar values, from mouse clicks) 
        if isempty(keyValue) || ~isscalar(keyValue) || ~(ismember(keyValue, allowedControls))
            continue; % Skip this iteration of the loop
        end
        
        switch keyValue
            case {113} % Open Shop (Q)
                shopFunc(); % Random shop for fun
        
            case {120} % Close game (X)
                % Check if player still wants to play
                userInp = questdlg(sprintf("Are you sure you would like to quit on level %d? ", currentLevel), ...
                    'Quit Game?', 'Yes', 'No', 'No');
                
                if strcmp(userInp, 'Yes')
                    forceQuit = true;
                    break 
                else
                    fprintf('Cancelled exit request\n');
                end
        end

        % Update Player Movement through key presses (WASD or arrow key)
        [newMaze, newPlrX, newPlrY] = movementHandling(keyValue, newMaze, currPlrX, currPlrY, MAZEPATHCOLOR);
        
    
        % Update player position
        currPlrX = newPlrX;
        currPlrY = newPlrY;
        newMaze(currPlrY, currPlrX) = PLAYERCOLOR;
        
        % Keep the game at full screen
        imshow(newMaze, 'InitialMagnification', 'fit');
    
        % Check if Player has Won
        if ((currPlrX == flagX) && (currPlrY == flagY)) || autoComplete
            autoComplete = false; % Disable current auto-Complete feature
            % Sound effect for winning
            soundPlayer('success');
            fprintf('Completed Level %d!\n', currentLevel);
            
            % Check if player still wants to play
            userCont = questdlg(sprintf('Would you like to continue to level %d?', currentLevel + 1), ...
                'Continue', 'Yes', 'No', 'No');
            forceQuit = strcmp(userCont, 'No'); % forceQuit if 'Yes'
            break
        end
    end
    
end

% Run
main();






