#Сравнить интенсивности выборочных и теоретических интенсивностей потоков.
import numpy as np

# Функция для генерации пуассоновского потока
def generate_poisson_process(lmbda, T1, T2):
    events = []
    t = T1
    while t < T2:
        # Генерация времени межсобытийного интервала
        inter_event_time = np.random.exponential(1 / lmbda)
        t += inter_event_time
        if t < T2:
            events.append(t)
    return np.array(events)

# Параметры
N = 14  # номер студента
T1 = N
T2 = N + 100
lambda1 = (N + 8) / (N + 24)
lambda2 = (N + 9) / (N + 25)
interval_length = T2 - T1

# Генерация двух потоков
stream1 = generate_poisson_process(lambda1, T1, T2)
stream2 = generate_poisson_process(lambda2, T1, T2)

# Объединение потоков
total_stream = np.concatenate((stream1, stream2))

# Выборочные интенсивности для каждого потока
lambda1_empirical = len(stream1) / interval_length
lambda2_empirical = len(stream2) / interval_length
lambda_sum_empirical = len(total_stream) / interval_length

# Теоретические значения интенсивностей
lambda1_theoretical = (N + 8) / (N + 24)
lambda2_theoretical = (N + 9) / (N + 25)
lambda_sum_theoretical = lambda1_theoretical + lambda2_theoretical

# Вывод результатов
print(f"Теоретическая интенсивность потока 1: {lambda1_theoretical}")
print(f"Выборочная интенсивность потока 1: {lambda1_empirical}")

print(f"Теоретическая интенсивность потока 2: {lambda2_theoretical}")
print(f"Выборочная интенсивность потока 2: {lambda2_empirical}")

print(f"Теоретическая интенсивность суммарного потока: {lambda_sum_theoretical}")
print(f"Выборочная интенсивность суммарного потока: {lambda_sum_empirical}")
