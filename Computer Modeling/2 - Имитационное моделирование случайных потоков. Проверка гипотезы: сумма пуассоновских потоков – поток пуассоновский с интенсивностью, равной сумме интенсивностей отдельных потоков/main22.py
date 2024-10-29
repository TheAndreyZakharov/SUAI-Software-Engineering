#Создать графическую интерпретацию потока событий
import numpy as np
import matplotlib.pyplot as plt

# События для потока 1 и 2
times_lambda1 = [14.144656290359723, 14.245430959518284, 15.870360435778926, 16.29501713640534, 17.228897323542817,
                 17.571732656860803, 19.40067390264146, 19.72280321277349, 19.855450931254342, 21.776704196762626,
                 22.08432219022099, 23.55329638966273, 24.414203278922265, 26.904221517373184, 27.49644391044489,
                 31.408330066964005, 32.21902663112003, 33.155504275125715, 38.51710311042, 40.83000094504166,
                 45.81949059265343, 46.45381695088097, 48.886923434048974, 52.177927391625424, 55.739809477928745,
                 56.73897570448275, 58.79551591892846, 59.51988432239473, 61.80060963647, 63.21371535795842,
                 63.458969643398625, 64.3807617215022, 64.43243120521215, 64.54499442569066, 64.87706203583943,
                 67.14875098498709, 70.08644113098782, 71.29001091235361, 71.40316555508083, 71.5922739991153,
                 72.40440118334325, 73.71274107451295, 74.15484461961928, 75.42705960159543, 78.03842390835,
                 80.55257706894515, 82.30877823333554, 84.81758137261708, 85.61718089332184, 90.38252402622072,
                 90.39986558825497, 90.84778013256036, 91.69839353132784, 92.2167541395015, 93.97352734454577,
                 94.34769349689543, 94.44441301764397, 94.61808599851017, 98.42055750341736, 100.19345020492788,
                 100.19615661822402, 100.47528276511183, 101.07816867378038, 102.3964861401507, 104.83052744768527,
                 108.3556985687063, 111.7704078990894, 112.65734735982943, 113.74143637399168, 113.91586082365728]

times_lambda2 = [14.965213008440834, 16.463872328461488, 25.92814800109643, 27.044130012269843, 27.36239734353938,
                 27.43314672880725, 27.881548211275117, 30.249314673970748, 36.86246424634978, 38.05398556827677,
                 39.36362496298905, 40.10005640922487, 40.33805550024891, 41.070112841991964, 44.05832527399739,
                 45.97694154636217, 47.23389321303442, 47.820761282650544, 51.89751687367954, 52.831095566093154,
                 54.158247596639995, 54.55526987165556, 56.385166184168725, 57.13230675232804, 57.48376771737754,
                 60.36914172925102, 62.32865896369908, 62.48602040315972, 62.78012376566771, 65.20233308057423,
                 65.34822637910412, 68.90270199916066, 69.8037561125557, 71.73569047748956, 74.1608726094903,
                 75.40066530170397, 75.56331825016916, 79.84851480196735, 80.09549999780303, 80.12161535986704,
                 82.02559515177765, 82.3271465729763, 82.92042288018673, 84.03867939206404, 85.368841996041,
                 86.04507069118826, 86.86238898034254, 86.92009255120678, 89.25327518503057, 90.56596112727736,
                 90.66917569348078, 91.48669619767543, 91.9915254072604, 92.0793466932704, 93.57524185391517,
                 94.12270998735971, 94.24505552125193, 94.9416995054687, 96.36944563207875, 98.86734154993871,
                 100.20990759592745, 104.03602359924209, 104.80016721429358, 105.49110014166743, 105.58544476554952,
                 105.92566607826508, 108.24171508080693, 110.31954370874698, 113.70130368506567]

# Построение графиков
plt.figure(figsize=(10, 6))

# Построение для потока 1
plt.scatter(times_lambda1, [1]*len(times_lambda1), color='blue', label='Поток 1 (λ1)', alpha=0.6)

# Построение для потока 2
plt.scatter(times_lambda2, [2]*len(times_lambda2), color='red', label='Поток 2 (λ2)', alpha=0.6)

# Оформление графика
plt.title('График событий двух потоков')
plt.xlabel('Время')
plt.yticks([1, 2], ['Поток 1', 'Поток 2'])
plt.legend()
plt.grid(True)
plt.show()
