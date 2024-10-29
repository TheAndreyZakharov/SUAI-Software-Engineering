import numpy as np
import matplotlib.pyplot as plt
import time

# Функция Эасома
def fEaso(x):
    return -np.cos(x[0]) * np.cos(x[1]) * np.exp(-((x[0] - np.pi) ** 2 + (x[1] - np.pi) ** 2))

# Параметры PSO
population_size = 100          # Количество частиц
max_iterations = 100           # Максимальное количество итераций
w = 0.5                         # Коэффициент инерции
c1 = 1.5                        # Коэффициент когнитивной компоненты (личный опыт)
c2 = 1.5                        # Коэффициент социальной компоненты (опыт группы)
x_min, x_max = 0, 2 * np.pi     # Диапазон для x1 и x2

# Инициализация частиц
particles = np.random.uniform(x_min, x_max, (population_size, 2))
velocities = np.random.uniform(-1, 1, (population_size, 2))

# Инициализация лучшей позиции для каждой частицы и глобальной лучшей позиции
personal_best_positions = np.copy(particles)
personal_best_scores = np.array([fEaso(p) for p in particles])
global_best_position = particles[np.argmin(personal_best_scores)]
global_best_score = np.min(personal_best_scores)

# Построение графика
x1 = np.linspace(x_min, x_max, 200)
x2 = np.linspace(x_min, x_max, 200)
x1, x2 = np.meshgrid(x1, x2)
z = fEaso([x1, x2])

fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')

# Перерисовка поверхности функции
surf = ax.plot_surface(x1, x2, z, cmap='viridis', edgecolor='none')

# Установка пределов осей и стиля
ax.set_xlim([x_min, x_max])
ax.set_ylim([x_min, x_max])
ax.set_zlim([-1.5, 0.5])
ax.view_init(elev=30, azim=240)
ax.set_title('Оптимизация функции Эасома с помощью PSO', fontsize=16)
ax.set_xlabel('x1', fontsize=14)
ax.set_ylabel('x2', fontsize=14)
ax.set_zlabel('f(x1, x2)', fontsize=14)

# Основной цикл PSO
for iteration in range(max_iterations):
    # Обновление позиций и скоростей частиц
    for i in range(population_size):
        # Когнитивная и социальная компоненты
        cognitive_component = c1 * np.random.rand() * (personal_best_positions[i] - particles[i])
        social_component = c2 * np.random.rand() * (global_best_position - particles[i])
        
        # Обновление скорости
        velocities[i] = w * velocities[i] + cognitive_component + social_component
        particles[i] += velocities[i]  # Обновление позиции
        
        # Ограничение позиций частиц
        particles[i] = np.clip(particles[i], x_min, x_max)

        # Оценка новой позиции
        fitness = fEaso(particles[i])

        # Обновление лучшего личного результата
        if fitness < personal_best_scores[i]:
            personal_best_scores[i] = fitness
            personal_best_positions[i] = particles[i]

    # Обновление глобального лучшего результата
    current_best_index = np.argmin(personal_best_scores)
    if personal_best_scores[current_best_index] < global_best_score:
        global_best_score = personal_best_scores[current_best_index]
        global_best_position = personal_best_positions[current_best_index]

    # Визуализация текущих позиций частиц
    ax.scatter(particles[:, 0], particles[:, 1], [fEaso(p) for p in particles], color='blue', alpha=0.2)

    plt.pause(0.1)

# Отображение найденного экстремума
ax.scatter(global_best_position[0], global_best_position[1], global_best_score, color='red', s=100, label='Найденный минимум (PSO)')
ax.scatter(np.pi, np.pi, -1, color='green', s=100, label='Известный минимум')

ax.legend(loc='upper right')
plt.show()

print(f'Лучшее найденное решение (PSO): x1 = {global_best_position[0]:.6f}, x2 = {global_best_position[1]:.6f}')
print(f'Значение функции в этой точке (PSO): {global_best_score:.6f}')
print(f'Известный оптимум: f(x1, x2) = -1 при (x1, x2) = (pi, pi)')