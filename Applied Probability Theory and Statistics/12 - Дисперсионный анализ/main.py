import numpy as np
import pandas as pd
from scipy.stats import f_oneway
from tabulate import tabulate
import matplotlib.pyplot as plt


def read_csv_files(file_names):
   data = {}
   for file_name in file_names:
       group_number = file_name.split('.')[0]
       data[group_number] = pd.read_csv(file_name)
   return data


def perform_anova(data, category, alpha=0.05):
   group_means = []
   all_data = []
   for group_number, df in data.items():
       group_mean = df[category].mean()
       group_means.append((group_number, group_mean))
       all_data.extend(df[category].tolist())

   overall_mean = np.mean(all_data)

   groups = [df[category].tolist() for df in data.values()]
   statistic, p_value = f_oneway(*groups)

   reject_null_hypothesis = p_value < alpha

   return group_means, overall_mean, statistic, p_value, reject_null_hypothesis


def print_results(data, categories):
   for category in categories:
       print(f"\nКатегория: {category}")
       group_means, overall_mean, statistic, p_value, reject_null_hypothesis = perform_anova(data, category)

       print("\nСредние значения по группам:")
       print(tabulate(group_means, headers=["Группа", "Среднее"]))

       print(f"\nСреднее значение по всему потоку: {overall_mean:.2f}")

       print(f"\nРезультаты дисперсионного анализа:")
       print(f"Значение статистики: {statistic:.2f}")
       print(f"p-значение: {p_value:.4f}")

       if reject_null_hypothesis:
           print("Отвергаем нулевую гипотезу: есть связь между номером группы и результатами опросов")
       else:
           print("Принимаем нулевую гипотезу: связь между номером группы и результатами опросов отсутствует")


file_names = ["4131.csv", "4132.csv", "4133.csv", "4134.csv", "4136.csv"]
data = read_csv_files(file_names)

categories = data[next(iter(data))].columns.tolist()  # получаем список категорий из первого файла

print_results(data, categories)
 
