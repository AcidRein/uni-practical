clear
clc
%% BMI calculator56

% User Input
userWeight= input("Input your Weight (KG): ", "s");
userHeight = input("Input your Height (Metres): ", "s");

% Verify user input
% Checks if the attempt to turn string to number returns 'NaN'
if isnan(str2double(userWeight)) || isnan(str2double(userHeight))
    fprintf('Please input numbers only\n');
    return % end code given error
end
% After successfully verifying they are numbers, make them a num type
userWeight = str2double(userWeight);
userHeight = str2double(userHeight);

% Calculate BMI
if (userWeight < 0) || (userHeight < 0) % Negative values error
   fprintf('You can not have negative values\n')
   return % end code given error
else
   userBMI = userWeight/(userHeight ^ 2);
end

% Displaying information to User
fprintf('Your BMI is: %.2f\n', userBMI);

% More information on BMI
% Source: https://www.betterhealth.vic.gov.au/tools/body-mass-index-calculator-for-adult

if userBMI < 0
   return
elseif userBMI < 18.5
   fprintf('You are underweight and possibly malnourished.\n')
elseif userBMI >= 18.5 && userBMI < 25
   fprintf('You have a healthy weight range for young and middle-aged adults.\n')
elseif userBMI >= 25 && userBMI < 30
   fprintf('You are overWeight\n')
elseif userBMI >= 30
   fprintf("You are Obese\n")
else
   fprintf("Invalid BMI\n")
end

