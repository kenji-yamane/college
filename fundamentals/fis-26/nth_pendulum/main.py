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

# num_bars defines the number of bars to be simulated. Works well to up to 17 bars
num_bars = 6

angle = []
for i in range(num_bars):
    angle.append(pi/2 - 0.1*i)
angle = np.array(angle)
velocity = np.zeros(num_bars)

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
