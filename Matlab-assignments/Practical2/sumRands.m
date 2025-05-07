clear
clc
%% ( Method 1 ) Generate 5 random numbers and sum it all up [Using randi()]
FINDAVERAGE = false; % Set me to true (and Run) to find the average sum
Simulation = 1;

% Fundamental function to calculate sum of 5 random integers between 1-10
function sum1 = SimulateSum()
    sum1 = 0;
    for i = 1:5
        % Create random integer from (1 - 10) inclusive using randi Vectors
        randomInteger = (randi([1, 10], 1));
        fprintf('The integer: %d was chosen!\n', randomInteger);
    
        % Add to sum
        sum1 = sum1 + randomInteger;
    end
end

% The total sum of all simulated sums (For finding Average)
totalSum = 0;

% If the user wants to run a simulation (For finding Average)
if FINDAVERAGE == true
    Simulation = input("Please input Simulation instances (Integers): ");
end

% Finds the sum of 5 random integers and add it to the total sum
for i = 1:Simulation
    totalSum = totalSum + SimulateSum();
end

% Finding the average
if FINDAVERAGE == true
    fprintf('With %d Simulations ran, the average sum is = %.2f\n', Simulation, (totalSum) / Simulation);
else
    fprintf('Sum of 5 Random Integers = %d\n', totalSum)
end

%% ( Method 2 ) of finding the sum of 5 random numbers [Without randi()]
%{
sum2 = 0;
for i = 1:5
    % Chooses a random number between 0 - 1
    % Multiply by 10 to move the decimal up one place
    % use 'ceil' function to only get integered numbers ranging from 1 - 10
    randomInteger = ceil((rand() * 10));
    fprintf('The integer: %0.1f was chosen!\n', randomInteger);
    sum2 = sum2 + randomInteger;
end

% Display the total sum
fprintf('%d\n', sum2);
%}



