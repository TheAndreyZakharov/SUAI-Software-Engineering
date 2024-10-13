import numpy as np

# Коэффициенты целевой функции
c = np.array([1, 6, 0, 0, 0, 0])

# Матрица ограничений
A = np.array([
    [1, 2, 1, 0, 0, 0],
    [3, -3, 0, -1, 0, 0],
    [2, 3, 0, 0, 1, 0],
    [3, 1, 0, 0, 0, -1]
])

# Правые части ограничений
b = np.array([10, 6, 6, 4])

# Базисные переменные
basis = [2, 3, 4, 5]

while True:
    # Вычисляем потенциалы
    potentials = c[basis] @ np.linalg.inv(A[:, basis])

    # Вычисляем оценки
    deltas = potentials @ A - c

    # Если все оценки неотрицательны, то решение оптимально
    if all(d >= 0 for d in deltas):
        break

    # Выбираем входящую переменную (с наибольшей отрицательной оценкой)
    j0 = np.argmin(deltas)

    # Вычисляем минимальное отношение
    z = np.linalg.inv(A[:, basis]) @ b
    q = np.linalg.inv(A[:, basis]) @ A[:, j0]
    theta = [z[i] / q[i] if q[i] > 0 else float('inf') for i in range(len(q))]
    i0 = np.argmin(theta)

    # Обновляем базис
    basis[i0] = j0

# Вычисляем оптимальное решение
x = np.zeros_like(c)
x[basis] = np.linalg.inv(A[:, basis]) @ b

print("Оптимальное значение целевой функции:", c @ x)
print("Оптимальные значения переменных: x1 =", x[0], ", x2 =", x[1])
