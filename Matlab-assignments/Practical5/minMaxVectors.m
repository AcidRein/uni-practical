clear
clc
%% Take two vectors v1 and v2 as its parameters and returns two values: min and max of the vectors
% Challenge, dont use min() or max() function

function [min, max] = minMaxVectorss(v1, v2)
    v3 = [v1 v2];
    min = inf;
    max = -inf;
    for i = 1:length(v3)
        if v3(i) > max
            max = v3(i);
        end
        if v3(i) < min
            min = v3(i);
        end
    end
end

vec1 = [2, 4, 6, 8, 10];
vec2 = [21, 19, 16, 13];

[minVal, maxVal] = minMaxVectorss(vec1, vec2);

fprintf('Minimum: %d\nMaximum: %d\n', minVal, maxVal);