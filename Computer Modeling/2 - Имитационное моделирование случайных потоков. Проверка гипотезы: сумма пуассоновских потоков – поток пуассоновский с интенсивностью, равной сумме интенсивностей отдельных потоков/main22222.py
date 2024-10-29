import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import chisquare
import pandas as pd

# Параметры
N = 14
T1 = N
T2 = N + 100
lambda1 = (N + 8) / (N + 24)
lambda2 = (N + 9) / (N + 25)
lambda_total = lambda1 + lambda2  # Суммарная интенсивность
num_realizations = 100  # Число реализаций
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

# Генерация суммарного потока
combined_streams = [generate_poisson_stream(lambda_total, T1, T2) for _ in range(num_realizations)]

# Графическая интерпретация событий
plt.figure(figsize=(12, 8))
for i in range(num_realizations):
    plt.scatter(combined_streams[i], [i + 1] * len(combined_streams[i]), color='purple', marker='o',
                label='потоки' if i == 0 else "")

plt.title('Суммарный поток событий с интенсивностью λ')
plt.xlabel('Время')
plt.ylabel('Номер реализации')
plt.xticks(np.arange(T1, T2 + 1, 10))
plt.yticks(np.arange(1, num_realizations + 1, 1))
plt.grid()

# Вертикальные линии для интервалов
for i in range(num_intervals + 1):
    plt.axvline(x=T1 + i * delta_t, color='gray', linestyle='--', alpha=0.5)

# Подпись интервалов
for i in range(1, num_intervals + 1):
    plt.text(T1 + (i - 0.5) * delta_t, -1, str(i), horizontalalignment='center')

plt.legend()
plt.show()

# Гистограмма распределения событий по интервалам времени для всех реализаций
plt.figure(figsize=(12, 6))
all_events = np.concatenate(combined_streams)  # Собираем все события в один массив
hist_data, bin_edges, _ = plt.hist(all_events, bins=np.arange(T1, T2 + delta_t, delta_t), color='skyblue', edgecolor='black')

plt.title('Распределение событий по временным интервалам для всех реализаций')
plt.xlabel('Время')
plt.ylabel('Частота событий')
plt.xticks(np.arange(T1, T2 + 1, 10))
plt.grid(True)
plt.show()

# Проверка гипотезы о распределении
alpha = 0.05  # Уровень значимости
num_errors = 0  # Счетчик ошибок

# Проходим по всем реализациям и считаем хи-квадрат для каждой
for i, stream in enumerate(combined_streams):
    observed_counts, _ = np.histogram(stream, bins=np.arange(T1, T2 + delta_t, delta_t))

    # Ожидаемые частоты для данной реализации, на основе средней интенсивности
    expected_counts = np.full(num_intervals, len(stream) / num_intervals)

    try:
        chi2_stat, p_value = chisquare(observed_counts, f_exp=expected_counts)
        print(f'Итерация {i + 1}: Chi-squared statistic: {chi2_stat:.2f}, p-value: {p_value:.4f}')

        if p_value <= alpha:
            num_errors += 1

    except ValueError as e:
        print(f"Ошибка при вычислении критерия хи-квадрат в итерации {i + 1}:", e)

# Подсчет ошибок
error_percentage = (num_errors / num_realizations) * 100

print(f"Количество итераций с p-value <= {alpha}: {num_errors}")
print(f"Процент итераций с p-value <= {alpha}: {error_percentage:.2f}%")

# Сравнение процента ошибок с уровнем значимости
if error_percentage < alpha * 100:
    print(f"Процент ошибок ({error_percentage:.2f}%) меньше уровня значимости ({alpha * 100}%), гипотеза принята.")
else:
    print(f"Процент ошибок ({error_percentage:.2f}%) превышает уровень значимости ({alpha * 100}%), гипотеза отвергнута.")

# Выборочная интенсивность
empirical_lambda_total = np.mean([len(stream) / (T2 - T1) for stream in combined_streams])
print(f'Выборочная интенсивность для суммарного потока: {empirical_lambda_total}')
print(f'Теоретическая интенсивность для суммарного потока: {lambda_total}')