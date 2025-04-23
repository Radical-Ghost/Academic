import math

def minmax(depth, node_index, is_max, scores, height):
    if depth == height:
        return scores[node_index]
    
    if is_max:
        return max(
            minmax(depth + 1, node_index * 2, False, scores, height),
            minmax(depth + 1, node_index * 2 + 1, False, scores, height)
        )
    else:
        return min(
            minmax(depth + 1, node_index * 2, True, scores, height),
            minmax(depth + 1, node_index * 2 + 1, True, scores, height)
        )

def main():
    n = int(input("Enter number of leaf nodes (power of 2): "))
    scores = []

    print(f"Enter {n} leaf node values (integer scores):")
    for i in range(n):
        val = int(input(f"Leaf {i + 1}: "))
        scores.append(val)

    height = int(math.log2(n))
    optimal_value = minmax(0, 0, True, scores, height)
    print("The optimal value is:", optimal_value)

main()