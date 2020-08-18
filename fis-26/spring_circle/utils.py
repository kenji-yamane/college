import pygame
from math import sqrt


def plot(ax, canvas, data1, data2):
    ax.plot(data1, data2, color='lightblue')
    canvas.draw()
    renderer = canvas.get_renderer()
    raw_data = renderer.tostring_rgb()
    size = canvas.get_width_height()
    return pygame.image.fromstring(raw_data, size, "RGB")


def norm(x, y):
    return sqrt(x**2 + y**2)


def draw_spring(x1, y1, x2, y2, window):
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


def draw_text(ctrl, possible_values, font, window):
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
