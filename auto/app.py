import math

beta  = 0.035 
Qdc   = 0.02
A     = 1.5
Tp    = 0.01
T     = 12 * 36
N     = int(T / Tp)
hl    = [0]

hust  = (Qdc/beta)**2

hmin = 0
hmax = 10

Qdmin = 0
Qdmax = 0.05

umin = 0
umax = 10

kp = 2
Ti = 0.5
Td = 0.01

ul   = []
el   = []

def u(n, prod):
    prod = prod + el[n]

    var = kp * (el[n] + (Td * prod / Ti))

    if (var >= umin):
        if (var <= umax):
            ul.append(var)
        else:
            ul.append(umax)
    else:
        ul.append(umin)
    return prod

def e(n):
    var = hust - hl[n]
    el.append(var)

#  AAAAAA
def Qd(n):
    var = (Qdmax / umax) * ul[n]
    return var

def h(n):
    var = hl[n - 1] - Qdc + Qd(n)
    hl.append(var)
    print(hl[-1])

prod = 0
for i in range(N):
    e(i)
    prod = u(i, prod)
    h(i)
print(hl[-1])
