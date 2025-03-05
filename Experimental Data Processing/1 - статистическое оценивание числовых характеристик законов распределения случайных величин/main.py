import numpy as np
import scipy.stats as stats

data = np.array([1.3, 2.8, 4.3, 6.5, 9.9, 12.1, 9.2, 7.7, 6.4, 4.6, 18.6, 1])
confidence_level_95 = 0.95
confidence_level_82 = 0.82
max_error = 0.31

# 1. Оценка математического ожидания
mean_estimate = np.mean(data)

# 2. 95%-доверительный интервал
n = len(data)
stderr = stats.sem(data)
t_crit_95 = stats.t.ppf((1 + confidence_level_95) / 2, df=n-1)
ci_95 = (mean_estimate - t_crit_95 * stderr, mean_estimate + t_crit_95 * stderr)

# 3. Отсеивание аномальных наблюдений
filtered_data = data[(data >= ci_95[0]) & (data <= ci_95[1])]

# 4. Уточненная оценка математического ожидания
updated_mean_estimate = np.mean(filtered_data)

# 5. Проверка качества оценивания
# Доверительный интервал для математического ожидания при 82%-й вероятности
t_crit_82 = stats.t.ppf((1 + confidence_level_82) / 2, df=len(filtered_data)-1)
stderr_filtered = stats.sem(filtered_data)
ci_82 = (updated_mean_estimate - t_crit_82 * stderr_filtered, updated_mean_estimate + t_crit_82 * stderr_filtered)

# Доверительная вероятность попадания в интервал с максимальной вероятной погрешностью
prob_with_error = stats.t.cdf((max_error / stderr_filtered), df=len(filtered_data)-1) * 2 - 1

# Вывод результатов
print("1. Оценка математического ожидания:", mean_estimate)
print("2. 95%-доверительный интервал:", ci_95)
print("3. Данные после отсеивания аномалий:", filtered_data)
print("4. Уточненная оценка математического ожидания:", updated_mean_estimate)
print("5. Проверка качества оценивания:")
print("   - Доверительный интервал при 82% вероятности:", ci_82)
print("   - Доверительная вероятность попадания в интервал с погрешностью", max_error, ":", prob_with_error)
