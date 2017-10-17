#!/usr/bin/env python3
"""
PID controller realtime simulation as plot
In this simulation, you are a robot trying to
drive straight along a line.
"""
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import numpy as np
import random
import math
import time

# Config values
setpoint = 5 # Setpoint to tune to
start    = 7 # Starting y value
seconds = 30 # Time to run simulation
dt     = 0.1 # Step size of simulation

# Internal state decorator
def static_vars(**kwargs):
    def decorate(func):
        for k in kwargs:
            setattr(func, k, kwargs[k])
        return func
    return decorate

# PID functions
@static_vars(kp=0.02)
def P(err):
    return err * P.kp

@static_vars(ki=0.001, integral=0)
def I(err, dt):
    I.integral = I.integral + err * dt
    return I.integral * I.ki

@static_vars(kd=0.05, prev_err=0)
def D(err, dt):
    derivative = (err - D.prev_err) / dt
    D.prev_err = err
    return derivative * D.kd

def pid(err, dt):
    return P(err) + I(err, dt) + D(err, dt)

# Simulation variables
t = 0     # time
x = 0
y = start
rad = 0 # radians
vel = 1 # m/s
x_list = []
y_list = []

while t < seconds:

    rad += pid(setpoint - y, dt)

    x += math.cos(rad) * vel * dt
    y += math.sin(rad) * vel * dt
    x_list.append(x)
    y_list.append(y)
    t += dt

plt.plot(x_list, y_list)
plt.plot([min(x_list), max(x_list)], [setpoint, setpoint])
# plt.axis([min(x_list), max(x_list), min(*y_list, setpoint), max(*y_list, setpoint)])
plt.show()

