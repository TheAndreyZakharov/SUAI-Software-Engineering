import numpy as np
from scipy.optimize import differential_evolution
import time

# Функции для отбора, кроссинговера и мутации (ваш ГА)
def tournament_selection(population, fitness_values):
    # Турнирный отбор двух особей
    parents = np.zeros((2, 3))  # Определяем, что n = 3
    for i in range(2):
        idx = np.random.randint(len(population))
        parents[i] = population[idx]
    return parents

def crossover(parent1, parent2):
    # Одноточечный кроссинговер
    alpha = np.random.rand(3)  # Определяем, что n = 3
    child1 = alpha * parent1 + (1 - alpha) * parent2
    child2 = (1 - alpha) * parent1 + alpha * parent2
    return child1, child2

def mutate(individual, mutation_rate, x_min, x_max):
    # Мутация с заданной вероятностью
    if np.random.rand() < mutation_rate:
        return (x_max - x_min) * np.random.rand(3) + x_min  # Определяем, что n = 3
    else:
        return individual

# Параметры генетического алгоритма
N = 100  # Размер популяции
generations = 100  # Количество поколений
mutation_rate = 0.05  # Вероятность мутации
crossover_rate = 0.8  # Вероятность кроссинговера

# Диапазон значений x
x_min = -100
x_max = 100

# Инициализация начальной популяции (трехмерная)
population = (x_max - x_min) * np.random.rand(N, 3) + x_min

# Функция Эйзома, которую оптимизируем
def fitness_function(x):
    return -np.cos(x[:, 0]) * np.cos(x[:, 1]) * np.cos(x[:, 2]) * \
           np.exp(-((x[:, 0] - np.pi) ** 2 + (x[:, 1] - np.pi) ** 2 + (x[:, 2] - np.pi) ** 2))

best_fitness_history = np.zeros(generations)
best_solution = population[0, :]
best_fitness = fitness_function(population[0:1])[0]

# Начало отсчета времени
start_time = time.time()

for generation in range(generations):
    # Оценка популяции
    fitness_values = fitness_function(population)

    # Поиск лучшего решения
    current_best_fitness = np.min(fitness_values)
    best_idx = np.argmin(fitness_values)

    if current_best_fitness < best_fitness:
        best_fitness = current_best_fitness
        best_solution = population[best_idx, :]

    # Селекция: турнирный отбор
    new_population = np.copy(population)
    for i in range(0, N, 2):
        parents = tournament_selection(population, fitness_values)

        # Кроссинговер
        if np.random.rand() < crossover_rate:
            child1, child2 = crossover(parents[0], parents[1])
        else:
            child1 = parents[0]
            child2 = parents[1]

        # Мутация
        child1 = mutate(child1, mutation_rate, x_min, x_max)
        child2 = mutate(child2, mutation_rate, x_min, x_max)

        new_population[i] = child1
        new_population[i + 1] = child2

    population = new_population
    best_fitness_history[generation] = best_fitness

# Конец отсчета времени
execution_time = time.time() - start_time

# Вывод результатов для вашего алгоритма
print(f'Лучшее найденное решение (мой ГА): x1 = {best_solution[0]:.6f}, x2 = {best_solution[1]:.6f}, x3 = {best_solution[2]:.6f}')
print(f'Значение функции в этой точке (мой ГА): {best_fitness:.6f}')
print(f'Время выполнения (мой ГА): {execution_time:.6f} секунд')


# Встроенный ГА из SciPy для сравнения
def wrapped_fitness_function(x):
    return fitness_function(np.array([x]))

start_time = time.time()
result = differential_evolution(wrapped_fitness_function, bounds=[(x_min, x_max)] * 3,
                                strategy='best1bin', maxiter=generations, popsize=N,
                                mutation=(0.5, 1), recombination=0.7)
ga_best_solution = result.x
ga_best_fitness = -result.fun  # Знак минус, т.к. мы максимизируем
ga_execution_time = time.time() - start_time

# Вывод результатов для встроенного ГА
print(f'Лучшее найденное решение (встроенный ГА): x1 = {ga_best_solution[0]:.6f}, x2 = {ga_best_solution[1]:.6f}, x3 = {ga_best_solution[2]:.6f}')
print(f'Значение функции в этой точке (встроенный ГА): {ga_best_fitness:.6f}')
print(f'Время выполнения (встроенный ГА): {ga_execution_time:.6f} секунд')