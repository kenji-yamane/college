import pygame
from math import sin, cos, pi
from constants import BALL_RADIUS


class Support:
    """
    Represents the ceiling and the thread
    """
    def __init__(self, center, ceiling, thread, strand, theta0):
        """
        Creates a support
        Parameters:
        :param center: middle point of ceiling
        :type center: tuple of ints
        :param ceiling: length of ceiling
        :type ceiling: int
        :param thread: length of decorative lines
        :type thread: int
        :param strand: length of decorative lines
        :type strand: int
        """
        self.center = center
        self.begin_ceiling = (center[0] - ceiling/2, center[1])
        self.end_ceiling = (center[0] + ceiling/2, center[1])
        self.ceiling = ceiling
        self.theta = theta0
        self.thread = thread
        self.end_thread = [center[0] + self.thread*sin(theta0), center[1] + self.thread*cos(theta0)]
        self.strand = strand
        self.strand_begins = []
        self.strand_ends = []
        self.make_strands()

    def ball_position(self, theta):
        """
        Determines ball position based on support
        :param theta: angle at the moment
        :return: tuple of int
        """
        path_radius = self.thread + BALL_RADIUS
        x = self.center[0] + path_radius*sin(theta)
        y = self.center[1] + path_radius*cos(theta)
        return x, y

    def update_line(self, theta):
        """
        Updates end point of thread
        :param theta: angle at the moment
        :type theta: float
        """
        self.end_thread[0] = self.center[0] + self.thread*sin(theta)
        self.end_thread[1] = self.center[1] + self.thread*cos(theta)

    def make_strands(self):
        """
        Determines the points associated with each decorative line
        """
        for i in range(10):
            displacement = self.ceiling*i/10
            begin_point = (self.begin_ceiling[0] + displacement, self.begin_ceiling[1])
            self.strand_begins.append(begin_point)
            end_point = (begin_point[0] + self.strand*cos(pi/4), begin_point[1] - self.strand*sin(pi/4))
            self.strand_ends.append(end_point)

    def draw(self, window):
        """
        Draws on window each element associated with support,
        ceiling,
        decorative lines,
        thread
        :param window: window into which the things will be drawed
        :type window: pygame window
        """
        pygame.draw.line(window, (222, 184, 135), self.begin_ceiling, self.end_ceiling, 2)
        pygame.draw.line(window, (188, 143, 143), self.center, self.end_thread, 2)
        for i in range(len(self.strand_ends)):
            pygame.draw.line(window, (222, 184, 135), self.strand_begins[i], self.strand_ends[i], 2)
