% Factorial print from 1 to 100

n = 100; 
global memo;
memo = zeros(n);

function [res] = fact(n)
    global memo;  
    for i = 1:n
        if memo(i) == 0
            if i == 1
                memo(i) = 1;
            else
                memo(i) = memo(i-1) * i;
            end
            fprintf("Factorial of %d is %d\n", i, memo(i));
        end
    end
    res = memo(i);
    return;
end

A = fact(n);