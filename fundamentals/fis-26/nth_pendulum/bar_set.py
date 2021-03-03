from numpy import random
from math import pi

from bar import Bar
from constants import BAR_LENGTH

class BarSet:
    """
    Represents a set of bars
    """
    def __init__(self, starting_point, angle):
        """
        Creates a set of bars
        :param starting_point: initial point where all begins
        :type starting_point: tuple of float
        :param angle: set of angles for each bar
        :type angle: numpy array
        """
        self.bars = []
        self.starting_point = starting_point

        for i in range(len(angle)):
            if i is 0:
                self.bars.append(Bar(self.starting_point, angle[i], length=BAR_LENGTH/len(angle)))
            else:
                self.bars.append(Bar(self.bars[i - 1].end_point, angle[i], length=BAR_LENGTH/len(angle)))
    
    def update(self, angle, velocity):
        """
        Updates each and every bar
        :param angle: new angle for each bar
        :type angle: numpy array
        :param velocity: new velocity for each bar
        :type velocity: numpy array
        """
        for i in range(len(angle)):
            if i is 0:
                self.bars[i].update(angle[i], velocity[i])
            else:
                self.bars[i].starting_point = self.bars[i - 1].end_point
                self.bars[i].update(angle[i], velocity[i])
    
    def draw(self, window):
        """
        Draws every bar
        :param window: window into which every bar will be drawed
        :type window: pygame window
        """
        for bar in self.bars:
            bar.draw(window)
