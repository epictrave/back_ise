from sympy import Symbol, solve, exp

m = Symbol('m')
e = Symbol('e')

eq1 = exp((1.6 - e) / m) - 1
eq2 = exp((2.4 - e) / m) - 100


solve([eq1, eq2], m, e)

print("")
