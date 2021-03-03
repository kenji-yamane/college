import numpy as np
import random
from math import inf


class Particle:
    """
    Represents a particle of the Particle Swarm Optimization algorithm.
    """
    def __init__(self, lower_bound, upper_bound):
        """
        Creates a particle of the Particle Swarm Optimization algorithm.

        :param lower_bound: lower bound of the particle position.
        :type lower_bound: numpy array.
        :param upper_bound: upper bound of the particle position.
        :type upper_bound: numpy array.
        """
        self.lower_bound = lower_bound
        self.upper_bound = upper_bound
        self.position = np.zeros(np.size(lower_bound))
        self.velocity = np.zeros(np.size(lower_bound))
        for i in range(len(lower_bound)):
            self.position[i] += random.uniform(lower_bound[i], upper_bound[i])
            self.velocity[i] += random.uniform(lower_bound[i] - upper_bound[i], upper_bound[i] - lower_bound[i])
        self.local_best = -inf
        self.local_best_position = None


class ParticleSwarmOptimization:
    """
    Represents the Particle Swarm Optimization algorithm.
    Hyperparameters:
        inertia_weight: inertia weight.
        cognitive_parameter: cognitive parameter.
        social_parameter: social parameter.

    :param hyperparams: hyperparameters used by Particle Swarm Optimization.
    :type hyperparams: Params.
    :param lower_bound: lower bound of particle position.
    :type lower_bound: numpy array.
    :param upper_bound: upper bound of particle position.
    :type upper_bound: numpy array.
    """
    def __init__(self, hyperparams, lower_bound, upper_bound):
        self.num_particles = hyperparams.num_particles
        self.inertia_weight = hyperparams.inertia_weight
        self.cognitive_parameter = hyperparams.cognitive_parameter
        self.social_parameter = hyperparams.social_parameter
        self.lower_bound = lower_bound
        self.upper_bound = upper_bound
        self.ctrl = 0
        self.best = -inf
        self.best_position = None
        self.particles = []
        for i in range(self.num_particles):
            self.particles.append(Particle(lower_bound, upper_bound))

    def get_best_position(self):
        """
        Obtains the best position so far found by the algorithm.

        :return: the best position.
        :rtype: numpy array.
        """
        return self.best_position

    def get_best_value(self):
        """
        Obtains the value of the best position so far found by the algorithm.

        :return: value of the best position.
        :rtype: float.
        """
        return self.best

    def get_position_to_evaluate(self):
        """
        Obtains a new position to evaluate.

        :return: position to evaluate.
        :rtype: numpy array.
        """
        position = self.particles[self.ctrl].position
        self.ctrl = self.ctrl + 1
        return position

    def advance_generation(self):
        """
        Advances the generation of particles.
        """
        for particle in self.particles:
            rp = random.uniform(0.0, 1.0)
            rg = random.uniform(0.0, 1.0)
            particle.velocity = self.inertia_weight*particle.velocity + self.cognitive_parameter*rp*(particle.local_best_position - particle.position) + self.social_parameter*rg*(self.best_position - particle.position)
            particle.position = particle.position + particle.velocity

    def notify_evaluation(self, value):
        """
        Notifies the algorithm that a particle position evaluation was completed.

        :param value: quality of the particle position.
        :type value: float.
        """
        if self.particles[self.ctrl - 1].local_best < value:
            self.particles[self.ctrl - 1].local_best = value
            self.particles[self.ctrl - 1].local_best_position = self.particles[self.ctrl - 1].position
        if self.best < value:
            self.best = value
            self.best_position = self.particles[self.ctrl - 1].position
        if self.ctrl is self.num_particles:
            self.advance_generation()
            self.ctrl = 0

