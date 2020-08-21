import numpy as np
from math import sin, cos

from constants import BAR_LENGTH, GRAVITY, STEP, PHYSICAL_BAR_LENGTH

def pendulum_function(angle, velocity):
    """
    Represents the differential equations vinculated to the phenomena
    :param angle: angles
    :type angle: numpy array
    :param velocity: velocities
    :type velocity: numpy array
    """

    n = len(angle)
    A = []
    b = []

    for k in range(n):
        row = []
        element = (1 + 2*k - 2*n)*sin(angle[k])*GRAVITY/(2*PHYSICAL_BAR_LENGTH*20)
        for i in range(n):
            if i < k:
                row.append((2*n - 2*k - 1)*cos(angle[i] - angle[k])/2)
                element += (2*n - 2*k - 1)*(velocity[i]**2)*sin(angle[i] - angle[k])/40
            elif i == k:
                row.append((3*n - 3*k - 2)/3)
            else:
                row.append((2*n - 2*i - 1)*cos(angle[i] - angle[k])/2)
                element += (2*n - 2*i - 1)*(velocity[i]**2)*sin(angle[i] - angle[k])/40
        
        row = np.divide(row, 20)
        A.append(row)
        b.append(element)

    velocity_differential = np.linalg.solve(A, b)
    angle_differential = np.array(velocity)

    return angle_differential, velocity_differential

def runge_kutta(angle, velocity):
    """
    Applies the runge_kutta method of solving differential equations
    :param angle: input
    :type angle: numpy array
    :param velocity: input
    :type velocity: numpy array
    """

    k1_angle, k1_velocity = pendulum_function(angle, velocity)
    k2_angle, k2_velocity = pendulum_function(angle + k1_angle*STEP, velocity + k1_velocity*STEP)

    next_angle = angle + (k1_angle + k2_angle)*STEP/2
    next_velocity = velocity + (k1_velocity + k2_velocity)*STEP/2

    return next_angle, next_velocity
