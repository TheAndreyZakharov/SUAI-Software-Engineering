import pandas as pd
import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt
from tabulate import tabulate

# Зададим уровень значимости
alpha = 0.05

# Считаем данные из всех CSV файлов
data = pd.concat([pd.read_csv("4131.csv"),
                 pd.read_csv("4132.csv"),
                 pd.read_csv("4133.csv"),
                 pd.read_csv("4134.csv"),
                 pd.read_csv("4136.csv")])

# Выделим данные только для файла 4133.csv, который является группой
group_data = pd.read_csv("4133.csv")

# Проверим нормальность выборки по всем данным
for column in data.columns:
   sample = data[column].dropna()
   print("Группа:", column)
   print("Всего наблюдений:", len(sample))

   # Построим гистограмму исходных данных
   plt.hist(sample, bins=20, density=True, alpha=0.5)

   # Вычислим оценки параметров нормального распределения
   loc, scale = stats.norm.fit(sample)

   # Вычислим теоретическую плотность вероятности
   x = np.linspace(sample.min(), sample.max(), 100)
   y = stats.norm.pdf(x, loc=loc, scale=scale)

   # Построим теоретическую плотность вероятности
   plt.plot(x, y, 'r', linewidth=2)
   plt.title(column)
   plt.show()

   # Выполним тест согласия Пирсона
   chi2, p = stats.normaltest(sample)
   print(tabulate([["Статистика критерия", chi2], ["p-value", p]], headers=["", "Значение"]))

   if p < alpha:
       print("Гипотеза о нормальности отвергается на уровне значимости", alpha)
   else:
       print("Гипотеза о нормальности не отвергается на уровне значимости", alpha)
   print("=" * 50)

# Проверим нормальность выборки только для группы (файл 4133.csv)
for column in group_data.columns:
   sample = group_data[column].dropna()
   print("Группа:", column)
   print("Всего наблюдений:", len(sample))

   # Построим гистограмму исходных данных
   plt.hist(sample, bins=20, density=True, alpha=0.5)

   # Вычислим оценки параметров нормального распредел
   loc, scale = stats.norm.fit(sample)

   # Вычислим теоретическую плотность вероятности
   x = np.linspace(sample.min(), sample.max(), 100)
   y = stats.norm.pdf(x, loc=loc, scale=scale)

   # Построим теоретическую плотность вероятности
   plt.plot(x, y, 'r', linewidth=2)
   plt.title(column)
   plt.show()

   # Выполним тест согласия Пирсона
   chi2, p = stats.normaltest(sample)
   print(tabulate([["Статистика критерия", chi2], ["p-value", p]], headers=["", "Значение"]))

   if p < alpha:
       print("Гипотеза о нормальности отвергается на уровне значимости", alpha)
   else:
       print("Гипотеза о нормальности не отвергается на уровне значимости", alpha)
   print("=" * 50)
