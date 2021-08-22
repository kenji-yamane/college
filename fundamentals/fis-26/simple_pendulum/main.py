import pygame
from constants import BALL_RADIUS, SCREEN_HEIGHT, SCREEN_WIDTH, FPS
from support import Support
from math import sin, pi, cos
import numpy as np
import matplotlib.pyplot as plt


def pendulum_func(parameters):
    return np.array([parameters[1], -gravity*sin(parameters[0])/length])


def runge_kutta_step(parameters, step):
    k1 = pendulum_func(parameters)
    intermediate = parameters + step*k1
    k2 = pendulum_func(intermediate)
    return parameters + step*(k1 + k2)/2


length = 1
gravity = 9.8
theta0 = -pi/3
params = np.array([theta0, 0.0])
ceiling = 150
path_radius = 200

pygame.init()
window = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Pêndulo Simples")
clock = pygame.time.Clock()
font = pygame.font.SysFont('Arial', 20, True)
support = Support((SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - path_radius),
                  path_radius, path_radius - BALL_RADIUS, 20, params[0])
running = True

time_history = []
angle_history = []
ideal_history = []
iterations = 0

while running:
    clock.tick(FPS)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    window.fill((200, 255, 255))

    params = runge_kutta_step(params, 1/FPS)
    x, y = support.ball_position(params[0])
    support.update_line(params[0])
    pygame.draw.circle(window, (0, 0, 0), (int(x), int(y)), BALL_RADIUS, BALL_RADIUS - 1)
    support.draw(window)
    pygame.display.update()

    time_history.append(iterations/FPS)
    ideal_history.append(theta0*cos(np.sqrt(gravity/length)*iterations/FPS))
    angle_history.append(params[0])
    iterations = iterations + 1

plt.figure()
plt.xlabel('Tempo (s)')
plt.ylabel('Ângulo (rad)')
plt.plot(time_history, angle_history, time_history, ideal_history)
plt.title('Histórico do ângulo')
plt.legend(['real', 'aprox'])
plt.savefig('angle_history.jpg')

pygame.quit()
