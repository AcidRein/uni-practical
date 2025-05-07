clear
clc
%% Take two numbers x and y as its parameters and returns two numbers: [small and big]

function [small, big] = compareNumss(x, y)
    if (x > y)
        small = y;
        big = x;
    else
        small = x;
        big = y;
    end
end
[a1, a2] = compareNumss(3, 4);
fprintf('[%d, %d]', a1, a2);
