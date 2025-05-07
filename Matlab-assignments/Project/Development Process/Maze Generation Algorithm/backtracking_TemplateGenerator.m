clear
clc
clearvars fig
%% recursive backtracking Map generation #2 preperation (evidence of learning)
%{
% RULES: 
% Select a random cell to start.
% Choose a random adjacent cell. Only create a passage if that cell has not been visited yet.
% Repeat the process until there are no more adjacent cells to choose from.
% Start backtracking until you can choose a cell again.
% The algorithm is done when you return to the starting cell.
%}

%% Main Function
% Initialize a template for the backtracking algorithmn to walk through
function [newMapTemplate] = mapTemplate(MAPROW, MAPCOL) 
    newMapTemplate = zeros(MAPROW, MAPCOL);
    % outterWidth represent the size of the surrounding maze. (1
    outterWidth = 3;

    % Mark outside of map as visited, and border it so our algo doesnt go
    % out of bounds.

    for i = 1:MAPROW
        for j = 1:MAPCOL
            % If outside the border, make it already discovered
            if (i < outterWidth || i > MAPROW - outterWidth + 1) || (j < outterWidth || j > MAPCOL - outterWidth + 1)
                newMapTemplate(i, j) = 0.5;
            % If is in range of border, make wall 
            elseif (i == outterWidth || i == MAPROW - outterWidth + 1) || (j == outterWidth || j == MAPCOL - outterWidth + 1)
                newMapTemplate(i, j) = 0;
            % Make all odd part of the map wall, even part a path
            elseif mod(i, 2) == 0 || mod(j, 2) == 0
                newMapTemplate(i, j) = 1;
            end
        end
    end
end

%% Main %%
% Map size
newMapArray = mapTemplate(51, 51);

% Display Final Result
figure;
imshow(newMapArray);

% Save
imwrite(newMapArray, 'backtracking_Template.jpeg');







