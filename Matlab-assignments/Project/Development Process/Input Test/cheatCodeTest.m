clear
clc
%% Cheat code testing with key input
% Up Up Down Down Left Right Left Right B A

% W = 119
% A = 97
% S = 115
% D = 100
% Left Arrow = 28
% Right Arrow = 29
% Up Arrow= 30
% Down Arrow = 31
% B = 98
% X = 120

success = false;
answer = [30, 30, 31, 31, 28, 29, 28, 29, 98, 97];
tempLog = []; 

while ~(success)
    % Wait for input
    keyPress = waitforbuttonpress;
    keyValue = double(get(gcf, 'CurrentCharacter'));
    
    % Ignore invalid inputs (empty or non-scalar values, from mouse clicks) 
    if isempty(keyValue) || ~isscalar(keyValue)
        continue; % Skip this iteration of the loop
    end
    
    tempLog = [tempLog, keyValue];
    for i = 1:length(tempLog)
        if ~(tempLog(i) == answer(i))
            tempLog = [];
            
            % If the user were 2 character off
            if i > (length(answer) - 2)
                fprintf('SO CLOSE!\n');
            end
            break
        end

        if i == length(answer)
            success = true;
        end
    end

    disp(string(mat2str(tempLog)));
end

fprintf('SUCCESS!\n')