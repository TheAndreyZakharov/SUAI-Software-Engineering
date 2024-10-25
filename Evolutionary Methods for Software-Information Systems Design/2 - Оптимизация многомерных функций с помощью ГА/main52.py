import numpy as np
from scipy.optimize import differential_evolution
import time

# Параметры генетического алгоритма
N = 100  # Размер популяции
generations = 100  # Количество поколений
mutation_rate = 0.05  # Вероятность мутации
crossover_rate = 0.8  # Вероятность кроссинговера

# Диапазон значений x
x_min = -100  # Измененный диапазон
x_max = 100  # Измененный диапазон

# Инициализация начальной популяции (двумерная)
population = (x_max - x_min) * np.random.rand(N, 2) + x_min

# Функция, которую оптимизируем (функция Эасома)
def fitness_function(x):
    return -np.cos(x[:, 0]) * np.cos(x[:, 1]) * np.exp(-((x[:, 0] - np.pi) ** 2 + (x[:, 1] - np.pi) ** 2))

best_fitness_history = np.zeros(generations)
best_solution = population[0, :]
best_fitness = fitness_function(best_solution.reshape(1, -1))

# Начало отсчета времени
start_time = time.time()

def tournament_selection(population, fitness_values):
    idx1, idx2 = np.random.randint(len(population), size=2)
    return population[idx1] if fitness_values[idx1] < fitness_values[idx2] else population[idx2]

def crossover(parent1, parent2):
    alpha = np.random.rand(2)
    child1 = alpha[0] * parent1 + (1 - alpha[0]) * parent2
    child2 = (1 - alpha[1]) * parent1 + alpha[1] * parent2
    return child1, child2

def mutate(individual, mutation_rate, x_min, x_max):
    if np.random.rand() < mutation_rate:
        return (x_max - x_min) * np.random.rand(2) + x_min  # Изменен для 2D
    return individual

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
        parents = np.array([tournament_selection(population, fitness_values) for _ in range(2)])

        # Кроссинговер
        if np.random.rand() < crossover_rate:
            child1, child2 = crossover(parents[0], parents[1])
        else:
            child1, child2 = parents[0], parents[1]

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
print(f'Лучшее найденное решение (мой ГА): ({best_solution[0]}, {best_solution[1]})')
print(f'Значение функции в этой точке (мой ГА): {best_fitness}')
print(f'Время выполнения (мой ГА): {execution_time} секунд')

# Встроенный ГА из SciPy для сравнения
start_time = time.time()
result = differential_evolution(lambda x: -fitness_function(x.reshape(1, -1)),
                                 bounds=[(x_min, x_max), (x_min, x_max)],
                                 maxiter=generations, popsize=N, mutation=(0.5, 1.5), recombination=crossover_rate)
ga_best_solution = result.x
ga_best_fitness = -result.fun  # Знак минус, т.к. мы максимизируем
ga_execution_time = time.time() - start_time

# Вывод результатов для встроенного ГА
print(f'Лучшее найденное решение (встроенный ГА): ({ga_best_solution[0]}, {ga_best_solution[1]})')
print(f'Значение функции в этой точке (встроенный ГА): {ga_best_fitness}')
print(f'Время выполнения (встроенный ГА): {ga_execution_time} секунд')