function xtilde = periodic(x, P)
xtilde = x' * ones(1, P); %P columns or period of x
xtilde = (xtilde(:))';

