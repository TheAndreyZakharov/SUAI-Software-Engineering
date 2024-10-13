import pandas as pd
import numpy as np
from scipy import stats


def solution(x: np.array, y: np.array, alpha: float = 0.05) -> bool:
   pvalue = stats.ttest_ind(x, y, equal_var=False, alternative='two-sided').pvalue

   if pvalue <= alpha:
       is_rejected = True
   else:
       is_rejected = False

   return is_rejected


def process_dataframe(category: str, all_groups: pd.DataFrame, my_group: pd.DataFrame):
   x = all_groups[category].to_numpy()
   y = my_group[category].to_numpy()

   if solution(x, y):
       print(f'Категория {category}: Гипотезу о равенстве средних отвергаем')
   else:
       print(f'Категория {category}: Гипотезу о равенстве средних принимаем')


if __name__ == '__main__':
   df1 = pd.read_csv('4131.csv')
   df2 = pd.read_csv('4132.csv')
   df3 = pd.read_csv('4133.csv')
   df4 = pd.read_csv('4134.csv')
   df5 = pd.read_csv('4136.csv')

   all_groups = pd.concat([df1, df2, df3, df4, df5], ignore_index=True)
   my_group = df3

   categories = all_groups.columns

   for category in categories:
       process_dataframe(category, all_groups, my_group)
 
