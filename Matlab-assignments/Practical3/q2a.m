clear
clc
%% Append the result of B to the end of A.

A = [1:10];
B = [11:21];

sizeA = length(A); % predefine the length of A
sizeB = length(B); % predefine the length of B

for i = (sizeA + 1):sizeA + sizeB % Start indexing from the very end (+ 1) of vector As
    A(i) = B(i - sizeA); % Change the end + 1 of 'A' vector to the start of B vector
end

% Weird printing but it works ig
for i = 1:length(A) - 1
    fprintf('%d ', A(i));
end
fprintf('%d', A(length(A)));