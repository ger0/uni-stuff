import numpy as np 
from numpy import sin 
from math import pi as pi 
from bokeh.plotting import figure, output_file, show 
import matplotlib.pyplot as plt 
 
 
def state_dot(arg_state): 
    B = np.array([[mi, 0], [-1, 0]]) 
    F = np.array([-(g / L) * sin(arg_state[1]), 0])  # r?wnanie ruchu 
    return F - B.dot(arg_state) 
 
 
def runge_kutta(arg_state): 
    k1 = state_dot(arg_state) 
    k2 = state_dot(arg_state + k1 * dt / 2) 
    k3 = state_dot(arg_state + k2 * dt / 2) 
    k4 = state_dot(arg_state + k3 * dt) 
    state_plus = arg_state + (k1 + 2 * k2 + 2 * k3 + k4) * dt / 6 
    return state_plus 
 
 
L = 1 
g = 9.81 
mi = .45 
 

theta = np.radians(45.0) 
omega = np.radians(0.0) 
#theta = pi/2 
#omega = 0 
 
time = np.linspace(0, 30, 3001) 
dt = time[1] - time[0] 

 

Theta = [] 
Omega = [] 
 
state = [omega, theta] 
 
for t in time:
    Theta.append(state[1]) 
    Omega.append(state[0]) 
    state = runge_kutta(state) 
 
output_file('index.html') 
p = figure(title='PA') 

for i in range(0, len(Theta)): 
    Theta[i] *= (180.0/pi) 
p.line(time, Theta, line_width=2) 
show(p) 
 
#plt.subplot(1, 2, 1) 
#plt.plot(time, Theta) 
#plt.subplot(1, 2, 2) 
#plt.plot(time, Omega) 
#plt.show() 
