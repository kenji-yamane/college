import pygame
from math import cos, sin

from constants import BLUE, BAR_WIDTH, BAR_LENGTH, BAR_MASS

class Bar:
    """
    Represents a bar
    """
    def __init__(self, starting_point, angle, velocity = 0.0, mass = BAR_MASS, length = BAR_LENGTH):
        """
        Creates a bar in the virtual environment
        :param mass: mass of the bar
        :type mass: float
        :param length: length of the bar
        :type length: float
        :param starting_point: bar point attached to the system
        :type starting_point: tuple of floats
        :type angle: angle with respect to the vertical of the bar
        """
        self.mass = mass
        self.length = length
        self.starting_point = starting_point
        self.angle = angle
        self.velocity = velocity        
        self.end_point = self.determine_end()
    
    def update(self, angle, omega):
        """
        Updates bar angle and bar velocity, generalized coordinates in the hamiltonian model
        :param angle: new bar angle
        :type angle: float
        :param omega: new bar angle velocity
        :type omega: float
        """
        self.angle = angle
        self.velocity = omega
        self.end_point = self.determine_end()
    
    def determine_end(self):
        """
        Determines bar end point
        """
        return (self.starting_point[0] + self.length*sin(self.angle), self.starting_point[1] + self.length*cos(self.angle))
    
    def draw(self, window):
        """
        Draws the bar in the virtual environment
        :param window: window into which the bar will be drawed
        :type window: pygame window
        """
        pygame.draw.line(window, BLUE, self.starting_point, self.end_point, BAR_WIDTH)
