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

function [plrTrail, plrGhost, autoComplete] = shopFunc(currLevel, plrTrail, plrGhost)
    autoComplete = false; % Input for 'Auto complete level' feature 

    

    fprintf(['\n== Welcome to Shop. Play more to unlock more! ==\n', ...
        '[1] Unlock player Trail [Level 3 Required]\n', ...
        '[2] Unlock ability to phase through walls! (Not liable for leaving array index issues) [Level 6 Required]\n', ...
        '[3] Automatically beat the level [Level 10 Required]\n', ...
        'You are on level [%d]. Enter a number to select:'], currLevel);
    userInp = input('', 's');

    % Verify Input
    switch userInp
        case "1"
            if currLevel >= 3 % VERIFY LEVEL
                plrTrail = ~(plrTrail);
                fprintf('Player trail: %d\n', plrTrail);
            else
                fprintf('Too Low Level!\n');
            end
        case "2"
            if currLevel >= 6 % VERIFY LEVEL
                plrGhost = ~(plrGhost);
                fprintf('Player Ghost mode: %d\n', plrGhost);
            else
                fprintf('Too Low Level!\n');
            end
        case "3"
            if currLevel >= 10 % VERIFY LEVEL
                autoComplete = true;
            else
                fprintf('Too Low Level!\n');
            end
            %{
        case "4" % SCRATCHED!
            
            
            if currLevel >= 15 
                cheatsAvailable = true;
                fpritnf('\nCheat code says: Up Up Down Down Left Right Left Right B A\n');
            else
                fprintf('Too Low Level!\n');
            end
            %}
        otherwise
            fprintf('Not a valid choice.\n')
            return
    end

    
end

