#Запрограммировать предложенный алгоритм генерации пуассоновского потока
#данные для визуализации потоков
#проверки гипотезы о суммарном потоке
import numpy as np
import matplotlib.pyplot as plt

# Параметры задачи
N = 14  # номер студента
T1 = N
T2 = N + 100
lambda1 = (N + 8) / (N + 24)
lambda2 = (N + 9) / (N + 25)

# Генерация пуассоновского потока
def generate_poisson_process(lambda_param, T1, T2):
    times = []  # Массив моментов времени событий
    t = T1
    while t < T2:
        U = np.random.rand()  # Генерируем случайное число U из (0, 1)
        t += -np.log(U) / lambda_param  # Экспоненциальное распределение
        if t < T2:
            times.append(t)
    return times

# Генерация двух потоков
times1 = generate_poisson_process(lambda1, T1, T2)
times2 = generate_poisson_process(lambda2, T1, T2)

# Вывод результатов
print(f"Поток 1: {len(times1)} событий, моменты: {times1}")
print(f"Поток 2: {len(times2)} событий, моменты: {times2}")
