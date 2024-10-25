import numpy as np
import random
import matplotlib.pyplot as plt


# Функция, которую необходимо минимизировать
def objective_function(x):
    if x == 0:  # Исключаем деление на 0
        return np.inf
    return np.cos(x - 0.5) / np.abs(x)


# Декодирование хромосомы в число x
def decode_chromosome(chromosome, min_x, max_x):
    decimal_value = int(''.join(map(str, chromosome)), 2)
    x = min_x + (max_x - min_x) * decimal_value / (2 ** len(chromosome) - 1)
    return x


# Генерация начальной популяции
def generate_population(pop_size, chromosome_length):
    return [np.random.randint(0, 2, chromosome_length).tolist() for _ in range(pop_size)]


# Оценка пригодности (fitness) для каждого индивида
def evaluate_population(population, min_x, max_x):
    fitness_values = []
    for chromosome in population:
        x = decode_chromosome(chromosome, min_x, max_x)
        fitness = objective_function(x)
        fitness_values.append(fitness)
    return fitness_values


# Отбор (рулетка)
def select_parents(population, fitness_values):
    # Смещаем фитнес значения, чтобы они все были положительными
    min_fitness = min(fitness_values)
    shifted_fitness_values = [f - min_fitness + 1e-6 for f in fitness_values]  # добавляем небольшое значение, чтобы избежать нуля
    total_fitness = sum(shifted_fitness_values)
    probabilities = [f / total_fitness for f in shifted_fitness_values]
    parents_indices = np.random.choice(len(population), size=2, p=probabilities)
    return population[parents_indices[0]], population[parents_indices[1]]


# Скрещивание (однородный кроссовер)
def crossover(parent1, parent2):
    crossover_point = np.random.randint(1, len(parent1) - 1)
    child1 = parent1[:crossover_point] + parent2[crossover_point:]
    child2 = parent2[:crossover_point] + parent1[crossover_point:]
    return child1, child2


# Мутация
def mutate(chromosome, mutation_rate):
    for i in range(len(chromosome)):
        if random.random() < mutation_rate:
            chromosome[i] = 1 - chromosome[i]  # Инвертируем бит
    return chromosome


# Основные параметры
pop_size = 100  # количество особей в популяции
chromosome_length = 16  # длина хромосомы
min_x = -10  # минимальное значение x
max_x = 10  # максимальное значение x
generations = 100  # количество поколений
mutation_rate = 0.01  # вероятность мутации

# Генерация начальной популяции
population = generate_population(pop_size, chromosome_length)

# Цикл по поколениям
for generation in range(generations):
    fitness_values = evaluate_population(population, min_x, max_x)

    new_population = []

    # Создание нового поколения
    while len(new_population) < pop_size:
        parent1, parent2 = select_parents(population, fitness_values)
        child1, child2 = crossover(parent1, parent2)
        child1 = mutate(child1, mutation_rate)
        child2 = mutate(child2, mutation_rate)
        new_population.extend([child1, child2])

    population = new_population[:pop_size]

    # Выводим лучшие результаты для текущего поколения
    best_fitness = min(fitness_values)
    best_index = fitness_values.index(best_fitness)
    best_x = decode_chromosome(population[best_index], min_x, max_x)

    print(f"Generation {generation + 1}: Best x = {best_x:.4f}, Best fitness = {best_fitness:.4f}")

# Финальный результат
best_fitness = min(fitness_values)
best_index = fitness_values.index(best_fitness)
best_x = decode_chromosome(population[best_index], min_x, max_x)

print(f"Best solution found: x = {best_x:.4f}, fitness = {best_fitness:.4f}")