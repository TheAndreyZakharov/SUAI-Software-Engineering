#Генерация пуассоновских потоков
#Графическая интерпретация потока событий
import numpy as np
import matplotlib.pyplot as plt

# Параметры
N = 14  # Ваш номер студента
T1 = N
T2 = N + 100
lambda1 = (N + 8) / (N + 24)
lambda2 = (N + 9) / (N + 25)

# Генерация пуассоновского потока
def generate_poisson_process(T1, T2, lambd):
    time = T1
    times = []  # Время наступления событий
    while time < T2:
        u = np.random.random()
        interval = -np.log(u) / lambd  # Генерация интервала по показательной функции
        time += interval
        if time < T2:
            times.append(time)
    return times

# Генерация потоков для двух разных λ
times1 = generate_poisson_process(T1, T2, lambda1)
times2 = generate_poisson_process(T1, T2, lambda2)

# Графическое представление
plt.figure(figsize=(10, 6))
plt.step(times1, np.arange(1, len(times1)+1), label=f'λ1 = {lambda1:.2f}')
plt.step(times2, np.arange(1, len(times2)+1), label=f'λ2 = {lambda2:.2f}')
plt.title('Пуассоновские потоки')
plt.xlabel('Время')
plt.ylabel('Количество событий')
plt.legend()
plt.show()
