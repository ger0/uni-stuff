import numpy as np 
from numpy import sin 
from math import pi as pi 
from bokeh.plotting import figure, output_file, show 
import matplotlib.pyplot as plt 
 
time = np.linspace(0, 30, 3001) 
dt = time[1] - time[0] 
L = 1 
g = 9.81 
mi = .45 

def alpha(arg_state): 
    alpha = -(g / L) * sin(arg_state[1]) - mi * arg_state[0]
    return alpha

def euler(arg_state):
    omega = arg_state[0] + alpha(arg_state) * dt
    theta = arg_state[1] + omega * dt
    return [omega, theta]
 
theta = np.radians(45.0) 
omega = np.radians(0.0) 

Theta = [] 
Omega = [] 
 
state = [omega, theta] 
 
for t in time:  
    Theta.append(state[1]) 
    Omega.append(state[0]) 
    state = euler(state) 
 
output_file('index.html') 
p = figure(title='PA') 

for i in range(0, len(Theta)): 
    Theta[i] *= (180.0/pi) 

p.line(time, Theta, line_width=2) 
show(p) 
