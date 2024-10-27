import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial.distance import cdist

# --- Настройки алгоритма ---
FILENAME = "berlin52.txt"       # Имя файла с координатами городов
N_ANTS = 100                     # Количество муравьев
N_ITERATIONS = 200              # Количество поколений
ALPHA = 1                       # Влияние феромона на выбор пути
BETA = 7                        # Влияние расстояния на выбор пути
EVAPORATION_RATE = 0.1          # Коэффициент испарения феромона
PHEROMONE_CONSTANT = 300        # Константа феромона для маршрутов

# --- Шаг 1: Загрузка данных ---
def load_coordinates(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
    coords = np.array([list(map(float, line.strip().split()[1:])) for line in lines if line.strip() != "EOF"])
    return coords

# --- Шаг 2: Вычисление матрицы расстояний ---
def calculate_distance_matrix(coords):
    return cdist(coords, coords, metric='euclidean')

# --- Шаг 3: Реализация муравьиного алгоритма ---
def ant_colony_optimization(coords, dist_matrix, n_ants, n_iterations, alpha, beta, evaporation_rate, pheromone_constant):
    n_cities = len(dist_matrix)
    pheromone = np.ones((n_cities, n_cities))  # начальные феромоны
    best_route = None
    best_distance = float('inf')
    all_best_routes = []  # Хранение лучших маршрутов каждого поколения
    
    for iteration in range(n_iterations):
        routes = []
        route_lengths = []
        
        for ant in range(n_ants):
            visited = np.zeros(n_cities, dtype=bool)
            current_city = np.random.randint(0, n_cities)
            route = [current_city]
            visited[current_city] = True
            total_distance = 0
            
            while len(route) < n_cities:
                probabilities = calculate_transition_probabilities(current_city, visited, pheromone, dist_matrix, alpha, beta)
                next_city = np.random.choice(range(n_cities), p=probabilities)
                route.append(next_city)
                total_distance += dist_matrix[current_city, next_city]
                current_city = next_city
                visited[current_city] = True
            
            # Замкнуть маршрут
            total_distance += dist_matrix[route[-1], route[0]]
            route_lengths.append(total_distance)
            routes.append(route)
        
        # Обновление феромонов
        pheromone *= (1 - evaporation_rate)
        for i, route in enumerate(routes):
            for j in range(n_cities - 1):
                pheromone[route[j], route[j+1]] += pheromone_constant / route_lengths[i]
        
        # Поиск лучшего маршрута
        min_length = min(route_lengths)
        if min_length < best_distance:
            best_distance = min_length
            best_route = routes[route_lengths.index(min_length)]
        
        # Добавляем лучший маршрут текущего поколения
        all_best_routes.append((best_route, best_distance))
    
    return best_route, best_distance, all_best_routes

# --- Шаг 4: Вероятности переходов между городами ---
def calculate_transition_probabilities(current_city, visited, pheromone, dist_matrix, alpha, beta):
    probabilities = []
    for j in range(len(visited)):
        if visited[j]:
            probabilities.append(0)
        else:
            pheromone_level = pheromone[current_city, j] ** alpha
            visibility = (1 / dist_matrix[current_city, j]) ** beta
            probabilities.append(pheromone_level * visibility)
    probabilities = probabilities / np.sum(probabilities)
    return probabilities

# --- Шаг 5: Визуализация маршрутов ---
def visualize_routes(coords, all_best_routes, final_best_route, optimal_route):
    fig, axes = plt.subplots(1, 4, figsize=(24, 6))  # Добавляем четвертую ось
    
    # Левый график - лучшие маршруты каждого поколения
    for i, (route, distance) in enumerate(all_best_routes):
        route_coords = coords[route + [route[0]]]  # замыкаем маршрут
        axes[0].plot(route_coords[:, 0], route_coords[:, 1], marker='o', linestyle='-', label=f"Gen {i+1}")
    axes[0].set_title("Лучшие маршруты по поколениям")
    axes[0].set_xlabel("X")
    axes[0].set_ylabel("Y")
    
    # Средний график - лучший маршрут среди всех
    final_route_coords = coords[final_best_route + [final_best_route[0]]]  # замыкаем маршрут
    axes[1].plot(final_route_coords[:, 0], final_route_coords[:, 1], marker='o', color='red', linestyle='-')
    axes[1].set_title("Лучший маршрут среди всех поколений")
    axes[1].set_xlabel("X")
    axes[1].set_ylabel("Y")
    
    # Правый график - оптимальный маршрут из условия задачи
    optimal_route_coords = coords[optimal_route + [optimal_route[0]]]  # замыкаем маршрут
    axes[2].plot(optimal_route_coords[:, 0], optimal_route_coords[:, 1], marker='o', color='blue', linestyle='-')
    axes[2].set_title("Оптимальный маршрут из условия задачи")
    axes[2].set_xlabel("X")
    axes[2].set_ylabel("Y")
    
    # Четвертый график - лучший найденный путь по гамильтонову пути (без замыкания)
    best_hamiltonian_route_coords = coords[final_best_route]  # Убираем замыкание маршрута
    axes[3].plot(best_hamiltonian_route_coords[:, 0], best_hamiltonian_route_coords[:, 1], marker='o', color='green', linestyle='-')
    axes[3].set_title("Лучший найденный гамильтонов путь")
    axes[3].set_xlabel("X")
    axes[3].set_ylabel("Y")
    
    plt.tight_layout()
    plt.show()

# Дополнительно: Вычисление длины оптимального маршрута
def calculate_optimal_route_distance(optimal_route, dist_matrix):
    distance = sum(dist_matrix[optimal_route[i], optimal_route[i+1]] for i in range(len(optimal_route) - 1))
    distance += dist_matrix[optimal_route[-1], optimal_route[0]]  # замыкаем маршрут
    return distance

# Загрузка данных и запуск алгоритма
coordinates = load_coordinates(FILENAME)
distance_matrix = calculate_distance_matrix(coordinates)
best_route, best_distance, all_best_routes = ant_colony_optimization(
    coordinates, distance_matrix, N_ANTS, N_ITERATIONS, ALPHA, BETA, EVAPORATION_RATE, PHEROMONE_CONSTANT
)

OPTIMAL_ROUTE = [0, 48, 31, 44, 18, 40, 7, 8, 9, 42, 32, 50, 10, 51, 13, 12, 46, 25, 26, 27, 11, 24, 3, 5, 14, 4, 23, 47, 37, 36, 39, 38, 35, 34, 33, 43, 45, 15, 28, 49, 19, 22, 29, 1, 6, 41, 20, 16, 2, 17, 30, 21]  # Оптимальный маршрут

# Визуализация и вывод результатов
optimal_distance = calculate_optimal_route_distance(OPTIMAL_ROUTE, distance_matrix)
visualize_routes(coordinates, all_best_routes, best_route, OPTIMAL_ROUTE)

print("Лучший маршрут, найденный алгоритмом:", best_route)
print("Длина найденного маршрута:", best_distance)
print("Оптимальный маршрут из условия:", OPTIMAL_ROUTE)
print("Длина оптимального маршрута:", optimal_distance)