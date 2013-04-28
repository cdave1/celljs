f = function fac2(n) {
    if (n <= 1) return 1; 
    return n * fac2(n-1);
};
//f(5);
doit(f(5), "a");