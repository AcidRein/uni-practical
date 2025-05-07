clear
clc
%% Find Leap year

years = [2015:2041];
leapYears = zeros(1, sum(mod(years, 4) == 0)); % Preallocate Vector memory

leapIndex = 1; % Keep track of leapYear index

for i = 1: length(years) % Loop through all items in 'years' Vector
    if mod(years(i), 4) == 0 % Check if divisibe by 4 (Basically checking leap year)
        leapYears(leapIndex) = years(i); % If leap year, add it to the leapYears array
        leapIndex = leapIndex + 1; % Increment leapYear's index
    end
end

% Weird printing but it works ig
for i = 1:length(leapYears) - 1
    fprintf('%d ', leapYears(i));
end
fprintf('%d', leapYears(length(leapYears)));
