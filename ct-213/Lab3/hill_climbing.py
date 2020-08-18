from math import inf
import numpy as np


def hill_climbing(cost_function, neighbors, theta0, epsilon, max_iterations):
    """
    Executes the Hill Climbing (HC) algorithm to minimize (optimize) a cost function.

    :param cost_function: function to be minimized.
    :type cost_function: function.
    :param neighbors: function which returns the neighbors of a given point.
    :type neighbors: list of numpy.array.
    :param theta0: initial guess.
    :type theta0: numpy.array.
    :param epsilon: used to stop the optimization if the current cost is less than epsilon.
    :type epsilon: float.
    :param max_iterations: maximum number of iterations.
    :type max_iterations: int.
    :return theta: local minimum.
    :rtype theta: numpy.array.
    :return history: history of points visited by the algorithm.
    :rtype history: list of numpy.array.
    """
    theta = theta0
    history = [theta0]
    iterations = 0
    min_cost = inf
    min_theta = theta0

    while cost_function(theta) > epsilon and iterations < max_iterations:
        for neighbor in neighbors(theta):
            if cost_function(neighbor) < min_cost:
                min_cost = cost_function(neighbor)
                min_theta = neighbor

        if cost_function(min_theta) > cost_function(theta):
            return theta, history

        theta = min_theta
        history.append(theta)
        iterations = iterations + 1

    return theta, history
