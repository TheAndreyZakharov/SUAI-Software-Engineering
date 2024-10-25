import numpy as np
import random
import matplotlib.pyplot as plt
import scipy.optimize as opt

# Определяем целевую функцию для минимизации
def objective_function(x):
    if x == 0:  # Исключаем деление на 0
        return np.inf
    return np.cos(x - 0.5) / np.abs(x)

# Декодируем хромосому (битовую строку) в действительное число x
def decode_chromosome(chromosome, min_x, max_x):
    decimal_value = int(''.join(map(str, chromosome)), 2)  # Преобразуем битовую строку в целое число
    x = min_x + (max_x - min_x) * decimal_value / (2 ** len(chromosome) - 1)  # Масштабируем в пределах [min_x, max_x]
    return x

# Генерируем начальную популяцию заданного размера с хромосомами определенной длины
def generate_population(pop_size, chromosome_length):
    return [np.random.randint(0, 2, chromosome_length).tolist() for _ in range(pop_size)]  # Генерация случайных битовых строк

# Оцениваем популяцию путем вычисления значений целевой функции для каждой хромосомы
def evaluate_population(population, min_x, max_x):
    return [objective_function(decode_chromosome(chromosome, min_x, max_x)) for chromosome in population]

# Выбираем двух родителей на основе их приспособленности (фитнеса)
def select_parents(population, fitness_values):
    min_fitness = min(fitness_values)  # Находим минимальное значение фитнеса
    shifted_fitness_values = [f - min_fitness + 1e-6 for f in fitness_values]  # Смещаем фитнес, чтобы избежать отрицательных значений
    total_fitness = sum(shifted_fitness_values)  # Сумма всех фитнесов
    probabilities = [f / total_fitness for f in shifted_fitness_values]  # Вероятности выбора родителей на основе фитнеса

    # Случайно выбираем двух родителей с вероятностью, пропорциональной их фитнесу
    parents_indices = np.random.choice(len(population), size=2, p=probabilities, replace=False)
    return population[parents_indices[0]], population[parents_indices[1]]

# Кроссовер между двумя родителями: создаем потомков, обмениваясь частями хромосом
def crossover(parent1, parent2):
    crossover_point = np.random.randint(1, len(parent1) - 1)  # Точка кроссовера
    child1 = parent1[:crossover_point] + parent2[crossover_point:]  # Первый потомок
    child2 = parent2[:crossover_point] + parent1[crossover_point:]  # Второй потомок
    return child1, child2

# Мутация хромосомы: с вероятностью mutation_rate инвертируем бит
def mutate(chromosome, mutation_rate):
    return [1 - bit if random.random() < mutation_rate else bit for bit in chromosome]

# Основной цикл работы генетического алгоритма
def run_genetic_algorithm(pop_size, chromosome_length, min_x, max_x, generations, mutation_rate, crossover_rate):
    population = generate_population(pop_size, chromosome_length)  # Генерация начальной популяции
    best_solutions = []  # Хранение лучших решений в каждом поколении
    global_best_solution = None  # Глобальное лучшее решение
    global_best_fitness = np.inf  # Инициализация глобального лучшего fitness

    # Основной цикл по поколениям
    for generation in range(generations):
        fitness_values = evaluate_population(population, min_x, max_x)  # Оценка текущей популяции
        new_population = []

        # Создаем новое поколение путем селекции, кроссовера и мутации
        while len(new_population) < pop_size:
            parent1, parent2 = select_parents(population, fitness_values)  # Селекция
            if random.random() < crossover_rate:  # Кроссовер с определенной вероятностью
                child1, child2 = crossover(parent1, parent2)
            else:
                child1, child2 = parent1, parent2
            new_population.extend([mutate(child1, mutation_rate), mutate(child2, mutation_rate)])  # Мутация

        population = new_population[:pop_size]  # Обновляем популяцию

        best_fitness = min(fitness_values)  # Находим лучший фитнес в поколении
        best_index = fitness_values.index(best_fitness)  # Индекс лучшей хромосомы
        best_x = decode_chromosome(population[best_index], min_x, max_x)  # Декодируем лучшую хромосому
        best_solutions.append((best_x, best_fitness))  # Сохраняем лучшее решение

        # Обновляем глобальное лучшее решение
        if best_fitness < global_best_fitness:
            global_best_fitness = best_fitness
            global_best_solution = best_x

        print(f"Generation {generation + 1}: Best x = {best_x:.4f}, Best fitness = {best_fitness:.4f}")

    # Выводим глобально лучшее решение по завершению всех поколений
    print(f"\nGlobal Best Solution after {generations} generations: Best x = {global_best_solution:.4f}, Best fitness = {global_best_fitness:.4f}")

    # Выводим значение функции для лучшего решения
    best_fitness_value = objective_function(global_best_solution)
    print(f"Function value at the best x = {global_best_solution:.4f}: f(x) = {best_fitness_value:.4f}")

    return best_solutions  # Возвращаем лучшие решения для последующего анализа

# Основные параметры генетического алгоритма
min_x = -10
max_x = 10
chromosome_length = 16
generations = 100

# Запуск алгоритма с фиксированными параметрами для построения графика
pop_size = 100
mutation_rate = 0.01
crossover_rate = 0.9

best_solutions = run_genetic_algorithm(pop_size, chromosome_length, min_x, max_x, generations, mutation_rate,
                                       crossover_rate)

# График функции
x_values = np.linspace(-10, 10, 400)  # Генерируем x-значения для построения графика
y_values = [objective_function(x) for x in x_values if x != 0]  # Вычисляем значения функции для каждого x

# Построение графика функции и найденных экстремумов
plt.plot(x_values, y_values, label='f(x) = cos(x-0.5)/|x|')
for best_x, _ in best_solutions:
    plt.scatter(best_x, objective_function(best_x), color='red')  # Отмечаем найденные экстремумы на графике

plt.xlabel('x')
plt.ylabel('f(x)')
plt.title('График функции и найденные экстремумы')
plt.axhline(0, color='black', linewidth=0.5, linestyle='--')  # Добавляем горизонтальную линию y = 0
plt.axvline(0, color='black', linewidth=0.5, linestyle='--')  # Добавляем вертикальную линию x = 0
plt.legend()  # Отображаем легенду
plt.show()

# Определение функции для оптимизации
def f(x):
    return np.cos(x - 0.5) / np.abs(x)

# Задаем ограничения: x ∈ [-10, -1e-5) ∪ (1e-5, 10]
bounds = [(-10, -1e-5), (1e-5, 10)]

# Поиск минимума с использованием метода границ
result = opt.minimize_scalar(f, bounds=(-10, 10), method='bounded')

# Выводим результат
print("Минимум найден в точке x =", result.x)
print("Значение функции f(x) =", result.fun)