import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt

# Данные
X1 = np.array([-2, -1, 0, 1, 2, -3])
X2 = np.array([1, 3, 4, 6, 7, -10])
Y = np.array([-11, -2, 7, 16, 26, -9])

# 1. Центрирование факторов
X1_c = X1 - np.mean(X1)
X2_c = X2 - np.mean(X2)

# 2. Составляем матричное уравнение
X_matrix = np.vstack([X1_c, X2_c, np.ones_like(X1)]).T  # Матрица регрессоров
Y_vector = Y  # Вектор отклика

# 3. Оценки коэффициентов регрессии
B = np.linalg.lstsq(X_matrix, Y_vector, rcond=None)[0]
B1, B2, B0 = B  # Разбираем коэффициенты
print(f"1. Уравнение регрессии: y = {B1:.3f}*x1 + {B2:.3f}*x2 + {B0:.3f}")

# 4. Проверка адекватности по критерию Фишера
Y_pred = X_matrix @ B  # Предсказанные значения
S_res = np.sum((Y - Y_pred) ** 2)  # Остаточная сумма квадратов
S_tot = np.sum((Y - np.mean(Y)) ** 2)  # Полная сумма квадратов
R2 = 1 - (S_res / S_tot)  # Коэффициент детерминации

n, m = len(X1), 3  # Число наблюдений и коэффициентов
F_stat = (R2 / (m - 1)) / ((1 - R2) / (n - m))
F_crit = stats.f.ppf(1 - 0.05, m - 1, n - m)
print(f"2. Критерий Фишера: F = {F_stat:.3f}, критическое значение = {F_crit:.3f}")
print("   - Уравнение адекватно" if F_stat > F_crit else "   - Уравнение НЕ адекватно")

# 5. Проверка значимости коэффициентов по критерию Стьюдента
sigma2 = S_res / (n - m)
cov_matrix = np.linalg.inv(X_matrix.T @ X_matrix) * sigma2
std_errors = np.sqrt(np.diag(cov_matrix))
T_stats = B / std_errors
T_crit = stats.t.ppf(1 - 0.05 / 2, n - m)

print("3. Критерий Стьюдента:")
for i, (coef, t_stat) in enumerate(zip(B, T_stats)):
    print(f"   - Коэффициент B{i}: t = {t_stat:.3f}, критическое значение = {T_crit:.3f},", "значим" if abs(t_stat) > T_crit else "НЕзначим")

# 6. Исключение незначимых коэффициентов и повторная проверка
significant_mask = abs(T_stats) > T_crit
if not all(significant_mask):
    X_reduced = X_matrix[:, significant_mask]
    B_reduced = np.linalg.lstsq(X_reduced, Y_vector, rcond=None)[0]
    print("4. Уравнение после исключения незначимых факторов:")
    print("   - Уравнение:", " + ".join([f"{c:.3f}*x{i+1}" for i, c in enumerate(B_reduced[:-1])]) + f" + {B_reduced[-1]:.3f}")