import numpy as np
import matplotlib.pyplot as plt

# Генерируем 3 случайные величины ξ, η и γ с равномерным распределением от 0 до 1
xi = np.random.uniform(0, 1, size=10000)
eta = np.random.uniform(0, 1, size=10000)
gamma = np.random.uniform(0, 1, size=10000)

# Вычисляем значение случайной величины f для каждой тройки значений (ξ, η, γ)
f = np.exp(xi) + np.exp(eta) + np.exp(gamma)

# Строим гистограмму значений f
plt.hist(f, bins=50, alpha=0.5, edgecolor='black')
plt.xlabel('Значения случайной величины f')
plt.ylabel('Частота')
plt.title('Гистограмма случайной величины f')
plt.show()
