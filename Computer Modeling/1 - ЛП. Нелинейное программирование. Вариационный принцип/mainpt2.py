import sympy as sp
import numpy as np
import matplotlib.pyplot as plt

# Переменная
x = sp.Symbol('x')

# Общее решение
C1, C2 = sp.symbols('C1 C2')
y_general = x**2 / 2 + C1 * x + C2

# Граничные условия
boundary_eq1 = sp.Eq(y_general.subs(x, sp.pi / 4), -sp.log(sp.sqrt(2)))
boundary_eq2 = sp.Eq(y_general.subs(x, sp.pi / 2), 0)

# Решение системы уравнений для C1 и C2
constants = sp.solve([boundary_eq1, boundary_eq2], [C1, C2])
y_solution = y_general.subs(constants)

# Печать решения
print("Решение:", y_solution)

# График
x_vals = np.linspace(np.pi / 4, np.pi / 2, 100)
y_vals = [y_solution.subs(x, val) for val in x_vals]

plt.plot(x_vals, y_vals, label='y(x)')
plt.xlabel('x')
plt.ylabel('y(x)')
plt.title('Решение вариационной задачи')
plt.legend()
plt.grid(True)
plt.show()