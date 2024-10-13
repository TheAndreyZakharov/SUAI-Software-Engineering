import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.stats import pearsonr

# Чтение данных
df = pd.read_csv('kc_house_data.csv')

def regression_and_correlation(x, y, xlabel, ylabel):
   # Подготовка данных
   X = np.array(df[x])
   Y = np.array(df[y])

   # Вычисление коэффициентов линейной регрессии
   A = np.vstack([X, np.ones(len(X))]).T
   m, c = np.linalg.lstsq(A, Y, rcond=None)[0]

   # Построение графика
   plt.figure(figsize=(10, 6))
   plt.scatter(X, Y)
   plt.plot(X, m * X + c, color='red')
   plt.xlabel(xlabel)
   plt.ylabel(ylabel)
   plt.title(f'{xlabel} vs {ylabel}')
   plt.show()

   # Вычисление коэффициента корреляции
   corr, _ = pearsonr(df[x], df[y])
   print(f'Коэффициент корреляции между {xlabel} и {ylabel}: {corr:.3f}\n')

regression_and_correlation('price', 'sqft_living', 'Price', 'Sqft Living')
regression_and_correlation('price', 'sqft_lot', 'Price', 'Sqft Lot')
regression_and_correlation('sqft_living', 'sqft_lot', 'Sqft Living', 'Sqft Lot')
 
