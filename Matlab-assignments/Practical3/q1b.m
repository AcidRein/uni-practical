clear
clc
%% Display the 2^A to vector C.

A = [-10:0.5:10];
B = zeros(1, length(A)); % preallocate B vector
C = zeros(1, length(A)); % preallocate C vector

for i = 1:length(A)
    B(i) = round(A(i) ^ 3, 4); % Cube B
    C(i) = round(pow2(A(i)),4); % Squared C
end

% Weird printing but it works ig
for i = 1:length(C) - 1
    fprintf('%.4f ', C(i));
end
fprintf('%.4f', C(length(C)));
fprintf('\n')
