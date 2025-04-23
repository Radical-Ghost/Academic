import random

def fitness(x):
    return x**2

def generate_population(size, x_min, x_max):
    return [random.randint(x_min, x_max) for _ in range(size)]

def select(population):
    a, b = random.sample(population, 2)
    return a if fitness(a) > fitness(b) else b

def crossover(parent1, parent2):
    return (parent1 + parent2) // 2

def mutate(x, x_min, x_max, mutation_rate=0.1):
    if random.random() < mutation_rate:
        return random.randint(x_min, x_max)
    return x

def genetic_algorithm(size=10, generations=20, x_min=0, x_max=31):
    population = generate_population(size, x_min, x_max)
    for gen in range(generations):
        new_population = []
        for _ in range(size):
            p1 = select(population)
            p2 = select(population)
            child = crossover(p1, p2)
            child = mutate(child, x_min, x_max)
            new_population.append(child)
        population = new_population
        best = max(population, key=fitness)
        print(f"Generation {gen+1}: Best = {best}, Fitness = {fitness(best)}")
    return max(population, key=fitness)

best = genetic_algorithm()
print("Best solution found:", best)