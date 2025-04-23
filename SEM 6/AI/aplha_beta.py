import math

def minmax(depth, node_index, is_max, scores, height, alpha, beta):
    if depth == height:
        return scores[node_index]

    if is_max:
        best = -math.inf
        for i in range(2):
            val = minmax(depth + 1, node_index * 2 + i, False, scores, height, alpha, beta)
            best = max(best, val)
            alpha = max(alpha, best)
            if beta <= alpha:
                break
        return best
    else:
        best = math.inf
        for i in range(2):
            val = minmax(depth + 1, node_index * 2 + i, True, scores, height, alpha, beta)
            best = min(best, val)
            beta = min(beta, best)
            if beta <= alpha:
                break
        return best

def main():
    print("Welcome to Min-Max with Alpha-Beta Pruning")

    while True:
        try:
            n = int(input("Enter number of leaf nodes (power of 2): "))
            if n > 0 and (n & (n - 1)) == 0:
                break
            else:
                print("Please enter a valid power of 2.")
        except ValueError:
            print("Invalid input. Please enter an integer.")

    scores = []
    print(f"Enter {n} leaf node values (integer scores):")
    for i in range(n):
        val = int(input(f"Leaf {i + 1}: "))
        scores.append(val)

    height = int(math.log2(n))
    optimal_value = minmax(0, 0, True, scores, height, -math.inf, math.inf)
    print("The optimal value is:", optimal_value)

main()