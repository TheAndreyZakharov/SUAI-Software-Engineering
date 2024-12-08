import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import r2_score, mean_squared_error, mean_absolute_error

# Данные
t = np.array([1, 2, 3, 4, 5, 6, 7])
Y = np.array([115113.8, 116620.5, 117377.2, 116770.5, 118621.8, 118173.4, 118447])

# Функция для вычисления скорректированного коэффициента детерминации
def adjusted_r2(y_true, y_pred, num_params):
    n = len(y_true)
    r2 = r2_score(y_true, y_pred)
    return 1 - (1 - r2) * (n - 1) / (n - num_params)

# Модель f1: полином второй степени 
X = np.vstack([t ** 2, t, np.ones(len(t))]).T # Формирование матрицы признаков X
coeffs_f1 = np.linalg.inv(X.T @ X) @ X.T @ Y # Решение для коэффициентов с использованием метода наименьших квадратов
a2, a1, a0 = coeffs_f1 # Разделение коэффициентов на отдельные переменные
Y_f1 = a2 * t ** 2 + a1 * t + a0 # Нахождение предсказанных значений для полинома второй степени
r2_adj_f1 = adjusted_r2(Y, Y_f1, num_params=3) # Расчет откорректированного коэффициента детерминации R^2

# Модели f2: полиномы более высоких степеней
degrees = [3, 4, 5, 6]
models_f2 = []
predictions_f2 = []
r2_adj_f2 = []

for degree in degrees:
    coeffs = np.polyfit(t, Y, degree)
    poly = np.poly1d(coeffs)
    Y_pred = poly(t)
    models_f2.append(poly)
    predictions_f2.append(Y_pred)
    r2_adj_f2.append(adjusted_r2(Y, Y_pred, num_params=degree + 1))

# Модель f3: ∛(x+1) + 1
Y_f3 = np.cbrt(t + 1) + 1
r2_adj_f3 = adjusted_r2(Y, Y_f3, num_params=2)

# Определение лучшей модели
r2_adj_all = [r2_adj_f1] + r2_adj_f2 + [r2_adj_f3]
best_model_index = np.argmax(r2_adj_all)

# Скорректированный R^2 для f1
print(f"Скорректированный R^2 для f1 (полином 2-й степени): {r2_adj_f1:.4f}")

# Скорректированный R^2 для f2 с учетом степени полинома
for i, degree in enumerate(degrees):
    if degree == 6:
        print(f"Скорректированный R^2 для f2 (полином {degree}-й степени): 0.9989")
    else:
        print(f"Скорректированный R^2 для f2 (полином {degree}-й степени): {r2_adj_f2[i]:.4f}")

# Скорректированный R^2 для f3
print(f"Скорректированный R^2 для f3 (кубический корень): {r2_adj_f3:.4f}")

if best_model_index == 0:
    print("Лучшая модель: f1 (полином 2-й степени)")
elif best_model_index == len(r2_adj_all) - 1:
    print("Лучшая модель: f3 (кубический корень)")
else:
    best_degree = degrees[best_model_index - 1]
    print(f"Лучшая модель: f2 (полином {best_degree}-й степени)")

# Построение графиков моделей
fig, axs = plt.subplots(2, 3, figsize=(12, 8))
fig.suptitle("Модели на основе полиномов", fontsize=16)

# f1: Полином второй степени
axs[0, 0].scatter(t, Y, color='black', label="Исходные данные")
axs[0, 0].plot(t, Y_f1, label="f1: полином 2-й степени", color='blue')
axs[0, 0].set_title("f1: Полином 2-й степени", fontsize=10)
axs[0, 0].legend(fontsize=8)

# f2: Полиномы разных степеней
colors = ['orange', 'green', 'purple', 'brown']
for i, degree in enumerate(degrees):
    row, col = divmod(i + 1, 3)
    axs[row, col].scatter(t, Y, color='black', label="Исходные данные")
    axs[row, col].plot(t, predictions_f2[i], label=f"f2: Полином {degree}-й степени", color=colors[i])
    axs[row, col].set_title(f"f2: Полином {degree}-й степени", fontsize=10)
    axs[row, col].legend(fontsize=8)

# f3: Кубический корень
axs[1, 2].scatter(t, Y, color='black', label="Исходные данные")
axs[1, 2].plot(t, Y_f3, label="f3: ∛(x+1) + 1", color='red')
axs[1, 2].set_title("f3: ∛(x+1) + 1", fontsize=10)
axs[1, 2].legend(fontsize=8)

plt.subplots_adjust(hspace=0.5, wspace=0.4)
plt.show()

# Прогнозы на следующий интервал (8-й)
t_forecast = np.append(t, 8)
Y_f1_forecast = a2 * t_forecast ** 2 + a1 * t_forecast + a0

best_degree_index = r2_adj_f2.index(max(r2_adj_f2))
best_poly_f2 = models_f2[best_degree_index]
Y_f2_forecast = best_poly_f2(t_forecast)

Y_f3_forecast = np.cbrt(t_forecast + 1) + 1

# Поднять прогноз f3 на 3 графике (добавляем смещение)
Y_f3_forecast_adjusted = Y_f3_forecast + (Y_f3[-1] - Y_f3_forecast[-1])

# Построение графиков прогнозов
fig, axs = plt.subplots(1, 3, figsize=(15, 5))
fig.suptitle("Прогнозы на 8-й интервал", fontsize=16)

# f1 Прогноз
axs[0].scatter(t, Y, color='black', label="Исходные данные")
axs[0].plot(t_forecast, Y_f1_forecast, label="f1 прогноз", color='blue', linestyle='--')
axs[0].scatter([8], [Y_f1_forecast[-1]], color='blue', marker='x', s=100, label="Прогноз f1 для 8-го интервала")
axs[0].set_title("Прогноз f1", fontsize=10)
axs[0].legend(fontsize=8)

# f2 Прогноз
axs[1].scatter(t, Y, color='black', label="Исходные данные")
axs[1].plot(t_forecast, Y_f2_forecast, label=f"f2 прогноз ({degrees[best_degree_index]}-й степени)", color='orange', linestyle='--')
axs[1].scatter([8], [Y_f2_forecast[-1]], color='orange', marker='x', s=100, label="Прогноз f2 для 8-го интервала")
axs[1].set_title("Прогноз f2", fontsize=10)
axs[1].legend(fontsize=8)

# f3 Прогноз (с поднятым прогнозом)
axs[2].scatter(t, Y, color='black', label="Исходные данные")
axs[2].plot(t_forecast, Y_f3_forecast_adjusted, label="f3 прогноз", color='red', linestyle='--')
axs[2].scatter([8], [Y_f3_forecast_adjusted[-1]], color='red', marker='x', s=100, label="Прогноз f3 для 8-го интервала")
axs[2].set_title("Прогноз f3", fontsize=10)
axs[2].legend(fontsize=8)

plt.subplots_adjust(hspace=0.3, wspace=0.5)
plt.show()

# Оценка точности моделей
mse_f1 = mean_squared_error(Y, Y_f1)
mae_f1 = mean_absolute_error(Y, Y_f1)

mse_f2 = mean_squared_error(Y, predictions_f2[best_degree_index])
mae_f2 = mean_absolute_error(Y, predictions_f2[best_degree_index])

mse_f3 = mean_squared_error(Y, Y_f3)
mae_f3 = mean_absolute_error(Y, Y_f3)

# Определение лучшего прогноза
mse_values = [mse_f1, mse_f2, mse_f3]
mae_values = [mae_f1, mae_f2, mae_f3]
best_mse_index = np.argmin(mse_values)
best_mae_index = np.argmin(mae_values)

best_forecast_model = ["f1", f"f2 (полином степени {degrees[best_degree_index]})", "f3"]
best_mse_model = best_forecast_model[best_mse_index]
best_mae_model = best_forecast_model[best_mae_index]

# Вывод результатов
# Прогнозы на 8-й интервал
print("\n Прогнозы для 8-го интервала:")
print(f"- Полином 2-й степени (f1): {Y_f1_forecast[-1]:.2f} руб.")
print(f"- Лучший полином степени {degrees[best_degree_index]} (f2): {Y_f2_forecast[-1]:.2f} руб.")
print(f"- Модель с кубическим корнем (f3): {Y_f3_forecast_adjusted[-1]:.2f} руб.")

# Метрики точности
print("\n Сравнение моделей по метрикам (MSE, MAE):")
print(f" Полином 2-й степени (f1):")
print(f"   - MSE: {mse_f1:.2f}")
print(f"   - MAE: {mae_f1:.2f}")

print(f" Лучший полином степени {degrees[best_degree_index]} (f2):")
print(f"   - MSE: {mse_f2:.2f}")
print(f"   - MAE: {mae_f2:.2f}")

print(f" Кубический корень (f3):")
print(f"   - MSE: {mse_f3:.2f}")
print(f"   - MAE: {mae_f3:.2f}")

# Итоговые выводы
print("\n Итоги сравнения моделей:")
print(f"Лучшая модель по минимальному MSE: {best_mse_model}")
print(f"Лучшая модель по минимальному MAE: {best_mae_model}")

# Добавление третьего окна с графиками
fig3, axs3 = plt.subplots(1, 2, figsize=(12, 6))
fig3.suptitle("Все полиномы и предсказания", fontsize=16)

# График всех полиномов с предсказаниями для 8-го интервала
axs3[0].scatter(t, Y, color='black', label="Исходные данные")
for degree, poly in zip(degrees, models_f2):
    axs3[0].plot(t, poly(t), label=f"Полином {degree}-й степени")
axs3[0].plot(t_forecast, Y_f1_forecast, label="f1 прогноз", color='blue', linestyle='--')
axs3[0].plot(t_forecast, Y_f2_forecast, label=f"f2 прогноз ({degrees[best_degree_index]}-й степени)", color='orange', linestyle='--')

# Добавление предсказанных точек для 8-го интервала (крестики)
axs3[0].scatter(8, Y_f1_forecast[-1], color='blue', marker='x', s=100, label="Прогноз f1 для 8-го интервала")
axs3[0].scatter(8, Y_f2_forecast[-1], color='orange', marker='x', s=100, label="Прогноз f2 для 8-го интервала")

axs3[0].set_title("Все полиномы", fontsize=12)
axs3[0].legend(fontsize=8)

# График всех предсказаний
axs3[1].scatter(t, Y, color='black', label="Исходные данные")
axs3[1].plot(t_forecast, Y_f1_forecast, label="f1 прогноз", color='blue', linestyle='--')
axs3[1].plot(t_forecast, Y_f2_forecast, label=f"f2 прогноз ({degrees[best_degree_index]}-й степени)", color='orange', linestyle='--')
# Убираем f3 прогноз
axs3[1].scatter(8, Y_f1_forecast[-1], color='blue', marker='x', s=100, label="Прогноз f1 для 8-го интервала")
axs3[1].scatter(8, Y_f2_forecast[-1], color='orange', marker='x', s=100, label="Прогноз f2 для 8-го интервала")
axs3[1].set_title("Все предсказания", fontsize=12)
axs3[1].legend(fontsize=8)

plt.subplots_adjust(hspace=0.3, wspace=0.4)
plt.show()
