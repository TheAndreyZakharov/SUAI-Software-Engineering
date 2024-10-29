import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import chisquare

# Параметры
N = 14
T1 = N
T2 = N + 100
lambda1 = (N + 8) / (N + 24)
lambda2 = (N + 9) / (N + 25)
num_realizations = 25
num_intervals = 25
delta_t = (T2 - T1) / num_intervals

# Генерация потока событий
def generate_poisson_stream(lam, T1, T2):
    event_times = []
    current_time = T1
    while current_time < T2:
        inter_arrival_time = np.random.exponential(1 / lam)
        current_time += inter_arrival_time
        if current_time < T2:
            event_times.append(current_time)
    return np.array(event_times)

# Генерация потоков
streams1 = [generate_poisson_stream(lambda1, T1, T2) for _ in range(num_realizations)]
streams2 = [generate_poisson_stream(lambda2, T1, T2) for _ in range(num_realizations)]

# Построение суммарного потока
combined_streams = [np.concatenate((s1, s2)) for s1, s2 in zip(streams1, streams2)]
combined_streams = [np.sort(stream) for stream in combined_streams]

# Графическая интерпретация
plt.figure(figsize=(12, 8))
for i in range(num_realizations):
    plt.scatter(streams1[i], [i + 1] * len(streams1[i]), color='blue', marker='o', label='Поток X1' if i == 0 else "")
    plt.scatter(streams2[i], [i + 1 + num_realizations] * len(streams2[i]), color='red', marker='x', label='Поток X2' if i == 0 else "")

plt.title('Потоки событий X1(t) и X2(t)')
plt.xlabel('Время')
plt.ylabel('Номер реализации')
plt.xticks(np.arange(T1, T2 + 1, 10))
plt.yticks(np.arange(1, 2 * num_realizations + 1, 1))
plt.grid()

# Вертикальные линии для интервалов
for i in range(num_intervals + 1):
    plt.axvline(x=T1 + i * delta_t, color='gray', linestyle='--', alpha=0.5)

# Подпись интервалов
for i in range(1, num_intervals + 1):
    plt.text(T1 + (i - 0.5) * delta_t, -1, str(i), horizontalalignment='center')

plt.legend()
plt.show()

# Проверка гипотезы о распределении
total_stream = np.concatenate(combined_streams)
observed_counts, _ = np.histogram(total_stream, bins=np.arange(T1, T2 + delta_t, delta_t))

# Ожидаемые частоты
total_events = sum(len(stream) for stream in combined_streams)  # Общее количество событий
expected_counts = np.full(num_intervals, total_events / num_intervals)

# Отладочные выводы
print("Наблюдаемые частоты:", observed_counts)
print("Ожидаемые частоты:", expected_counts)

# Проверка суммы частот
observed_sum = np.sum(observed_counts)
expected_sum = np.sum(expected_counts)

print(f"Сумма наблюдаемых частот: {observed_sum}")
print(f"Сумма ожидаемых частот: {expected_sum}")

# Критерий хи-квадрат
try:
    chi2_stat, p_value = chisquare(observed_counts, f_exp=expected_counts)
    print(f'Chi-squared statistic: {chi2_stat}, p-value: {p_value}')
except ValueError as e:
    print("Ошибка при вычислении критерия хи-квадрат:", e)

# Выборочные и теоретические интенсивности
empirical_lambda1 = np.mean([len(stream) / (T2 - T1) for stream in streams1])
empirical_lambda2 = np.mean([len(stream) / (T2 - T1) for stream in streams2])
empirical_lambda_total = empirical_lambda1 + empirical_lambda2

print(f'Выборочная интенсивность для λ1: {empirical_lambda1}')
print(f'Выборочная интенсивность для λ2: {empirical_lambda2}')
print(f'Выборочная интенсивность для суммарного потока: {empirical_lambda_total}')

# Теоретические интенсивности
theoretical_lambda1 = lambda1
theoretical_lambda2 = lambda2
theoretical_lambda_total = theoretical_lambda1 + theoretical_lambda2

print(f'Теоретическая интенсивность для λ1: {theoretical_lambda1}')
print(f'Теоретическая интенсивность для λ2: {theoretical_lambda2}')
print(f'Теоретическая интенсивность для суммарного потока: {theoretical_lambda_total}')