# from collections import deque

# class Graph:
#     def __init__(self):
#         self.graph = {}

#     def add_node(self, node1, node2):
#         if node1 not in self.graph:
#             self.graph[node1] = []
        
#         if node2 not in self.graph:
#             self.graph[node2] = []

#         self.graph[node1].append(node2)
#         self.graph[node2].append(node1)

#     def dfs_traversal(self, start, visited=None):
#         if visited is None:
#             visited = set()

#         visited.add(start)
#         path = [start]

#         for neighbor in self.graph.get(start, []):
#             if neighbor not in visited:
#                 path.extend(self.dfs_traversal(neighbor, visited))
            
#         return path

#     def bfs_traversal(self, start, visited=None):
#         visited = set()
#         queue = deque([start_node])
#         path = []

#         while queue:
#             node = queue.popleft()
#             if node not in visited:
#                 visited.add(node)
#                 path.append(node)
#                 queue.extend(self.graph.get(node, []))

#         return path

# def main():
#     graph = Graph()

#     n = int(input("Enter number of nodes: "))
#     print("Enter nodes as (node1 node2)")
#     for i in range(n):
#         a, b = input(f"{i+1}: ").split()
#         graph.add_node(a, b)

#     start = input("Enter start node: ")

#     path = graph.dfs_traversal(start)

#     print(f"DFS traversal for path is: {"->".join(path)}")

# main()

# import random

# def fitness(x):
#     return x**2

# def generate_population(size, x_min, x_max):
#     return [random.randint(x_min, x_max) for _ in range(size)]

# def select(population):
#     a, b = random.sample(population, 2)
#     return a if fitness(a) > fitness(b) else b

# def crossover(p1, p2):
#     return (p1 + p2) // 2

# def mutation(x, x_min, x_max, mutation=0.9):
#     if random.random() > mutation:
#         return random.randint(x_min, x_max)
#     return x

# def genetic(size=10, gen=20, x_min=0, x_max=31):
#     population = generate_population(size, x_min, x_max)
#     for i in range(gen):
#         new_population = []
#         for _ in range(size):
#             p1 = select(population)
#             p2 = select(population)
#             child = crossover(p1, p2)
#             child = mutation(child, x_min, x_max)
#             new_population.append(child)
#         population = new_population
#         best = max(population, key=fitness)
#         print(f"For generation {i+1}: Best solution: {best} and fitness: {fitness(best)}")
#     return max(population, key=fitness)

# x = genetic()
# print(f"Best solution: {x} and fitness: {fitness(x)}")

# import random

# def fitness(x):
#     return x**3 - 3*x**2 - 20*x -2

# def hill_climb():
#     current_x = random.uniform(0, 10)
#     step_size = 0.1
#     iterations = 1000

#     for i in range(iterations):
#         print(current_x)
#         next_x = current_x + random.choice([-step_size, step_size])
#         next_x = max(0, min(10, next_x))

#         if fitness(next_x) > fitness(current_x):
#             current_x = next_x

#     return current_x

# x = hill_climb()
# print(f"Best value for x: {x} and f(x): {fitness(x)} for x^3 + 3x^2 - 20x - 2")

# import math

# def minmax(depth, node_index, is_max, scores, height):
#     if depth == height:
#         return scores[node_index]

#     if is_max:
#         return max(
#             minmax(depth+1, node_index*2, False, scores, height),
#             minmax(depth+1, node_index*2+1, False, scores, height)
#         )
#     else:
#         return min(
#             minmax(depth+1, node_index*2, True, scores, height),
#             minmax(depth+1, node_index*2+1, True, scores, height)
#         )

# def main():
#     n = int(input("Enter the depth of the tree (power of 2): "))
#     height = math.log2(n)
#     scores = []

#     print("Enter the values of leaf nodes: ")
#     for i in range(n):
#         scores.append(int(input(f"Leaf {i+1}: ")))

#     best = minmax(0, 0, True, scores, height)
#     print(f"Best node to choose is: {best}")

# main()

# import math

# def minmax(depth, node_index, is_max, scores, height, alpha, beta):
#     if depth == height:
#         return scores[node_index]

#     if is_max:
#         best = -math.inf
#         for i in range(2):
#             val = minmax(depth+1, node_index*2+i, False, scores, height, alpha, beta)
#             best = max(val, best)
#             alpha = max(alpha, best)
#         return best

#     else:
#         best = math.inf
#         for i in range(2):
#             val = minmax(depth+1, node_index*2+i, True, scores, height, alpha, beta)
#             best = min(val, best)
#             alpha = min(alpha, best)
#         return best

# def main():
#     n = int(input("Enter the depth of the tree (power of 2): "))
#     height = math.log2(n)
#     scores = []

#     print("Enter the values of leaf nodes: ")
#     for i in range(n):
#         scores.append(int(input(f"Leaf {i+1}: ")))

#     best = minmax(0, 0, True, scores, height, -math.inf, math.inf)
#     print(f"Best node to choose is: {best}")

# main()

# def astar(graph, s, g, hur):
#     open_list = [s]
#     g_cost = {i: float('inf') for i in graph}
#     g_cost[s] = 0
#     came_from = {i: None for i in graph}

#     while open_list:
#         current = min(open_list, key=lambda node: g_cost[node] + hur.get(node, 0))

#         if current == g:
#             path = []
#             while current is not None:
#                 path.append(current)
#                 current = came_from[current]
#             path.reverse()
#             print(f"Path form start {s} to goal {g}: {path}")
#             return
        
#         open_list.remove(current)

#         for neighbor in graph[current]:
#             new_cost = g_cost[current] + 1
#             if new_cost <= g_cost[neighbor]:
#                 g_cost[neighbor] = new_cost
#                 came_from[neighbor] = current
#                 if neighbor not in open_list:
#                     open_list.append(neighbor)
        
#     print(f"No valid path to the goal {g}")
#     return

# def main():
#     n, e = map(int, input("Enter the number of nodes and edges: ").split())
#     hur = {}
#     graph = {i+1: [] for i in range(n)}

#     for i in range(e):
#         u, v, h = map(int, input("Enter the U, V, H values: ").split())
#         graph[u].append(v)
#         graph[v].append(u)
#         hur[u] = h
#         hur[v] = hur.get(v, 0)

#     s, g = map(int, input("Enter start and goal nodes: ").split())

#     astar(graph, s, g, hur)

# main()

from pgmpy.models import DiscreteBayesianNetwork
from pgmpy.factors.discrete import TabularCPD
from pgmpy.inference import VariableElimination

model = DiscreteBayesianNetwork([
    ('Flu', 'Fever'),
    ('Flu', 'Cough'),
    ('Allergy', "Cough")
])

flu_cpd = TabularCPD('Flu', 2, [[0.9], [0.1]])
allergy_cpd = TabularCPD("Allergy", 2, [[0.7], [0.3]])

fever_cpd = TabularCPD(
    variable="Fever", variable_card=2,
    values=[[0.95, 0.2],  # P(Fever = 0 | Flu)
            [0.05, 0.8]], # P(Fever = 1 | Flu)
    evidence=['Flu'], evidence_card=[2]
)

cough_cpd = TabularCPD(
    variable="Cough", variable_card=2,
    values=[
        [0.99, 0.4, 0.5, 0.01],  # Cough = 0
        [0.01, 0.6, 0.5, 0.99]   # Cough = 1
    ],
    evidence=['Flu', 'Allergy'],
    evidence_card=[2, 2]
)

model.add_cpds(flu_cpd, fever_cpd, allergy_cpd, cough_cpd)
print(f"Model is ready: {model.check_model()}")

infer = VariableElimination(model)

result1 = infer.query(variables=["Flu"], evidence={'Fever': 1, 'Cough': 1})
print("P(FLU | Fever=1, Cough=1)")
print(result1)

result2 = infer.query(variables=['Allergy'], evidence={'Cough': 1})
print("\nP(Allergy | Cough=1)")
print(result2)