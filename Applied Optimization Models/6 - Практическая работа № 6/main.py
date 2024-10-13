import numpy as np
from scipy.optimize import linear_sum_assignment

# Задаем матрицу эффективности
cost_matrix = np.array([
    [3, 4, 12, 2, 7],
    [4, 4, 10, 11, 7],
    [9, 0, 14, 10, 1],
    [3, 1, 11, 7, 11],
    [6, 10, 13, 15, 11]
])

# Преобразуем задачу максимизации в задачу минимизации, 
# так как алгоритм linear_sum_assignment находит минимум
cost_matrix_minimization = cost_matrix.max() - cost_matrix

# Применяем венгерский метод
row_ind, col_ind = linear_sum_assignment(cost_matrix_minimization)

# Вычисляем суммарную эффективность для найденного назначения
total_efficiency = cost_matrix[row_ind, col_ind].sum()

# Создаем матрицу назначений
assignment_matrix = np.zeros_like(cost_matrix)
assignment_matrix[row_ind, col_ind] = 1

# Возвращаем результаты
row_ind, col_ind, total_efficiency, assignment_matrix.tolist()

