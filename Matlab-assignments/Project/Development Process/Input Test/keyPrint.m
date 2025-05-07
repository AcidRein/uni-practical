clear
clc
%% Detects input values

% Source:
% https://au.mathworks.com/matlabcentral/answers/335596-how-to-make-matlab-detect-keyboard-stroke
% Up arrow = 30
while 1
    % Wait for input
    keyPress = waitforbuttonpress;
    keyValue = double(get(gcf,'CurrentCharacter'));
    fprintf('You pressed key: %d\n', keyValue);
    if keyValue == 30 % If up arrow key is detected
        fprintf('Ended\n')
        break
    end
end