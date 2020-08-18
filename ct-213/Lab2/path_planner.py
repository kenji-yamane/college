from grid import Node, NodeGrid
from math import inf
import heapq


class PathPlanner(object):
    """
    Represents a path planner, which may use Dijkstra, Greedy Search or A* to plan a path.
    """
    def __init__(self, cost_map):
        """
        Creates a new path planner for a given cost map.

        :param cost_map: cost used in this path planner.
        :type cost_map: CostMap.
        """
        self.cost_map = cost_map
        self.node_grid = NodeGrid(cost_map)

    @staticmethod
    def construct_path(goal_node):
        """
        Extracts the path after a planning was executed.

        :param goal_node: node of the grid where the goal was found.
        :type goal_node: Node.
        :return: the path as a sequence of (x, y) positions: [(x1,y1),(x2,y2),(x3,y3),...,(xn,yn)].
        :rtype: list of tuples.
        """
        node = goal_node
        # Since we are going from the goal node to the start node following the parents, we
        # are transversing the path in reverse
        reversed_path = []
        while node is not None:
            reversed_path.append(node.get_position())
            node = node.parent
        return reversed_path[::-1]  # This syntax creates the reverse list

    def dijkstra(self, start_position, goal_position):
        """
        Plans a path using the Dijkstra algorithm.

        :param start_position: position where the planning stars as a tuple (x, y).
        :type start_position: tuple.
        :param goal_position: goal position of the planning as a tuple (x, y).
        :type goal_position: tuple.
        :return: the path as a sequence of positions and the path cost.
        :rtype: list of tuples and float.
        """

        start_node = self.node_grid.get_node(start_position[0], start_position[1])
        start_node.g = 0
        pq = []
        heapq.heappush(pq, (start_node.g, start_node))

        while pq:
            current_node_g, current_node = heapq.heappop(pq)
            while pq and current_node.closed is True:
                current_node_g, current_node = heapq.heappop(pq)
            current_node.closed = True
            if current_node is self.node_grid.get_node(goal_position[0], goal_position[1]):
                break
            successors = self.node_grid.get_successors(current_node.i, current_node.j)

            for successor_data in successors:
                successor = self.node_grid.get_node(successor_data[0], successor_data[1])
                dist = self.cost_map.get_edge_cost((current_node.i, current_node.j), (successor.i, successor.j))
                if successor.g > current_node_g + dist:
                    successor.g = current_node_g + dist
                    successor.parent = current_node
                    heapq.heappush(pq, (successor.g, successor))

        ans = self.node_grid.get_node(goal_position[0], goal_position[1]).g
        path = self.construct_path(self.node_grid.get_node(goal_position[0], goal_position[1]))
        self.node_grid.reset()
        return path, ans

    def greedy(self, start_position, goal_position):
        """
        Plans a path using greedy search.

        :param start_position: position where the planning stars as a tuple (x, y).
        :type start_position: tuple.
        :param goal_position: goal position of the planning as a tuple (x, y).
        :type goal_position: tuple.
        :return: the path as a sequence of positions and the path cost.
        :rtype: list of tuples and float.
        """

        start_node = self.node_grid.get_node(start_position[0], start_position[1])
        start_node.g = 0
        pq = []
        heapq.heappush(pq, (start_node.distance_to(goal_position[0], goal_position[1]), start_node))

        found = False
        while pq and found is False:
            dummy, current_node = heapq.heappop(pq)
            while pq and current_node.closed is True:
                dummy, current_node = heapq.heappop(pq)
            current_node.closed = True
            successors = self.node_grid.get_successors(current_node.i, current_node.j)
            for successor_data in successors:
                successor = self.node_grid.get_node(successor_data[0], successor_data[1])
                if successor.closed is False:
                    successor.g = current_node.g + self.cost_map.get_edge_cost((current_node.i, current_node.j), (successor.i, successor.j))
                    successor.parent = current_node
                    if successor is self.node_grid.get_node(goal_position[0], goal_position[1]):
                        found = True
                        break
                    heapq.heappush(pq, (successor.distance_to(goal_position[0], goal_position[1]), successor))

        ans = self.node_grid.get_node(goal_position[0], goal_position[1]).g
        path = self.construct_path(self.node_grid.get_node(goal_position[0], goal_position[1]))
        self.node_grid.reset()
        return path, ans

    def a_star(self, start_position, goal_position):
        """
        Plans a path using A*.

        :param start_position: position where the planning stars as a tuple (x, y).
        :type start_position: tuple.
        :param goal_position: goal position of the planning as a tuple (x, y).
        :type goal_position: tuple.
        :return: the path as a sequence of positions and the path cost.
        :rtype: list of tuples and float.
        """

        start_node = self.node_grid.get_node(start_position[0], start_position[1])
        start_node.g = 0
        start_node.f = start_node.g + start_node.distance_to(goal_position[0], goal_position[1])
        pq = []
        heapq.heappush(pq, (start_node.f, start_node))

        while pq:
            current_node_f, current_node = heapq.heappop(pq)
            while pq and current_node.closed is True:
                current_node_f, current_node = heapq.heappop(pq)
            current_node.closed = True
            if current_node is self.node_grid.get_node(goal_position[0], goal_position[1]):
                break
            successors = self.node_grid.get_successors(current_node.i, current_node.j)

            for successor_data in successors:
                successor = self.node_grid.get_node(successor_data[0], successor_data[1])
                dist = self.cost_map.get_edge_cost((current_node.i, current_node.j), (successor.i, successor.j))
                if successor.f > current_node.g + dist + successor.distance_to(goal_position[0], goal_position[1]):
                    successor.g = current_node.g + dist
                    successor.f = successor.g + successor.distance_to(goal_position[0], goal_position[1])
                    successor.parent = current_node
                    heapq.heappush(pq, (successor.f, successor))

        ans = self.node_grid.get_node(goal_position[0], goal_position[1]).g
        path = self.construct_path(self.node_grid.get_node(goal_position[0], goal_position[1]))
        self.node_grid.reset()
        return path, ans
