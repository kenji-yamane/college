import pygame
import numpy as np
from math import pi

from constants import SCREEN_HEIGHT, SCREEN_WIDTH, SKY, RED, FPS, TRAIL_RADIUS
from bar_set import BarSet
from utils import runge_kutta

pygame.init()
window = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('nth_pendulum')
clock = pygame.time.Clock()

starting_point = ((SCREEN_WIDTH/2, SCREEN_HEIGHT/4))

# One bar
# angle = np.array([pi/3])
# velocity = np.zeros(1)

# Two bars
# angle = np.array([pi/2, pi/2 - 0.1])
# velocity = np.zeros(2)

# Six bars
angle = np.array([pi/2, pi/2 - 0.1, pi/2 - 0.2, pi/2 - 0.3, pi/2 - 0.4, pi/2 - 0.5])
velocity = np.zeros(6)

# Eight bars
# angle = np.array([pi/2, pi/2 - 0.1, pi/2 - 0.2, pi/2 - 0.3, pi/2 - 0.4, pi/2 - 0.5, pi/2 - 0.6, pi/2 - 0.7])
# velocity = np.zeros(8)

bar_set = BarSet(starting_point, angle)
running = True

end_point_history = []

while running:
    clock.tick(FPS)
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    
    window.fill(SKY)
    bar_set.draw(window)
    for end_point in end_point_history:
        pygame.draw.circle(window, RED, (int(end_point[0]), int(end_point[1])), TRAIL_RADIUS)
    pygame.display.update()

    angle, velocity = runge_kutta(angle, velocity)
    bar_set.update(angle, velocity)
    end_point_history.append(bar_set.bars[len(bar_set.bars) - 1].end_point)
    if len(end_point_history) > 500:
        end_point_history.pop(0)

pygame.quit()
