import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.stats import poisson, chi2
import math

# Исходные данные
N = 14
T1 = N
T2 = N + 100
lambda1 = (N + 8) / (N + 24)
lambda2 = (N + 9) / (N + 25)

# Функция для генерации пуассоновского потока
def generate_poisson_stream(T1, T2, lambd):
    t = T1
    events = []
    while t < T2:
        u = -np.log(np.random.rand()) / lambd
        t += u
        if t < T2:
            events.append(t)
    return np.array(events)

# Генерация K = 50 потоков для суммарного потока
K = 50
num_bins = 25
bins = np.linspace(T1, T2, num_bins + 1)  # Интервалы для разбиения
total_streams = []
hist_data = []  # Для хранения количества событий в каждом интервале

# Генерация 50 потоков и подсчет количества событий в каждом из 25 интервалов
for _ in range(K):
    stream1 = generate_poisson_stream(T1, T2, lambda1)
    stream2 = generate_poisson_stream(T1, T2, lambda2)
    total_stream = np.sort(np.concatenate((stream1, stream2)))
    total_streams.append(total_stream)

    # Подсчет количества событий в каждом интервале
    counts, _ = np.histogram(total_stream, bins)
    hist_data.append(counts)

# Шаг 3: Формирование вспомогательной таблицы
df = pd.DataFrame(hist_data, columns=[f'Интервал {i + 1}' for i in range(num_bins)])
df.index = [f'Поток {i + 1}' for i in range(K)]

# Выводим таблицу
print(df)

# Сохранение таблицы в файл CSV
df.to_csv("events_distribution.csv", index=True)  # Сохраняем как CSV файл

# Шаг 4: Анализ вариантов (частоты)
# Создаем массив всех событий
all_events = np.array(hist_data).flatten()

# Определяем уникальные значения (варианты) и их частоты
unique_values, counts = np.unique(all_events, return_counts=True)

# Рассчитываем теоретические частоты
lambda_total = lambda1 + lambda2
interval_length = (T2 - T1) / num_bins  # Длина интервала
n_l_theoretical = poisson.pmf(unique_values, lambda_total * interval_length) * len(all_events)

# Формирование таблицы результатов (шаг 4)
results_df = pd.DataFrame({
    'Вариант (η_l)': unique_values,
    'Частота (n_l)': counts,
    'η_l * n_l': unique_values * counts,
    'n_l (теор)': n_l_theoretical,
    '(n_l - n_l_теор)^2 / n_l_теор': (counts - n_l_theoretical) ** 2 / n_l_theoretical
})

# Выводим таблицу
print(results_df)

# Сохранение таблицы в файл CSV
results_df.to_csv("variant_frequency_analysis.csv", index=False)

# Шаг 5: Вычисляем выборочные числовые характеристики
N_total = len(all_events)  # Общее количество событий

# 1. Выборочная интенсивность наступления событий (λ̂ * Δt)
lambda_hat_dt = np.sum(unique_values * counts) / N_total
print(f"Выборочная интенсивность λ̂ * Δt = {lambda_hat_dt}")

# 2. Оценка теоретической вероятности (p̂_l)
p_hat_l = (lambda_hat_dt ** unique_values * np.exp(-lambda_hat_dt)) / np.array([math.factorial(x) for x in unique_values])
print(f"Теоретическая вероятность p̂_l = {p_hat_l}")

# 3. Оценка теоретических частот (n_l^{теор} = p̂_l * N)
n_l_teor = p_hat_l * N_total
print(f"Теоретические частоты n_l^теор = {n_l_teor}")

# 4. Объем выборки как сумма частот (N = Σ n_l)
N_sum = np.sum(counts)
print(f"Объем выборки N = {N_sum}")

# Шаг 6: Вычисляем значение квантиля хи-квадрат

# Объединение категорий с малыми теоретическими частотами
threshold = 5  # Минимум 5 для теоретических частот
observed_combined = []
theoretical_combined = []
current_observed = 0
current_theoretical = 0

for obs, theo in zip(counts, n_l_theoretical):
    current_observed += obs
    current_theoretical += theo
    if current_theoretical >= threshold:
        observed_combined.append(current_observed)
        theoretical_combined.append(current_theoretical)
        current_observed = 0
        current_theoretical = 0

# Если остались необъединенные категории, добавляем их
if current_theoretical > 0:
    observed_combined.append(current_observed)
    theoretical_combined.append(current_theoretical)

observed_combined = np.array(observed_combined)
theoretical_combined = np.array(theoretical_combined)

# Вычисляем статистику хи-квадрат
chi_square_values = (observed_combined - theoretical_combined) ** 2 / theoretical_combined
chi_square_statistic = np.sum(chi_square_values)
print(f"Хи-квадрат статистика χ² = {chi_square_statistic}")

df_degrees_of_freedom = len(observed_combined) - 1  # Степени свободы
alpha = 0.05  # Уровень значимости
chi_square_critical = chi2.ppf(1 - alpha, df_degrees_of_freedom)
print(f"Критическое значение χ² = {chi_square_critical}")

# Шаг 7: Проверка гипотезы
if chi_square_statistic < chi_square_critical:
    print("Гипотеза о пуассоновском распределении НЕ отвергается")
else:
    print("Гипотеза о пуассоновском распределении ОТВЕРГАЕТСЯ")

# Шаг 2: Построение графика для всех потоков
plt.figure(figsize=(12, 8))

# Строим график для каждого из 50 потоков
for i, stream in enumerate(total_streams):
    for event in stream:
        plt.plot(event, i + 1, 'k|', markersize=10)  # Рисуем событие как вертикальную черту

# Подписываем оси и добавляем сетку
plt.xlabel("Время", fontsize=14)
plt.ylabel("Номер потока", fontsize=14)
plt.title("Графическая интерпретация потоков событий", fontsize=16)

# Добавляем номера частей интервала (1-25) на график
for i in range(1, num_bins + 1):
    x_pos = (bins[i - 1] + bins[i]) / 2  # Середина интервала
    plt.text(x_pos, K + 1, str(i), ha='center', va='center', fontsize=12, color='red')

# Настройка оси X: отображение времени
time_labels = [f"{int(b)}" for b in np.linspace(T1, T2, num_bins + 1)]
plt.xticks(np.linspace(T1, T2, num_bins + 1), labels=time_labels, rotation=45)

# Метки на оси Y для 50 потоков
plt.yticks(np.arange(1, K + 1, 1))

plt.grid(True)

# Отображаем график
plt.tight_layout()
plt.show()


# Создание полигона частот (график частот)
plt.figure(figsize=(12, 6))

# Подсчет суммарной частоты событий по всем интервалам
frequency_data = np.sum(hist_data, axis=0)

# Создаем полигон частот
plt.plot(bins[:-1], frequency_data, marker='o', linestyle='-', color='b', label='Частота событий')
plt.fill_between(bins[:-1], frequency_data, alpha=0.3, color='b')

# Подписываем оси и добавляем сетку
plt.xlabel("Интервалы времени", fontsize=14)
plt.ylabel("Количество событий", fontsize=14)
plt.title("Полигон частот для событий", fontsize=16)

# Задаем метки на оси X, включая правую границу 114
plt.xticks(np.arange(T1, T2 + 1, step=(T2 - T1) / (len(bins) - 1)), rotation=45)
plt.xlim([T1, T2])  # Устанавливаем границы по оси X

plt.grid(True)
plt.legend()

# Отображаем график
plt.tight_layout()
plt.show()