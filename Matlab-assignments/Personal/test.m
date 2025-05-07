clear
clc
%% Useful Functions
%{
rand() % returns a random number from 0 - 1 (mainly for floats)
ranfromNumber = 4; % choose a random number in range of 4-11
rantoNumber = 11; % read above
ranVector = 1; % how much vectors you want. 1 = [x], 2 = [a, b] (on the bottom) [c,d]. etc,
vectorTable = 1; % choose what row/column to choose number from
randi([ranfromNumber, rantoNumber], ranVector, vectorTable) % returns random number
pause(1.0) % pauses the script for 1 second
size(myVector, x) % returns no. of rows and/or columns. x = 1 is row, x = 2 is column.
csvread('your.csv', x, y) % read csv files. x = no. of rows to skip, y = no. columns to skip
%}

%% Operators
%{

myPower = x ^ n (probably better than using function 'power')
myModulo = mod(a, 2) % the modulo (remainder) of a / 2
myAbsolute = abs(-b); % absolute of a value
%}

%% If statement
MYCONSTANT1 = 69;

if MYCONSTANT1 > 69
    %fprinf("we are the champions\n");
elseif MYCONSTANT1 < 69
    %fprintf('less than my const 1\n');
else
    %fprinft('is the funny number\n');
end

%% Switch
dayNumber = 3; %input("Input a day: ");
switch dayNumber
    case 1
        %disp("Monday");
    case 2
        %disp("Tuesday");
    case 3
        %disp("Wednesday");
    case 4
        %disp("Thurday");
    case 5
        %disp("Friday");
    case 6
        %disp("Saturnday");
    case 7
        %disp("Sunday");
    otherwise
        %disp("Not in any case")
end

%% For-loops
startValue = 1;
endValue = 10;
stepValue = 2; % (we can use -x to start counting from endValue to startValue)

% Basic for loop
for i= startValue : endValue % from 1 - 10
    %disp(i);
end

% For loop with steps
for a = startValue:stepValue:endValue % from 1-10, counting by 2
    %disp(a);
end

%% Vectors

myVec1 = [1:10];
checkMe = randi([1,20]);

if ismember(checkMe, myVec1)
    fprintf('%d FOUND!\n', checkMe)
else
    fprintf('%d NOT FOUND!\n', checkMe)
end




