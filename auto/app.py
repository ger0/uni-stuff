import math

beta  = 0.035 
h0    = 0
Qdc   = 0.05
A     = 1.5
Tp    = 0.01
T     = 12 * 3600
N     = T / Tp
hl    = []

def Qd(n):
    return (A * (hl[n + 1] - hl[n]) / Tp + beta * math.sqrt(hl[n]))

def h(x):
    if (x == 0):
        hl.append(h0)
        return h0
    else:
        hx = h(x)
        hl.append((1 / A) * (-(beta) * math.sqrt(hx) + Qd(x - 1)) * Tp + hx)
        return hl[-1]

print(h(N))
