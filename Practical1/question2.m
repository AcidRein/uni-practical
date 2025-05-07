clear
clc
%% City water usage
WATER_PER_PERSON = 274; % In Litres
% Source
% https://www.tankshop.com.au/articles/how-to-calculate-water-usage-in-your-home/

% Input
totalPopulation = input("What is the population?: ");

% Functionality
waterUsagePerDay = totalPopulation * (WATER_PER_PERSON / 1000);

% Print
fprintf('The average water usage per day with a population of %d is %.2f KLitres\n', totalPopulation, waterUsagePerDay);

