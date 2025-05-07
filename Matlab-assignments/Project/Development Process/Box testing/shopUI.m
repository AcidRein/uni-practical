clear
clc
%% The use of all other msg boxes combined to make a shop!

% Function to open/reopen the shop
function toggleShop()
    % Check if the 'Shop' figure already exists
    existingFig = findall(0, 'Type', 'figure', 'Name', 'Shop');

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
            'Position', [20, 180, 200, 22]); % Adjust width
        cbx2 = uicheckbox(fig, ...
            'Text', '[Level 6] Ghost Mode', ...
            'Position', [20, 140, 200, 22]); % Adjust width
        
        % Add a label next to the button
        buttonLabel = uilabel(fig, ...
            'Text', 'Beat current Level', ...
            'Position', [20, 100, 100, 22], ... % Position next to the button
            'FontSize', 12);

        % Create a button
        button1 = uibutton(fig, ...
            'Text', '[Level 10]', ...
            'Position', [150, 100, 100, 22]); % Adjust width
        button2 = uibutton(fig, ...
            'Text', '[Toggle Shop]', ...
            'Position', [20, 60, 100, 22]);

        % Set callback functions
        cbx1.ValueChangedFcn = @(src, event) disp(['Checkbox 1 Value: ', num2str(src.Value)]);
        cbx2.ValueChangedFcn = @(src, event) disp(['Checkbox 2 Value: ', num2str(src.Value)]);
        button1.ButtonPushedFcn = @(src, event) disp(['Button 1 clicked']);
        button2.ButtonPushedFcn = @(src, event) toggleShop();
    else
        fprintf('Closing Figure\n');
        % Provide confirmation
        f = questdlg('Are you sure you want to quit?', ...
            'Quit Shop?', ...
            'Yes', 'Nah', 'Nah');
        
        if strcmp(f, 'Yes')
            close(existingFig);
        else
            fprintf('Cancelled\n')
        end
    end
end

% Call the function to open/reopen the checkbox figure
toggleShop();

