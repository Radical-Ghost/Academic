class Graph:
    def __init__(self):
        self.adj_list = {}

    def add_edge(self, parent, left=None, right=None):
        self.adj_list[parent] = (left, right)

    def depth_limited_search(self, start, goal, limit):
        return self.dls_helper(start, goal, limit, set(), [])

    def dls_helper(self, node, goal, limit, visited, path):
        if node is None or node in visited:
            return None
        path.append(node)
        visited.add(node)

        if node == goal:
            return path

        if limit <= 0:
            path.pop()
            visited.remove(node)
            return None

        left, right = self.adj_list.get(node, (None, None))

        for child in [left, right]:
            result = self.dls_helper(child, goal, limit - 1, visited, path)
            if result:
                return result

        path.pop()
        visited.remove(node)
        return None

# User Input
g = Graph()
num_nodes = int(input("Enter number of parent nodes: "))

print("Enter edges (parent left_child right_child) [Use 'None' for missing children]:")
for _ in range(num_nodes):
    parent, left, right = input().split()
    g.add_edge(parent, left if left != "None" else None, right if right != "None" else None)

start = input("Enter start node: ")
goal = input("Enter goal node: ")
depth_limit = int(input("Enter depth limit: "))

result = g.depth_limited_search(start, goal, depth_limit)

if result:
    print("Path Found:", " -> ".join(result))
else:
    print("No path found within depth limit")
