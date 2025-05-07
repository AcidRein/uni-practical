clear
clc
%% Plot result of B and C.

A = [-10:0.5:10];
B = zeros(1, length(A)); % preallocate B vector
C = zeros(1, length(A)); % preallocate C vector

for i = 1:length(A)
    B(i) = round(A(i) ^ 3, 4); % Cube B
    C(i) = 2 ^ A(i); % Squared C
end

close all;  %close all figure windows
hold on; % display plots on the same window for now
plot(A, B);
plot(A, C);
hold off;  % turn off plotting on the same window. 