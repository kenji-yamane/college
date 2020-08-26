import numpy as np

from constants import SUN_MASS, CELESTIAL_BODY_MASS,GRAVITATION, STEP, PIX2M, RADIUS_POTENCY

def retrieve_velocity(energy, initial_radius):
    """
    Returns the velocity module correspondent to the system through a given energy
    :param energy: energy of the system
    :type energy: float
    :param initial_radius: initial radius in polar coordinates
    :type initial_radius: float
    """

    initial_radius *= PIX2M

    degree = RADIUS_POTENCY - 1
    velocity = np.sqrt(2*(energy/CELESTIAL_BODY_MASS + GRAVITATION*SUN_MASS/((initial_radius**degree)*degree)))

    return velocity/PIX2M

def celestial_function(coordinates, velocities):
    """
    Function that represents the differential equations vinculated to the phenomena
    :param coordinates: polar coordinates of the object
    :type coordinates: numpy array
    :param velocities: velocities to each coordinate
    :type velocities: numpy array
    """

    radial_velocity_differential = (velocities[1]**2)*coordinates[0] - GRAVITATION*SUN_MASS/(coordinates[0]**RADIUS_POTENCY)
    angular_velocity_differential = -2*velocities[0]*velocities[1]/coordinates[0]

    velocities_differential = np.array([radial_velocity_differential, angular_velocity_differential])
    coordinates_differential = np.array(velocities)

    return coordinates_differential, velocities_differential

def runge_kutta(coordinates, velocities):
    """
    solves the differential equation with fourth order runge-kutta method
    :param coordinates: polar coordinates of the object
    :type coordinates: numpy array
    :param velocities: velocities to each coordinate
    :type velocities: numpy array
    """

    coordinates[0] *= PIX2M
    velocities[0] *= PIX2M

    k1_coordinates, k1_velocities = celestial_function(coordinates, velocities)
    k2_coordinates, k2_velocities = celestial_function(coordinates + STEP*k1_coordinates/2, velocities + STEP*k1_velocities/2)
    k3_coordinates, k3_velocities = celestial_function(coordinates + STEP*k2_coordinates/2, velocities + STEP*k2_velocities/2)
    k4_coordinates, k4_velocities = celestial_function(coordinates + STEP*k3_coordinates, velocities + STEP*k3_velocities)

    coordinates += (k1_coordinates/6 + k2_coordinates/3 + k3_coordinates/3 + k4_coordinates/6)*STEP
    velocities += (k1_velocities/6 + k2_velocities/3 + k3_velocities/3 + k4_velocities/6)*STEP
    
    coordinates[0] /= PIX2M
    velocities[0] /= PIX2M

    return coordinates, velocities
