clear
clc
%% Display the cubed result of A to B.

A = [-10:0.5:10];
B = zeros(1, length(A)); % preallocate B vector

for i = 1:length(A)
    B(i) = round(A(i) ^ 3, 4); % Cube B
end

% Weird printing but it works ig
for i = 1:length(B) - 1
    fprintf('%.4f ', B(i));
end
fprintf('%.4f', B(length(B)));
