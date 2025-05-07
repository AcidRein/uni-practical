clear
clc
%% Retrieve 5 inputs from the user, absolute and sum it all up.

sum = 0;
for i = 1:5
    % asks the user for a number, given the for-loop's index.
    fprintf('Please enter a Number (%d): ', i);
    userInput = input("", 's');
    % While the user has not input a number, re-prompt input
    while isnan(str2double(userInput))
        fprintf('Invalid number! Try again\n')
        fprintf('Please enter a Number (%d): ', i);
        userInput = input("", 's');
    end
    % Turn the user's input into a number, absolute it, then add to sum
    sum = sum + abs(str2double(userInput));
end

%print the final result
fprintf('Absolute Sum of all five numbers equal: %.1f\n', sum);