import numpy as np
import matplotlib.pyplot as plt

# объявляем функции
def f1(x):
   return 1.9 * np.sin(1.2 * x) + 4 * np.cos(3.2 * x)

def f2(x):
   return 0.3 * x + 2.2 * np.sin(2.2 * x)

# генерируем значения
x = np.linspace(-14, 14, 1000)

# строим
plt.plot(x, f1(x), label='f(x)=-1.2*sin(2.0*x)+3*cos(0.8*x)')
plt.plot(x, f2(x), label='f(x)=0.5*x+1.7*sin(x)')

# обозначения
plt.legend()
plt.xlabel('x')
plt.ylabel('y')

# отображаем график
plt.show()
