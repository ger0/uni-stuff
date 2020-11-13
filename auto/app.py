import math

beta  = 0.035 
h0    = 0
Qdc   = 0.05
Qdl   = []
A     = 1.5
Tp    = 0.1
T     = 12 * 3600
N     = T / Tp
N     = int(N)
hl    = []

def h(n):
    if (n == 0):
        hl.append(h0)
        Qdl.append(Qdc)
    else:
        hx = hl[n - 1]
        hl.append((1 / A) * (-(beta) * math.sqrt(hx) + Qdl[n - 1]) * Tp + hx)

        Qdl.append(A * (hl[n] - hl[n - 1]) / Tp + beta * math.sqrt(hl[n]))

print(N)

for n in range(N):
    h(n)

print(Qdl[-1])
print(beta * math.sqrt(hl[-1]))
