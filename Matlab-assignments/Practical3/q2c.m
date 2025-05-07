clear
clc
%% Interleave the vectors A and B.

% assume that A and B are the same length. 
A = [1:10];
B = [11:20];
C = zeros(1, length(A)); % Preallocate C vector to save memory on for-loop

indA = 1; % Keep track of the element in VecA
indB = 1; % Keep track of the element in VecB
for i = 1:length(A) + length(B) % Double for-loop quantity as C vector length will be lengthA + lengthB
    % We can interleave each element of A and B by using ODD and EVEN
    % numbers; ODD index means A(i) is appended, EVEN index means B(i) is appended.
    if mod(i, 2) == 0
        C(i) = B(indB);
        indB = indB + 1;
    else
        C(i) = A(indA);
        indA = indA + 1;
    end
end


% Weird printing but it works ig
for i = 1:length(C) - 1
    fprintf('%d ', C(i));
end
fprintf('%d', C(length(C)));
