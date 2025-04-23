import random

def fitness(x):
    return -x**2 + 10*x

def hill_climb():
    current_x = random.uniform(0, 10)
    step_size = 0.1
    max_iterations = 1000

    for _ in range(max_iterations):
        print(current_x)
        next_x = current_x + random.choice([-step_size, step_size])
        next_x = max(0, min(10, next_x))
        
        if fitness(next_x) > fitness(current_x):
            current_x = next_x

    return current_x, fitness(current_x)

x, y = hill_climb()
print(f"Best x: {x:.4f}, f(x): {y:.4f} for -x^2 + 10x")
