clear
clc
%% Q9 
function [newArray] = makeLayered(n)
    totalSize = (2*n)-1;
    newArray = zeros(totalSize, totalSize);
    for layer = 1:totalSize
        for c = 1:totalSize
            disMidCol = abs(c - ceil(totalSize/2));
            disMidRow = abs(r - ceil(totalSize/2));
            if disMidCol > disMidRow
              res = 1 + disMid;
            else
            end
            newArray(layer, c) = res;
        end
    end
end

n = input('Enter int: ');
A = makeLayered(n);

for r = 1:n+2
    for c = 1:n+2
        fprintf("%d ", A(r, c));
    end
    fprintf("\n");
end