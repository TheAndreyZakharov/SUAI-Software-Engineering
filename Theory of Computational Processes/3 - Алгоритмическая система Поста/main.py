import re

# Фиксированные входные данные
A = ['1', '*', '-', '=']
X = ['x1', 'x2', 'y', 'x']
A1 = ['1']
R = [
    "(1) x1*1x2-y= -> x1*x2-y=x1",
    "(2) x1*1-y=x2 -> =x1x2-y",
    "(3) =1x-1y -> =x-y",
    "(4) =1x-1 -> =x",
    "(5) =1-1x -> =-x",
    "(6) x1*1-y= -> =x1-y"
]

# Функция для проверки строки на наличие символов, не входящих в алфавит
def check_alphabet(input_str, alphabet):
    for char in input_str:
        if char not in alphabet:
            raise ValueError(f"Ошибка: Найден символ '{char}', который не входит в алфавит.")

# Функция для проверки строк на наличие переменных, не входящих в заданное множество
def check_variables(input_str, variables):
    found_vars = re.findall(r'[a-zA-Z]+\d*', input_str)  # Найти все переменные
    for var in found_vars:
        if var not in variables:
            raise ValueError(f"Найдена переменная, не входящая в заданное множество: {var}")

# Функция для проверки формата аксиомы
def check_axiom_format(axiom):
    # Проверяем, соответствует ли аксиома формату число*число-число=
    pattern = r'^\d+\*\d+-\d+=$'
    if not re.match(pattern, axiom):
        raise ValueError("Ошибка: Аксиома должна иметь формат число*число-число=.")

# Функция для проверки правил на наличие недопустимых переменных
def check_rules_variables(rules, variables):
    for rule in rules:
        # Извлечение правых частей правил
        parts = rule.split('->')
        for part in parts:
            check_variables(part.strip(), variables)  # Проверка на наличие недопустимых переменных

# Функция для применения правил с использованием регулярных выражений
def apply_rules(start_str, rules):
    current_str = start_str
    result_log = []

    rule_patterns = [
        (r'(\d+)\*1(\d+)-(\d+)=', r'\1*\2-\3=\1'),  # Правило 1
        (r'(\d+)\*1-(\d+)=(\d+)', r'=\1\3-\2'),     # Правило 2
        (r'=1(\d+)-1(\d+)', r'=\1-\2'),             # Правило 3
        (r'=1(\d+)-1', r'=\1'),                     # Правило 4
        (r'=1-1(\d+)', r'=-\1'),                    # Правило 5
        (r'(\d+)\*1-(\d+)=', r'=\1-\2'),            # Правило 6
    ]

    rule_names = [
        "(1) x1*1x2-y= -> x1*x2-y=x1",
        "(2) x1*1-y=x2 -> =x1x2-y",
        "(3) =1x-1y -> =x-y",
        "(4) =1x-1 -> =x",
        "(5) =1-1x -> =-x",
        "(6) x1*1-y= -> =x1-y",
    ]

    while True:
        applied = False

        for i, (pattern, replacement) in enumerate(rule_patterns):
            match = re.search(pattern, current_str)
            if match:
                result_log.append(f"Исходная строка: {current_str}")
                result_log.append(f"Применяемое правило: {rule_names[i]}")
                current_str = re.sub(pattern, replacement, current_str, count=1)
                result_log.append(f"Результат применения: {current_str}\n")
                applied = True
                print(f"Применено правило: {rule_names[i]}")
                break

        if not applied:
            print(f"Не удалось применить ни одно правило к строке: {current_str}")
            break

    return current_str, result_log

# Основная функция программы
def main(output_file):
    try:
        # Ввод примера через консоль
        example = input("Введите пример в формате число*число-число=: ").strip()

        # Открываем файл для записи и записываем ввод
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(f"Введённый пример: {example}\n")
            f.write(f"\nВходные данные:\nАлфавит: {A}\nПеременные: {X}\nАксиомы: {A1}\nПравила: {R}\n\n")

        # Проверка примера на соответствие алфавиту и множеству переменных
        check_alphabet(example, A)
        check_variables(example, X)
        check_axiom_format(example)  # Проверка формата аксиомы

        # Применение правил вывода к аксиоме
        current_str, log = apply_rules(example, R)

        # Запись результата в файл
        with open(output_file, 'a', encoding='utf-8') as f:
            f.write("Результаты применения правил:\n")
            for line in log:
                f.write(line + '\n')

            if not log:
                f.write(f"Ни одно правило не было применено для примера: {example}\n")

        print("Вычисление прошло успешно.")

    except ValueError as ve:
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(f"В ходе вычисления произошла ошибка: {ve}\n")
        print(f"В ходе вычисления произошла ошибка: {ve}")
    except Exception as e:
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(f"Ошибка: {e}\n")
        print(f"Ошибка: {e}")

# использование программы
if __name__ == '__main__':
    output_file = 'output.txt'  # Файл для сохранения результата
    main(output_file)