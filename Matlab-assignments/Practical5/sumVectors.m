clear
clc
%% Take two vectors v1 and v2 as parameters and returns one value that is the sum of both of these vectors.

function [sum] = sumVectorss(v1, v2)
    sum = 0;
    v3 = [v1 v2];
    for i = 1:length(v3)
        sum = sum + v3(i);
    end
end

vec1 = [1, 2, 3];
vec2 = [3, 2, 1];
disp(sumVectorss(vec1, vec2));