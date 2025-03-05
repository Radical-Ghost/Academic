from collections import deque

class Graph:
    def __init__(self):
        self.graph = {}

    def add_edge(self, node1, node2):
        if node1 not in self.graph:
            self.graph[node1] = []

        if node2 not in self.graph:
            self.graph[node2] = []

        self.graph[node1].append(node2)
        self.graph[node2].append(node1)

    def dfs_traversal(self, start_node, visited=None):
        if visited is None:
            visited = set()

        visited.add(start_node)

        path = [start_node]

        for neighbor in self.graph.get(start_node, []):
            if neighbor not in visited:
                path.extend(self.dfs_traversal(neighbor, visited))
            
        return path
    
    def bfs_traversal(self, start_node, visited=None):
        visited = set()
        queue = deque([start_node])
        path = []

        while queue:
            node = queue.popleft()
            if node not in visited:
                visited.add(node)
                path.append(node)
                queue.extend(self.graph.get(node, []))
        
        return path

def main():
    graph = Graph()

    num_edges = int(input("Enter the number of edges: "))
    print("Enter edges (node1 node2):")
    for _ in range(num_edges):
        u, v = input().split()
        graph.add_edge(u, v)

    start_node = input("Enter the start node: ")
    choice = int(input("Enter your choice:\n1.DFS\n2.BFS\n"))

    if choice == 1:
        path = graph.dfs_traversal(start_node)
    else: path = graph.bfs_traversal(start_node)
    print(f"\nTraversal Path for {"DFS" if choice == 1 else "BFS"}: {"->".join(path)}")

main()