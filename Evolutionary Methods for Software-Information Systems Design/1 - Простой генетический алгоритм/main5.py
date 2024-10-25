import numpy as np
import matplotlib.pyplot as plt
import time

# Определение функции
def objective_function(x):
    return np.cos(x - 0.5) / np.abs(x) if x != 0 else float('inf')

# Генетический алгоритм
def genetic_algorithm(population_size, mutation_rate, crossover_rate, generations):
    population = np.random.uniform(-10, 10, population_size)
    best_fitness_history = []

    for generation in range(generations):
        fitness = np.array([objective_function(ind) for ind in population])
        best_fitness = np.min(fitness)
        best_fitness_history.append(best_fitness)

        # Кроссинговер
        for i in range(0, population_size, 2):
            if np.random.rand() < crossover_rate and i + 1 < population_size:
                crossover_point = np.random.rand()
                population[i], population[i + 1] = (
                    population[i] * crossover_point + population[i + 1] * (1 - crossover_point),
                    population[i] * (1 - crossover_point) + population[i + 1] * crossover_point,
                )

        # Мутация
        for i in range(population_size):
            if np.random.rand() < mutation_rate:
                population[i] += np.random.normal()

    best_individual = population[np.argmin([objective_function(ind) for ind in population])]
    return best_individual, objective_function(best_individual), best_fitness_history

# Параметры эксперимента
population_size = 50
mutation_rate = 0.05
generations = 100
p_c_values = np.arange(0.1, 1.0, 0.1)
results = []

# Запуск эксперимента
for p_c in p_c_values:
    start_time = time.time()
    best_individual, best_fitness, fitness_history = genetic_algorithm(population_size, mutation_rate, p_c, generations)
    elapsed_time = time.time() - start_time
    results.append((p_c, best_individual, best_fitness, elapsed_time, len(fitness_history)))

    # Вывод результатов в терминал
    print(f'P_c = {p_c:.1f}: Лучшее x = {best_individual:.4f}, Лучший фитнес = {best_fitness:.4f}, Время = {elapsed_time:.4f} с, Поколений = {len(fitness_history)}')

# Преобразование результатов для графиков
p_c_vals, best_xs, best_fitnesses, times, generations_count = zip(*results)

# Построение графиков
plt.figure(figsize=(15, 10))

# График лучшего значения x
plt.subplot(3, 1, 1)
plt.plot(p_c_vals, best_xs, marker='o')
plt.title('Лучшее значение x в зависимости от P_c')
plt.xlabel('P_c')
plt.ylabel('Лучшее x')

# График лучшего фитнеса
plt.subplot(3, 1, 2)
plt.plot(p_c_vals, best_fitnesses, marker='o', color='orange')
plt.title('Лучший фитнес в зависимости от P_c')
plt.xlabel('P_c')
plt.ylabel('Лучший фитнес')

# График времени выполнения
plt.subplot(3, 1, 3)
plt.plot(p_c_vals, times, marker='o', color='green')
plt.title('Время выполнения в зависимости от P_c')
plt.xlabel('P_c')
plt.ylabel('Время (с)')

plt.tight_layout()
plt.show()