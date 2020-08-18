import pygame
from math import cos, sin, sqrt
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.backends.backend_agg as agg
matplotlib.use("Agg")
PIX2INCH = 1.0/110
PIX2M = 3.0/800


def plot(ax, canvas, data1, data2):
    ax.plot(data1, data2, color='lightblue')
    canvas.draw()
    renderer = canvas.get_renderer()
    raw_data = renderer.tostring_rgb()
    size = canvas.get_width_height()
    return pygame.image.fromstring(raw_data, size, "RGB")


def norm(x, y):
    return sqrt(x**2 + y**2)


def drawSpring(x1, y1, x2, y2, window):
    n = 9
    xdiff, ydiff = x2 - x1, y2 - y1
    xperp, yperp = 10*xdiff/norm(xdiff, ydiff), 10*ydiff/norm(xdiff, ydiff)
    xdiff, ydiff = xdiff/n, ydiff/n

    for i in range(n):
        if i%2 is 0:
            signal = 1
        else:
            signal = -1
        xi, yi = x1 + i*xdiff, y1 + i*ydiff
        xnext, ynext = x1 + (i + 1)*xdiff, y1 + (i + 1)*ydiff
        if i is not n - 1:
            xnext, ynext = xnext + signal*yperp, ynext - signal*xperp
        if i is not 0:
            xi, yi = xi - signal*yperp, yi + signal*xperp
        pygame.draw.line(window, (50, 100, 0), (int(xi), int(yi)), (int(xnext), int(ynext)), 3)


def drawText():
    for i in range(len(possible_values)):
        text = font.render('%.2f' % possible_values[i], True, (0, 0, 0))
        window.blit(text, (round((i + 1)*0.06*800 - 4), round(0.7*600)))
        if i == ctrl:
            filled = 9
        else:
            filled = 1
        pygame.draw.circle(window, (0, 0, 0), (round((i + 1)*0.06*800 + 13), round(0.65*600)), 10, filled)
    text = font.render('Pressione J para diminuir o fator', True, (0, 0, 0))
    window.blit(text, (round(0.05 * 800), round(0.8 * 600)))
    text = font.render('Pressione L para aumentar o fator', True, (0, 0, 0))
    window.blit(text, (round(0.05 * 800), round(0.85 * 600)))


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

v = 0.0
vx = 0.0
vy = 0.0
previous_x = None
previous_y = None
previous_time = None
previous_vx = None
previous_vy = None
vx_history = []
vy_history = []
v_history = []
ax_history = []
ay_history = []
a_history = []
time_history = []
position_history = []
radial_history = []
possible_values = [0.25, 0.33, 0.5, 1, 2, 3, 4]
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

    if previous_x is not None:
        vx = (x - previous_x)*PIX2M/(time - previous_time)
        vy = (y - previous_y)*PIX2M/(time - previous_time)
        v = sqrt(vx**2 + vy**2)

    if previous_vx is not None and iteration > 3:
        ax = (vx - previous_vx)/(time - previous_time)
        ay = (vy - previous_vy)/(time - previous_time)
        time_history.append(time)
        vx_history.append(vx)
        vy_history.append(vy)
        v_history.append(v + 20)
        ax_history.append(ax)
        ay_history.append(ay)
        a_history.append(sqrt(ax**2 + ay**2) + 20)
        radial_history.append(sqrt((x - 200)**2 + (y - 150)**2))

    if len(v_history) > 200:
        v_history.pop(0)
        a_history.pop(0)
        time_history.pop(0)
        vx_history.pop(0)
        vy_history.pop(0)
        ax_history.pop(0)
        ay_history.pop(0)
        position_history.pop(0)
        radial_history.pop(0)
    if previous_vx is not None and iteration > 3:
        fig.suptitle('velocidade em x (m/s) vs tempo (s)')
        graph1 = plot(ax1, canvas1, time_history, vx_history)
        plt.cla()
        fig.suptitle('velocidade em y (m/s) vs tempo (s)')
        graph2 = plot(ax1, canvas1, time_history, vy_history)
        plt.cla()

    simWindow.fill((200, 255, 255))
    window.fill((255, 255, 255))
    window.blit(simWindow, (0, 0))
    if previous_vx is not None and iteration > 3:
        window.blit(graph1, (400, 0))
        window.blit(graph2, (400, 300))

    for position in position_history:
        pygame.draw.circle(window, (20, 90, 240), position, 4, 3)
    position_history.append((int(x), int(y)))

    drawSpring(200, 150, x, y, window)
    drawText()
    pygame.draw.circle(window, (0, 0, 0), (int(x), int(y)), 10, 9)
    pygame.display.update()

    previous_x = x
    previous_y = y
    previous_vx = vx
    previous_vy = vy
    previous_time = time
    previous_keys = pygame.key.get_pressed()
    iteration = iteration + 1

pygame.quit()
