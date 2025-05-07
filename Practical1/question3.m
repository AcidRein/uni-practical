clear
clc
%% City water usage with desalination
DAILY_DESALINATION_CAPACITY = 300000; % In KLitres

% Input
totalPopulation = input("What is the population?: ");
waterUsePerPerson = input("How much Litres of water is used person?: ");

% Functionality
waterUsagePerDay = totalPopulation * (waterUsePerPerson / 100);
desalinationCoverage = waterUsagePerDay/DAILY_DESALINATION_CAPACITY;

% Print
if desalinationCoverage <= 1
    fprintf('The Desalination Capacity can cover all %.2f%% of the daily water use\n', desalinationCoverage * 100);
else 
    fprintf("The daily water usage is %.2f%% Over the limit and the excess can't be covered\n", (desalinationCoverage - 1) * 100);
end

