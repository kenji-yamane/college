from constants import PIX2M


class Ball:

    def __init__(self, x = 0, y = 0, vx = 0, vy = 0, time = 0):
        self.x = x
        self.y = y
        self.vx = vx
        self.vy = vy
        self.time = time
        self.previous_x = x
        self.previous_y = y
        self.previous_time = time

        self.position_history = []
        self.vx_history = []
        self.vy_history = []
        self.time_history = []
    
    def compute_position(self, x, y, time):
        self.previous_x = self.x
        self.x = x
        self.previous_y = self.y
        self.y = y
        self.previous_time = self.time
        self.time = time

    def compute_velocity(self):
        self.vx = (self.x - self.previous_x)*PIX2M/(self.time - self.previous_time)
        self.vy = (self.y - self.previous_y)*PIX2M/(self.time - self.previous_time)
    
    def make_history(self):
        self.position_history.append((int(self.x), int(self.y)))
        self.vx_history.append(self.vx)
        self.vy_history.append(self.vy)
        self.time_history.append(self.time)
    
    def pop_history(self):
        self.position_history.pop(0)
        self.vx_history.pop(0)
        self.vy_history.pop(0)
        self.time_history.pop(0)

