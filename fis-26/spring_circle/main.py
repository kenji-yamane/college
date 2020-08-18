import pygame
from math import cos, sin
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.backends.backend_agg as agg
matplotlib.use("Agg")

from constants import PIX2INCH
from utils import plot, norm, draw_spring, draw_text
from ball import Ball


possible_values = [0.25, 0.33, 0.5, 1, 2, 3, 4]

fig = plt.figure(figsize=(400*PIX2INCH, 288*PIX2INCH))
ax1 = fig.add_subplot(111)
canvas1 = agg.FigureCanvasAgg(fig)

pygame.init()
window = pygame.display.set_mode((800, 600))
simWindow = pygame.Surface((400, 600))
pygame.display.set_caption("Simulação de MHS em uma rotação")
clock = pygame.time.Clock()
font = pygame.font.SysFont('Arial', 20, True)
running = True

ball = Ball()

graph1 = None
graph2 = None
iteration = 0
ctrl = 3
previous_keys = pygame.key.get_pressed()

while running:
    time = pygame.time.get_ticks()/1000
    omega = 1
    factor = possible_values[ctrl]

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    keys = pygame.key.get_pressed()
    if keys[pygame.K_l] and not previous_keys[pygame.K_l] and ctrl < 6:
        ctrl = ctrl + 1
    if keys[pygame.K_j] and not previous_keys[pygame.K_j] and ctrl >= 0:
        ctrl = ctrl - 1
    if keys[pygame.K_p]:
        pygame.image.save(window, '/home/kenji/Desktop/ciclo' + '%d' % ctrl + '.jpeg')

    phantomx = 70*cos(omega*time) + 200
    phantomy = 70*sin(omega*time) + 150
    diffx = (phantomx - 200)
    diffy = (phantomy - 150)
    x = phantomx + 0.3*diffx*sin(factor*omega*time)
    y = phantomy + 0.3*diffy*sin(factor*omega*time)

    ball.compute_position(x, y, time)

    if iteration > 200:
        ball.pop_history()

    simWindow.fill((200, 255, 255))
    window.fill((255, 255, 255))
    window.blit(simWindow, (0, 0))

    if iteration > 3:
        ball.compute_velocity()
        ball.make_history()

        fig.suptitle('velocidade em x (m/s) vs tempo (s)')
        graph1 = plot(ax1, canvas1, ball.time_history, ball.vx_history)
        plt.cla()
        fig.suptitle('velocidade em y (m/s) vs tempo (s)')
        graph2 = plot(ax1, canvas1, ball.time_history, ball.vy_history)
        plt.cla()

        window.blit(graph1, (400, 0))
        window.blit(graph2, (400, 300))

    for position in ball.position_history:
        pygame.draw.circle(window, (20, 90, 240), position, 4, 3)

    draw_spring(200, 150, x, y, window)
    draw_text(ctrl, possible_values, font, window)
    pygame.draw.circle(window, (0, 0, 0), (int(x), int(y)), 10, 9)
    pygame.display.update()

    previous_keys = pygame.key.get_pressed()
    iteration += 1

pygame.quit()
