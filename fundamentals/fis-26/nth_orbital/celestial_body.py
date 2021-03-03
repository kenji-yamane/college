import pygame
import numpy as np
from math import sin, cos

from utils import runge_kutta
from constants import CELESTIAL_BODY, CELESTIAL_BODY_RADIUS, SCREEN_HEIGHT, SCREEN_WIDTH, TRAIL_RADIUS, TRAIL_SEPARATION

class CelestialBody:
    """
    Represents a body in the sky bound to the sun's gravitational force
    """

    def __init__(self, radius, angle, velocity_module, velocity_angle, trail_color):
        """
        Initializes the celestial body
        :param radius: radius in polar coordinates with respect to the sun
        :type radius: float
        :param angle: angle in polar coordinates with respect to the sun
        :type angle: float
        :param velocity_module: module of the initial velocity of the celestial body
        :type radial_velocity: float
        :param velocity_angle: angle the velocity vector makes with respect to the x axis, counter clockwise
        :type angular_velocity: float
        """

        self.radius = radius
        self.angle = angle
        self.radial_velocity = velocity_module*cos(angle - velocity_angle)
        self.angular_velocity = -velocity_module*sin(angle - velocity_angle)/radius
        self.trail_color = trail_color
        self.ctrl = 0
        self.trajectory = []
    
    def update(self, coordinates, velocities):
        """
        Updates the celestial body
        :param radius: radius in polar coordinates with respect to the sun
        :type radius: float
        :param angle: angle in polar coordinates with respect to the sun
        :type angle: float
        :param radial_velocity: velocity in the radial direction
        :type radial_velocity: float
        :param angular_velocity: velocity in the angular direction
        :type angular_velocity: float
        """

        self.radius = coordinates[0]
        self.angle = coordinates[1]
        self.radial_velocity = velocities[0]
        self.angular_velocity = velocities[1]
    
    def retrieve(self):
        """
        Returns self parameters in the expected form to work with runge kutta
        """

        coordinates = np.array([self.radius, self.angle])
        velocities = np.array([self.radial_velocity, self.angular_velocity])

        return coordinates, velocities
    
    def draw(self, window):
        """
        Draws the celestial body on window
        :param window: window into which the celestial body will be drawed
        :type window: pygame window
        """

        x = SCREEN_WIDTH/2 + self.radius*cos(self.angle)
        y = SCREEN_HEIGHT/2 - self.radius*sin(self.angle)

        if self.ctrl == 0 and len(self.trajectory) < 500:
            self.trajectory.append((int(x), int(y)))
        self.ctrl += 1
        self.ctrl %= TRAIL_SEPARATION

        for point in self.trajectory:
            pygame.draw.circle(window, self.trail_color, point, TRAIL_RADIUS)

        pygame.draw.circle(window, CELESTIAL_BODY, (int(x), int(y)), CELESTIAL_BODY_RADIUS)
    
    def step(self):
        """
        Advances the object's parameters through time
        """
        coordinates, velocities = self.retrieve()
        coordinates, velocities = runge_kutta(coordinates, velocities)
        self.update(coordinates, velocities)
