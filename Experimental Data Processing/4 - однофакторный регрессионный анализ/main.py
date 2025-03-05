import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt

# Данные из таблицы
X = np.array([-3, -1, 0, 2, 3])
Y = np.array([10, -1, -3, -4, -1])

# 1. Решение системы нормальных уравнений (метод наименьших квадратов)
A = np.vstack([X**2, X, np.ones_like(X)]).T  # Матрица для МНК
b = Y  # Вектор значений Y
coeffs = np.linalg.lstsq(A, b, rcond=None)[0]  # Решение системы

# Коэффициенты полинома
a2, a1, a0 = coeffs
print(f"1. Уравнение регрессии: y = {a2:.3f}x^2 + {a1:.3f}x + {a0:.3f}")

# 2. Проверка адекватности уравнения регрессии по критерию Фишера
Y_pred = a2 * X**2 + a1 * X + a0  # Предсказанные значения
S_res = np.sum((Y - Y_pred) ** 2)  # Остаточная сумма квадратов
S_tot = np.sum((Y - np.mean(Y)) ** 2)  # Полная сумма квадратов
R2 = 1 - (S_res / S_tot)  # Коэффициент детерминации

n, m = len(X), 3  # Число наблюдений и коэффициентов
F_stat = (R2 / (m - 1)) / ((1 - R2) / (n - m))  # Ф-статистика
F_crit = stats.f.ppf(1 - 0.01, m - 1, n - m)  # Критическое значение Фишера
print(f"2. Критерий Фишера: F = {F_stat:.3f}, критическое значение = {F_crit:.3f}")
print("   - Уравнение адекватно" if F_stat > F_crit else "   - Уравнение НЕ адекватно")

# 3. Проверка значимости коэффициентов по критерию Стьюдента
sigma2 = S_res / (n - m)  # Дисперсия
cov_matrix = np.linalg.inv(A.T @ A) * sigma2  # Ковариационная матрица
std_errors = np.sqrt(np.diag(cov_matrix))  # Стандартные ошибки коэффициентов
T_stats = coeffs / std_errors  # t-статистики
T_crit = stats.t.ppf(1 - 0.01 / 2, n - m)  # Критическое значение t-критерия

print("3. Критерий Стьюдента:")
for i, (coef, t_stat) in enumerate(zip(coeffs, T_stats)):
    print(f"   - Коэффициент a{i}: t = {t_stat:.3f}, критическое значение = {T_crit:.3f},", "значим" if abs(t_stat) > T_crit else "НЕзначим")

# Исключение незначимых коэффициентов и повторная проверка
significant_mask = abs(T_stats) > T_crit
if not all(significant_mask):
    A_reduced = A[:, significant_mask]  # Исключаем незначимые коэффициенты
    coeffs_reduced = np.linalg.lstsq(A_reduced, b, rcond=None)[0]
    print("4. Повторное уравнение регрессии после исключения незначимых коэффициентов:")
    print("   - Уравнение:", " + ".join([f"{c:.3f}*x^{i}" for i, c in enumerate(coeffs_reduced[::-1])]))

# Визуализация
X_range = np.linspace(min(X), max(X), 100)
Y_range = a2 * X_range**2 + a1 * X_range + a0
plt.scatter(X, Y, color='red', label='Экспериментальные данные')
plt.plot(X_range, Y_range, label='Полиномиальная регрессия', color='blue')
plt.xlabel("X")
plt.ylabel("Y")
plt.legend()
plt.title("Полиномиальная регрессия 2-й степени")
plt.show()
