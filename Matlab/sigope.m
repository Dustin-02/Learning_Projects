% Khai bao ham xung don vi
function [x, n] = sigope(n01, n02, n1, n2)
n = [n1:n2];  
x1 = [n == n01];
x2 = [n == n02];
x = 2*x1 - x2;
end
