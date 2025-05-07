clear
clc
%% UserInput check if divisible by four

userInput = input('Enter a number: ', 's');

% Error Handling
if isnan(str2double(userInput))
    return
end
% Modify userInput
userInput = str2double(userInput);

% Check if divisible by 4
if (mod(userInput, 4) == 0)
    fprintf('Divisible by four');
end