%% Shop stuff to spice up gameplay
%{ 
Shop Ideas

% Unlock Trails 
% Wall hacks
% Auto complete levels

% SCRATCHED
- Auto maze solver by re-using recursive backtrack algo
- cheat code detection (up up down down left right left right b a) 
- Change Levels at will 
- Cheat Code unlocked to break the game
%}

function [] = shopFunc()
    global plrTrail plrGhost autoComplete currentLevel;

    % Check if the 'Shop' figure already exists
    existingFig = findall(0, 'Type', 'figure', 'Name', 'Shop');
    
    autoComplete = false; % Autocomplete level
    function [] = shopFeature(shopItem, src)
        switch shopItem
            case 1
                if currentLevel >= 3
                    plrTrail = src.Value;
                else
                    fprintf('You need to beat %d more levels!\n', 3 - currentLevel)
                end
                cbx1.Value = plrTrail;

            case 2
                if currentLevel >= 6
                    plrGhost = src.Value;
                else
                    fprintf('You need to beat %d more levels!\n', 6 - currentLevel)
                end
                cbx2.Value = plrGhost;

            case 3
                if currentLevel >= 10
                    autoComplete = true;
                else
                    fprintf('You need to beat %d more levels!\n', 10 - currentLevel)
                end
        end
    end
    if isempty(existingFig)
        % Create and resize the figure
        fig = uifigure('Name', 'Shop');
        fig.Position = [100, 100, 500, 300]; % Adjust figure for better text display

        % Add a label for informational text
        label = uilabel(fig, ...
            'Text', 'Welcome to the Shop!', ...
            'Position', [20, 220, 300, 22], ... % Adjust position and width
            'FontSize', 14);

        % Create three checkboxes
        cbx1 = uicheckbox(fig, ...
            'Text', '[Level 3] Player Trail', ...
            'Position', [20, 180, 200, 22], 'Value', plrTrail); % 
        cbx2 = uicheckbox(fig, ...
            'Text', '[Level 6] Ghost Mode', ...
            'Position', [20, 140, 200, 22], 'Value', plrGhost); % 
        
        % Add a label next to the button
        buttonLabel = uilabel(fig, ...
            'Text', '[Level 10] Beat current Level', ...
            'Position', [20, 100, 200, 22], ... % Position next to the button
            'FontSize', 12);

        % Create a button
        button1 = uibutton(fig, ...
            'Text', 'Complete Now!', ...
            'Position', [250, 100, 100, 22]); % Adjust width
        button2 = uibutton(fig, ...
            'Text', 'Toggle BGM', ...
            'Position', [20, 60, 100, 22]); % Adjust width

        % Set callback functions
        cbx1.ValueChangedFcn = @(src, event) shopFeature(1, src);
        cbx2.ValueChangedFcn = @(src, event) shopFeature(2, src);
        button1.ButtonPushedFcn = @(src, event) shopFeature(3, true);
        button2.ButtonPushedFcn = @(src, event) soundPlayer('bgmToggle');
    else
        disp('Cannot Open Shop: Shop already opened');
    end

    
end

