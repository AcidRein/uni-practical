clear
clc
%% Append B to the result of A in reverse order.

A = [1:10];
B = [11:21];

sizeA = length(A); % predefine the length of A
sizeB = length(B); % predefine the length of B

indCounter = 1; % Initialize counter to add elements after 'A'
for i = sizeB:-1:1 % Start indexing from the end of 'B', decreasing by step of -1 until 1.
    A(sizeA + (indCounter)) = B(i); % Change vector in A
    indCounter = indCounter + 1; % Increment the index counter by 1, to append the next vector
end

% Weird printing but it works ig
for i = 1:length(A) - 1
    fprintf('%d ', A(i));
end
fprintf('%d', A(length(A)));