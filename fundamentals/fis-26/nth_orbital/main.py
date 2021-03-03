import pygame
from math import pi

from utils import retrieve_velocity
from celestial_body import CelestialBody
from constants import SCREEN_HEIGHT, SCREEN_WIDTH, FPS, NIGHT_SKY, SUN, SUN_RADIUS, ACCELERATION_FACTOR, RED, GREEN, BLUE

pygame.init()
window = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('nth_orbital')
clock = pygame.time.Clock()

running = True
radius = SCREEN_WIDTH/(3.4)
# for n equal to 2
# offset = (-20, 0, 20)
# for n equal to 3
offset = (2, 2.5, 3.5)

celestial_body_1 = CelestialBody(radius, pi/6, retrieve_velocity(0, radius) + offset[0], 5*pi/6, RED)
celestial_body_2 = CelestialBody(radius, pi/6, retrieve_velocity(0, radius) + offset[1], 5*pi/6, GREEN)
celestial_body_3 = CelestialBody(radius, pi/6, retrieve_velocity(0, radius) + offset[2], 5*pi/6, BLUE)
sun_position = (SCREEN_WIDTH//2, SCREEN_HEIGHT//2)

while running:
    clock.tick(FPS)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    for i in range(ACCELERATION_FACTOR):
        window.fill(NIGHT_SKY)
        celestial_body_1.draw(window)
        celestial_body_2.draw(window)
        celestial_body_3.draw(window)
        pygame.draw.circle(window, SUN, sun_position, SUN_RADIUS)
        pygame.display.update()

        celestial_body_1.step()
        celestial_body_2.step()
        celestial_body_3.step()

pygame.quit()
