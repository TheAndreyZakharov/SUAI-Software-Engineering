import numpy as np
import matplotlib.pyplot as plt
import time

# Параметры PSO
population_size = 500          # Количество частиц
max_iterations = 500           # Максимальное количество итераций
w = 0.5                         # Коэффициент инерции
c1 = 1.5                        # Коэффициент когнитивной компоненты (личный опыт)
c2 = 1.5                        # Коэффициент социальной компоненты (опыт группы)
x_min, x_max = 0, 2 * np.pi     # Диапазон для переменных

# Функция Эасома для n-мерного случая
def fEaso(x):
    return -np.prod(np.cos(x)) * np.exp(-np.sum((x - np.pi) ** 2))

# Добавление функции для улучшения инициализации частиц
def initialize_particles(n):
    return np.random.uniform(x_min, x_max, (population_size, n))

def run_pso(n):
    # Инициализация частиц и их скоростей
    particles = initialize_particles(n)  # Используйте новую инициализацию
    velocities = np.random.uniform(-1, 1, (population_size, n))
    
    # Инициализация лучших позиций
    personal_best_positions = np.copy(particles)
    personal_best_scores = np.array([fEaso(p) for p in particles])
    global_best_position = particles[np.argmin(personal_best_scores)]
    global_best_score = np.min(personal_best_scores)

    start_time = time.time()
    
    # Основной цикл PSO
    for iteration in range(max_iterations):
        for i in range(population_size):
            cognitive_component = c1 * np.random.rand() * (personal_best_positions[i] - particles[i])
            social_component = c2 * np.random.rand() * (global_best_position - particles[i])
            velocities[i] = w * velocities[i] + cognitive_component + social_component
            particles[i] += velocities[i]
            particles[i] = np.clip(particles[i], x_min, x_max)

            fitness = fEaso(particles[i])
            if fitness < personal_best_scores[i]:
                personal_best_scores[i] = fitness
                personal_best_positions[i] = particles[i]

        current_best_index = np.argmin(personal_best_scores)
        if personal_best_scores[current_best_index] < global_best_score:
            global_best_score = personal_best_scores[current_best_index]
            global_best_position = personal_best_positions[current_best_index]
    
    execution_time = time.time() - start_time

    print(f"Для n = {n}:")
    print(f"Лучшее найденное решение: {global_best_position}")
    print(f"Значение функции в этой точке: {global_best_score:.6f}")
    print(f"Время выполнения: {execution_time:.4f} секунд\n")
    return global_best_position, global_best_score, execution_time

# Запуск для различных значений n
results = {}
for n in [2, 4, 6, 10]:
    results[n] = run_pso(n)