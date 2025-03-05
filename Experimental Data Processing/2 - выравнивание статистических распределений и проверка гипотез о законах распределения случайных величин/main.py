import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt

# Данные из таблицы
intervals = np.array([[-1.5, -1], [-1, -0.5], [-0.5, 0], [0, 0.5], [0.5, 1], [1, 1.5], [1.5, 2]])
observed_frequencies = np.array([7, 11, 22, 20, 21, 10, 9])
total_count = np.sum(observed_frequencies)

# 1. Найти статистические вероятности
probabilities = observed_frequencies / total_count

# 2. Построение гистограммы
bin_edges = np.append(intervals[:, 0], intervals[-1, 1])
plt.hist(intervals[:, 0], bins=bin_edges, weights=observed_frequencies, density=True, alpha=0.6, color='b', label='Экспериментальные данные')

# 3. Теоретическая плотность нормального распределения (метод моментов)
mean_estimate = np.sum((intervals[:, 0] + intervals[:, 1]) / 2 * observed_frequencies) / total_count
std_estimate = np.sqrt(np.sum(((intervals[:, 0] + intervals[:, 1]) / 2 - mean_estimate) ** 2 * observed_frequencies) / total_count)
x = np.linspace(-2, 2, 1000)
normal_pdf = stats.norm.pdf(x, mean_estimate, std_estimate)
plt.plot(x, normal_pdf, 'r-', label='Теоретическая плотность')

# 4. Проверка гипотезы методом К. Пирсона
expected_frequencies = total_count * (stats.norm.cdf(intervals[:, 1], mean_estimate, std_estimate) - stats.norm.cdf(intervals[:, 0], mean_estimate, std_estimate))
expected_frequencies *= total_count / np.sum(expected_frequencies)  # Коррекция, чтобы суммы совпадали

chi2_stat, p_value = stats.chisquare(observed_frequencies, expected_frequencies)
alpha = 0.05  # Для нечетных вариантов (вариант 77)

# Вывод результатов
print("1. Статистические вероятности попаданий:", probabilities)
print("2. Оценка математического ожидания:", mean_estimate)
print("3. Оценка стандартного отклонения:", std_estimate)
print("4. Проверка гипотезы Пирсона:")
print("   - Хи-квадрат статистика:", chi2_stat)
print("   - p-значение:", p_value)
print("   - Гипотеза о нормальном распределении", "принимается" if p_value > alpha else "отвергается")

# Оформление графика
plt.xlabel("Случайная величина")
plt.ylabel("Плотность вероятности")
plt.legend()
plt.title("Гистограмма и теоретическая плотность нормального распределения")
plt.show()