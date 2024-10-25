import numpy as np
import random
import matplotlib.pyplot as plt
import time

# Целевая функция для оптимизации
def objective_function(x):
    if x == 0:  # Исключаем деление на 0
        return np.inf  # Возвращаем бесконечность для значения x = 0
    return np.cos(x - 0.5) / np.abs(x)  # Основная функция cos(x-0.5)/|x|

# Функция декодирования хромосомы в вещественное значение
def decode_chromosome(chromosome, min_x, max_x):
    decimal_value = int(''.join(map(str, chromosome)), 2)  # Преобразование двоичной хромосомы в целое число
    x = min_x + (max_x - min_x) * decimal_value / (2 ** len(chromosome) - 1)  # Преобразование в диапазон [min_x, max_x]
    return x

# Генерация начальной популяции
def generate_population(pop_size, chromosome_length):
    return [np.random.randint(0, 2, chromosome_length).tolist() for _ in range(pop_size)]  # Случайная генерация популяции хромосом

# Оценка популяции на основе целевой функции
def evaluate_population(population, min_x, max_x):
    return [objective_function(decode_chromosome(chromosome, min_x, max_x)) for chromosome in population]  # Преобразование хромосом в x и оценка

# Выбор родителей для скрещивания с использованием метода рулетки
def select_parents(population, fitness_values):
    min_fitness = min(fitness_values)  # Находим минимальное значение фитнеса
    shifted_fitness_values = [f - min_fitness + 1e-6 for f in fitness_values]  # Смещаем значения фитнеса, чтобы они были положительными
    total_fitness = sum(shifted_fitness_values)  # Сумма всех фитнесов
    probabilities = [f / total_fitness for f in shifted_fitness_values]  # Вероятности выбора родителей пропорциональны значению фитнеса

    # Выбираем двух разных родителей с использованием вероятностного подхода (рулетка)
    parents_indices = np.random.choice(len(population), size=2, p=probabilities, replace=False)
    return population[parents_indices[0]], population[parents_indices[1]]

# Операция скрещивания (кроссинговера)
def crossover(parent1, parent2):
    crossover_point = np.random.randint(1, len(parent1) - 1)  # Выбор случайной точки для разбиения хромосом
    child1 = parent1[:crossover_point] + parent2[crossover_point:]  # Ребенок 1: часть от первого родителя и часть от второго
    child2 = parent2[:crossover_point] + parent1[crossover_point:]  # Ребенок 2: часть от второго родителя и часть от первого
    return child1, child2

# Операция мутации с заданной вероятностью
def mutate(chromosome, mutation_rate):
    return [1 - bit if random.random() < mutation_rate else bit for bit in chromosome]  # Инвертируем бит с вероятностью, равной mutation_rate

# Основной цикл генетического алгоритма
def run_genetic_algorithm(pop_size, chromosome_length, min_x, max_x, generations, mutation_rate, crossover_rate):
    population = generate_population(pop_size, chromosome_length)  # Генерация начальной популяции
    best_solutions = []  # Список для сохранения лучших решений в каждой итерации

    for generation in range(generations):
        fitness_values = evaluate_population(population, min_x, max_x)  # Оценка текущей популяции
        new_population = []  # Новая популяция для следующего поколения

        # Создание нового поколения
        while len(new_population) < pop_size:
            parent1, parent2 = select_parents(population, fitness_values)  # Выбор родителей
            if random.random() < crossover_rate:
                child1, child2 = crossover(parent1, parent2)  # Выполняем кроссинговер
            else:
                child1, child2 = parent1, parent2  # Если кроссинговера нет, дети — это копии родителей
            new_population.extend([mutate(child1, mutation_rate), mutate(child2, mutation_rate)])  # Мутация потомков и добавление их в новую популяцию

        population = new_population[:pop_size]  # Обновление популяции, ограниченной количеством особей

        best_fitness = min(fitness_values)  # Лучший фитнес текущего поколения
        best_index = fitness_values.index(best_fitness)  # Индекс лучшей особи
        best_x = decode_chromosome(population[best_index], min_x, max_x)  # Декодируем хромосому лучшей особи в значение x
        best_solutions.append((best_x, best_fitness))  # Сохраняем лучшее решение

        print(f"Generation {generation + 1}: Best x = {best_x:.4f}, Best fitness = {best_fitness:.4f}")  # Выводим лучшего представителя поколения

    return best_solutions  # Возвращаем список лучших решений за все поколения

# Основные параметры генетического алгоритма
min_x = -10  # Минимальное значение x
max_x = 10  # Максимальное значение x
chromosome_length = 16  # Длина хромосомы (количество бит)
generations = 100  # Количество поколений (итераций)

# Исследование зависимости различных параметров
results = []

for pop_size in [50, 100, 150]:  # Количество особей в популяции
    for mutation_rate in [0.01, 0.05]:  # Вероятность мутации
        for crossover_rate in [0.6, 0.9]:  # Вероятность кроссинговера
            start_time = time.time()  # Начало измерения времени
            best_solutions = run_genetic_algorithm(pop_size, chromosome_length, min_x, max_x, generations,
                                                   mutation_rate, crossover_rate)  # Запуск генетического алгоритма
            end_time = time.time()  # Конец измерения времени
            time_taken = end_time - start_time  # Затраченное время

            best_x, best_fitness = best_solutions[-1]  # Получение последнего (наилучшего) решения
            results.append((pop_size, mutation_rate, crossover_rate, (best_x, best_fitness), time_taken))  # Сохранение результатов

# Вывод результатов экспериментов
for result in results:
    pop_size, mutation_rate, crossover_rate, best_solution, time_taken = result
    best_x, best_fitness = best_solution
    print(f"Population size: {pop_size}, Mutation rate: {mutation_rate}, Crossover rate: {crossover_rate}, "
          f"Time: {time_taken:.2f}s, Best x: {best_x:.4f}, Best fitness: {best_fitness:.4f}")  # Вывод параметров и лучшего решения

# График функции и найденные экстремумы
x_values = np.linspace(-10, 10, 400)  # Диапазон значений x
y_values = [objective_function(x) for x in x_values if x != 0]  # Вычисление значений функции для графика

plt.plot(x_values, y_values, label='f(x) = cos(x-0.5)/|x|')  # Построение графика функции
for _, _, _, best_solution, _ in results:
    best_x, _ = best_solution
    plt.scatter(best_x, objective_function(best_x), color='red')  # Нанесение на график найденных экстремумов

plt.xlabel('x')  # Название оси X
plt.ylabel('f(x)')  # Название оси Y
plt.title('График функции и найденные экстремумы')  # Заголовок графика
plt.axhline(0, color='black', linewidth=0.5, linestyle='--')  # Горизонтальная линия оси
plt.axvline(0, color='black', linewidth=0.5, linestyle='--')  # Вертикальная линия оси
plt.legend()  # Легенда графика
plt.show()  # Показать график