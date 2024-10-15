# Итеративная версия функции x1 * x2 - y
def iterative_function(x1, x2, y):
    product = 0
    abs_x2 = abs(x2)  # Работаем с модулем
    for _ in range(abs_x2):
        product += x1
    if x2 < 0:
        product = -product  # Корректируем знак при отрицательном x2
    return product - y

# Рекурсивная версия функции x1 * x2 - y для целой части
def recursive_multiply_integer(x1, x2):
    if x2 == 0:
        return 0
    elif x2 > 0:
        return x1 + recursive_multiply_integer(x1, x2 - 1)
    else:  # Обрабатываем случай отрицательного x2
        return -x1 + recursive_multiply_integer(x1, x2 + 1)

def recursive_function(x1, x2, y):
    # Вычисляем произведение для целой части
    product = recursive_multiply_integer(x1, x2)
    return product - y

# Функции для безопасного ввода значений
def input_integer(prompt):
    while True:
        try:
            value = int(input(prompt))
            return value
        except ValueError:
            print("Ошибка: пожалуйста, введите корректное число.")

# Главная программа
def main():
    # Ввод каждого аргумента отдельно с проверкой
    x1 = input_integer("Введите значение x1: ")
    x2 = input_integer("Введите значение x2: ")
    y = input_integer("Введите значение y: ")

    # Вычисление итеративным способом
    result_iterative = iterative_function(x1, x2, y)
    print(f"Итеративный результат: {result_iterative}")

    # Вычисление рекурсивным способом
    result_recursive = recursive_function(x1, x2, y)
    print(f"Рекурсивный результат: {result_recursive}")

# Запуск программы
main()
