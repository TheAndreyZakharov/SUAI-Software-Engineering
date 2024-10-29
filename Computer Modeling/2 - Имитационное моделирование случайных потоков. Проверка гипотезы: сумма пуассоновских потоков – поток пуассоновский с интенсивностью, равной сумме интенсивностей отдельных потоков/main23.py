#Осуществить проверку гипотезы о виде распределения для суммарного потока
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import kstest

# Параметры потоков
T1 = 14  # начальный момент времени
T2 = 114  # конечный момент времени
lambda1 = (14 + 8) / (14 + 24)  # λ1
lambda2 = (14 + 9) / (14 + 25)  # λ2

# Генерация моментов событий для двух потоков
def generate_poisson_process(lmbda, T1, T2):
    events = []
    current_time = T1
    while current_time < T2:
        inter_event_time = np.random.exponential(1/lmbda)
        current_time += inter_event_time
        if current_time < T2:
            events.append(current_time)
    return np.array(events)

# Генерация событий
events_stream1 = generate_poisson_process(lambda1, T1, T2)
events_stream2 = generate_poisson_process(lambda2, T1, T2)

# Объединение двух потоков
merged_events = np.sort(np.concatenate([events_stream1, events_stream2]))

# Построение графиков событий
plt.figure(figsize=(10, 6))
plt.eventplot([events_stream1, events_stream2, merged_events], linelengths=0.9, colors=['b', 'g', 'r'])
plt.title('Poisson Streams and Merged Stream')
plt.xlabel('Time')
plt.ylabel('Stream')
plt.yticks([0, 1, 2], ['Stream 1', 'Stream 2', 'Merged Stream'])
plt.grid(True)
plt.show()

# Проверка гипотезы с помощью хи-квадрат
# Для проверки возьмем интервалы времени между событиями суммарного потока
inter_event_times = np.diff(merged_events)

# Ожидаемые интервалы для пуассоновского процесса
expected_intervals = np.random.exponential(1/(lambda1 + lambda2), len(inter_event_times))

# Применение теста Колмогорова-Смирнова
ks_stat, p_value = kstest(inter_event_times, 'expon', args=(0, 1/(lambda1 + lambda2)))

# Результаты
print(f'K-S statistic: {ks_stat}, p-value: {p_value}')

if p_value > 0.05:
    print("Не можем отвергнуть гипотезу: распределение суммарного потока соответствует пуассоновскому")
else:
    print("Отвергаем гипотезу: распределение суммарного потока не соответствует пуассоновскому")
