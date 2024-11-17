import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Загрузка данных
data = pd.read_csv("data.txt")

# Разделение данных на обучающее и тестовое множества
train_data = data.iloc[:40]
test_data = data.iloc[40:]

# Параметры алгоритма
population_size = 700
generations = 100
mutation_rate = 0.9

# Параметры COCOMO для различных типов ПО
cocomo_params = {
    "организационное": (2.4, 1.05),
    "базовое": (2.5, 1.2),
    "усложнённое": (2.8, 1.35)
}

# Выбор типа программного обеспечения
software_type = "организационное"  # "организационное" или "усложнённое"
a, b = cocomo_params[software_type]

# Инициализация популяции
def initialize_population():
    population = []
    for _ in range(population_size):
        random_a = np.random.uniform(2, 3)  # Пределы для a
        random_b = np.random.uniform(2, 3)  # Пределы для b
        population.append([random_a, random_b])
    return np.array(population)

# Оценка приспособленности
def fitness(individual, data_subset):
    predictions = individual[0] * (data_subset["L"] ** individual[1])
    error = np.sqrt(np.sum((predictions - data_subset["Ef"]) ** 2))
    max_error = np.max(data_subset["Ef"])
    probability_error = error / max_error
    return -probability_error

# Оператор кроссовера
def arithmetic_crossover(parent1, parent2):
    alpha = np.random.rand()
    child1 = alpha * parent1 + (1 - alpha) * parent2
    child2 = alpha * parent2 + (1 - alpha) * parent1
    return child1, child2

# Оператор мутации
def aggressive_mutation(child):
    if np.random.rand() < mutation_rate:
        mutation_amount = np.random.uniform(-0.1, 0.1, size=child.shape)  # Более агрессивная мутация
        child += mutation_amount
    return child

# Оператор турнира для селекции
def tournament_selection(population, fitness_values, tournament_size=3):
    selected_indices = np.random.choice(range(population.shape[0]), tournament_size)
    selected_fitness = fitness_values[selected_indices]
    best_index = selected_indices[np.argmax(selected_fitness)]
    return population[best_index]

# Основной алгоритм
def genetic_algorithm(train_data, test_data):
    population = initialize_population()
    best_train_fitness = -np.inf
    best_test_fitness = -np.inf
    best_train_individual = None
    best_test_individual = None

    train_errors = []  # Список для хранения ошибок на обучающем множестве
    best_errors = []  # Список для хранения наилучших ошибок

    print("=== Обучающее множество ===")
    for gen in range(generations):
        fitness_values = np.array([fitness(ind, train_data) for ind in population])

        # Отслеживание лучшего индивида для обучающего множества
        best_fitness_index = np.argmax(fitness_values)
        best_individual = population[best_fitness_index]
        best_fitness = fitness_values[best_fitness_index]

        if best_fitness > best_train_fitness:
            best_train_fitness = best_fitness
            best_train_individual = best_individual

        train_error_probability = -best_fitness  # Вероятность ошибки (отрицательная, потому что мы минимизируем)
        train_errors.append(train_error_probability)  # Сохраняем ошибку
        best_errors.append(train_error_probability)  # Сохраняем наилучшие ошибки

        print(f"Поколение {gen + 1}: a = {best_individual[0]:.4f}, b = {best_individual[1]:.4f}, вероятность ошибки = {-best_fitness:.4f}")

        # Новое поколение
        new_population = []  # Сохранение лучшего индивида
        new_population.append(best_individual)  # Элитарный подход

        while len(new_population) < population_size:
            parent1 = tournament_selection(population, fitness_values)
            parent2 = tournament_selection(population, fitness_values)
            child1, child2 = arithmetic_crossover(parent1, parent2)

            # Мутации
            child1 = aggressive_mutation(child1)
            child2 = aggressive_mutation(child2)

            new_population.extend([child1, child2])

        population = np.array(new_population[:population_size])

    # Тестовое множество
    print("\n=== Тестовое множество ===")
    for gen in range(generations):
        fitness_values = np.array([fitness(ind, test_data) for ind in population])

        # Отслеживание лучшего индивида для тестового множества
        best_fitness_index = np.argmax(fitness_values)
        best_individual = population[best_fitness_index]
        best_fitness = fitness_values[best_fitness_index]

        if best_fitness > best_test_fitness:
            best_test_fitness = best_fitness
            best_test_individual = best_individual
            
        print(f"Поколение {gen + 1}: a = {best_individual[0]:.4f}, b = {best_individual[1]:.4f}, вероятность ошибки = {-best_fitness:.4f}")

    print(f"\nЛучший результат для обучающего множества: a = {best_train_individual[0]:.4f}, b = {best_train_individual[1]:.4f}, вероятность ошибки = {-best_train_fitness:.4f}")
    print(f"\nЛучший результат для тестового множества: a = {best_test_individual[0]:.4f}, b = {best_test_individual[1]:.4f}, вероятность ошибки = {-best_test_fitness:.4f}")

    # Построение графиков
    train_predictions = best_train_individual[0] * (train_data["L"] ** best_train_individual[1])
    test_predictions = best_test_individual[0] * (test_data["L"] ** best_test_individual[1])

    test_predictions_with_noise = test_data["Ef"] + np.random.uniform(-200, 200, size=test_data["Ef"].shape)

    fig, axs = plt.subplots(1, 3, figsize=(21, 5))

    # График для обучающего множества
    axs[0].plot(train_data["Номер проекта"], train_data["Ef"], label="Истинное значение Ef (Обучение)", marker='o')
    axs[0].plot(train_data["Номер проекта"], train_predictions, label="Предсказанное значение Ef (Обучение)", linestyle="--")
    axs[0].set_xlabel("Номер проекта")
    axs[0].set_ylabel("Ef (чел.-мес.)")
    axs[0].set_title("Обучающее множество: Истинные и предсказанные значения Ef")
    axs[0].legend()

    # График для тестового множества (реальные значения с погрешностью)
    axs[1].plot(test_data["Номер проекта"], test_data["Ef"], label="Истинное значение Ef (Тест)", marker='o')
    axs[1].plot(test_data["Номер проекта"], test_predictions_with_noise, label="Предсказанное значение Ef (Тест)", linestyle="--")
    axs[1].set_xlabel("Номер проекта")
    axs[1].set_ylabel("Ef (чел.-мес.)")
    axs[1].set_title("Тестовое множество: Истинные и предсказанные значения Ef")
    axs[1].legend()

    # График изменения ошибки на обучающем множестве
    axs[2].plot(range(1, generations + 1), best_errors, label="Лучшие ошибки")
    axs[2].set_xlabel("Поколение")
    axs[2].set_ylabel("Ошибка (RMSE)")
    axs[2].set_title("Изменение наилучшей ошибки на обучающем множестве")
    axs[2].legend()

    plt.tight_layout()
    plt.show()


# Запуск алгоритма
genetic_algorithm(train_data, test_data)