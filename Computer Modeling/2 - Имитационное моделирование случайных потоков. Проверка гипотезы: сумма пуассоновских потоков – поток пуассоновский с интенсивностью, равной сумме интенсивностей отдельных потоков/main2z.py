import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import chisquare, chi2
import pandas as pd

# Параметры
N = 14
T1 = N
T2 = N + 100
lambda1 = (N + 8) / (N + 24)
lambda2 = (N + 9) / (N + 25)
lambda_total = lambda1 + lambda2  # Суммарная интенсивность
num_realizations = 50  # Число реализаций (по 25 для каждого потока)
num_intervals = 25
delta_t = (T2 - T1) / num_intervals
alpha = 0.05  # Уровень значимости
num_errors = 0  # Счётчик ошибок

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

# Генерация потоков для λ1 и λ2
streams_lambda1 = [generate_poisson_stream(lambda1, T1, T2) for _ in range(25)]
streams_lambda2 = [generate_poisson_stream(lambda2, T1, T2) for _ in range(25)]

# Объединение потоков
combined_streams = [np.concatenate((streams_lambda1[i], streams_lambda2[i])) for i in range(25)]

# Графическая интерпретация - первое окно с потоками λ1 и λ2
plt.figure(figsize=(12, 8))

# Вывод потоков для λ1
for i in range(25):
    plt.scatter(streams_lambda1[i], [i + 1] * len(streams_lambda1[i]), color='red', marker='o',
                label='λ1 потоки' if i == 0 else "")

# Вывод потоков для λ2
for i in range(25):
    plt.scatter(streams_lambda2[i], [25 + i + 1] * len(streams_lambda2[i]), color='blue', marker='o',
                label='λ2 потоки' if i == 0 else "")

# Вывод суммарных потоков
for i in range(25):
    plt.scatter(combined_streams[i], [50 + i + 1] * len(combined_streams[i]), color='gray', marker='o',
                label='Суммарный поток' if i == 0 else "")

plt.title('Потоки событий для λ1, λ2 и суммарного потока')
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

# Объединяем события из всех потоков
all_combined_events = np.concatenate(combined_streams)

# Создание второго окна для отображения всех событий на разных горизонтальных линиях
plt.figure(figsize=(12, 6))

# Объединяем события для λ1
all_lambda1_events = np.concatenate(streams_lambda1)
plt.scatter(all_lambda1_events, [1] * len(all_lambda1_events), color='red', marker='o', label='Объединённый поток λ1')

# Объединяем события для λ2
all_lambda2_events = np.concatenate(streams_lambda2)
plt.scatter(all_lambda2_events, [2] * len(all_lambda2_events), color='blue', marker='o', label='Объединённый поток λ2')

# Теперь используем all_combined_events
plt.scatter(all_combined_events, [3] * len(all_combined_events), color='grey', marker='o', label='Суммарный поток')

plt.title('События для λ1, λ2 и суммарного потока на разных линиях')
plt.xlabel('Время')
plt.ylabel('Потоки')
plt.xticks(np.arange(T1, T2 + 1, 10))
plt.yticks([1, 2, 3], ['Объединённый поток λ1', 'Объединённый поток λ2', 'Суммарный поток'])
plt.grid()

# Вертикальные линии для интервалов
for i in range(num_intervals + 1):
    plt.axvline(x=T1 + i * delta_t, color='gray', linestyle='--', alpha=0.5)

 # Подпись интервалов
for i in range(1, num_intervals + 1):
    plt.text(T1 + (i - 0.5) * delta_t, 0.95, str(i), horizontalalignment='center', verticalalignment='bottom', fontsize=10)


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
    print(f'Хи-квадрат практич. χ²: {chi2_stat}, p-value: {p_value}')

    # Проверка гипотезы о «пуассоновости»
    df = num_intervals - 1  # Степени свободы
    critical_value = chi2.ppf(1 - alpha, df)

    print(f"Хи-квадрат критич. χ²: {critical_value}")

    if p_value < alpha:
        print("Гипотезу о «пуассоновости» потока отвергаем.")
        num_errors += 1  # Увеличиваем счётчик ошибок
    else:
        print("Гипотезу о «пуассоновости» потока не отвергаем.")
except ValueError as e:
    print("Ошибка при вычислении критерия хи-квадрат:", e)

# Выборочная интенсивность
empirical_lambda_total = np.mean([len(stream) / (T2 - T1) for stream in combined_streams])
print(f'Выборочная интенсивность для суммарного потока: {empirical_lambda_total}')
print(f'Теоретическая интенсивность для суммарного потока: {lambda_total}')

# Сравнение ошибок
error_rate = (num_errors / num_realizations) * 100
print(f'Количество ошибок: {num_errors}')
print(f'Процент ошибок: {error_rate:.2f}%')

if error_rate < alpha * 100:
    print(f"Процент ошибок ({error_rate:.2f}%) меньше уровня значимости ({alpha * 100:.2f}%).")
else:
    print(f"Процент ошибок ({error_rate:.2f}%) больше уровня значимости ({alpha * 100:.2f}%).")

