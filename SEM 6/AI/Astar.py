def AStar(graph, s, g, hur):
    open_list = [s]
    g_cost = {node: float('inf') for node in graph}
    g_cost[s] = 0
    came_from = {node: None for node in graph}

    while open_list:
        current = min(open_list, key=lambda node: g_cost[node] + hur.get(node, 0))

        if current == g:
            path = []
            while current is not None:
                path.append(current)
                current = came_from[current]
            path.reverse()
            print(f"path: {path}")
            return

        open_list.remove(current)

        for neighbor in graph[current]:
            new_cost = g_cost[current] + 1
            if new_cost < g_cost[neighbor]:
                g_cost[neighbor] = new_cost
                came_from[neighbor] = current
                if neighbor not in open_list:
                    open_list.append(neighbor)

    print("path not found")
    return    

def main():
    n, e = map(int, input("Enter the number of Nodes and Edges: ").split())

    graph = {i: [] for i in range(n)}
    hur = {}

    for i in range(e):
        u, v, h = map(int, input("U, V, H: ").split())
        graph[u].append(v)
        graph[v].append(u)
        hur[u] = h
        hur[v] = hur.get(v, 0)

    s, g = map(int, input("Enter Source and Goal: ").split())

    AStar(graph, s, g, hur)

main()
