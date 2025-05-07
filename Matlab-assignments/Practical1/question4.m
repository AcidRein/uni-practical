clear
clc
%% Transport Cost Population

% (CONSTANTS) Assuming the people who own a car pays the same amount (weekly)
% Source: https://www.savings.com.au/car-loans/ongoing-car-costs
% Dividing by 7 to get the daily cost instead of weekly, rounded
FUEL_COST = round((98.31 / 7), 2);
CAR_INSURANCE = round((31.67 / 7), 2);
CAR_LOAN_COSTS = round((155.96 / 7), 2);

% User Input
personPopulation = input('(NUMBER) What is the population of your city?: ');
percentageCarOwners = input('(NUMBER) Percentage of people who owns a car (x%): ');
carServices = input("(NUMBER) How much do you charge for Car Services? (daily): $");
carRegistration = input("(NUMBER) How much do you charge for Car Registration? (daily): $");
 
% Functionality
carOwners =     ceil(personPopulation * (percentageCarOwners/100));
fprintf('You have a Population of %d, with %d people owning a car (rounded up).\n', personPopulation, carOwners);

% Function for calculations
function totalDailyCost = calcTransportCost(vehicleDrivers, carServiceFees, carRegistrationFees, fuelCost, insuranceCost, loanCost)
    totalFees = carServiceFees + carRegistrationFees + fuelCost + insuranceCost + loanCost;
    totalDailyCost = (vehicleDrivers * totalFees);
end

% Print
totalDailyCost = calcTransportCost(carOwners, carServices, carRegistration, FUEL_COST, CAR_INSURANCE, CAR_LOAN_COSTS);
fprintf('With car owners paying the following fees:\nCar Service Fee: $%.2f\nCar Registration Fee: $%.2f\nFuel Cost: $%.2f\nCar Insurance Fee: $%.2f\nCar Loan Fee: %.2f\n', carServices, carRegistration, FUEL_COST, CAR_INSURANCE, CAR_LOAN_COSTS)
fprintf('The total cost of transport for all car owners is given by the amount: $%.2f\n', totalDailyCost);