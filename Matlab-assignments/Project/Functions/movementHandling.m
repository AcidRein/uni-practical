function [newMaze, plrX, plrY] = movementHandling(movement, mazeArray, oldPlrX, oldPlrY, MAZEPATHCOLOR)
    global plrTrail plrGhost;
    % Check type of movement
    % W = 119
    % A = 97
    % S = 115
    % D = 100
    % Left Arrow = 28
    % Right Arrow = 29
    % Up Arrow= 30
    % Down Arrow = 31
    % B = 98
    % X = 120 ( Close Game )

    %fprintf('Received %d, %d, %d\n', oldPlrX, oldPlrY, movement);
    plrX = oldPlrX;
    plrY = oldPlrY;
    
    % Clear player Position in the maze
    newMaze = mazeArray;
    if plrTrail
        newMaze(oldPlrY, oldPlrX) = 0.6;
    else
        newMaze(oldPlrY, oldPlrX) = MAZEPATHCOLOR;
    end
    
    switch movement
        case {28, 97} % Turn Left
            % Check if valid movement
            if (mazeArray(oldPlrY, oldPlrX - 1) ~= 0 || plrGhost) % is not a wall, or ghost mode
                plrX = oldPlrX - 1;
            end
        case {29, 100} % Turn Right 
            if (mazeArray(oldPlrY, oldPlrX + 1) ~= 0  || plrGhost)
                plrX = oldPlrX + 1;
            end

        case {30, 119} % Turn Up
            if (mazeArray(oldPlrY - 1, oldPlrX) ~= 0 || plrGhost)
                plrY = oldPlrY - 1;
            end

        case {31, 115} % Turn Down
            if (mazeArray(oldPlrY + 1, oldPlrX) ~= 0 || plrGhost)
                plrY = oldPlrY + 1;
            end        
    end

    if ~((oldPlrX == plrX) && (oldPlrY == plrY)) % Check if the position is the same
        % Play a movement sound (it makes the game feel too slow);
        %soundPlayer('move');
    end

    %% Small chance to provide 'hints' while moving
    hintList = ["Hint: Don't forget, pressing 'Q' accesses the shop!", "Hint: Did you know, the human brain cannot feel pain", "Cool Tip: A good grade would be nice :)", ...
        "Hint: If input isn't working, try focusing on the Maze figure", "Hint: Pressing 'X' will safely close the game and stop any music"];
    succChance = randi([1, 500]);
    if succChance == 1
        fprintf("\n%s\n", hintList(randi([1, length(hintList)])))
    end
    
    
end
