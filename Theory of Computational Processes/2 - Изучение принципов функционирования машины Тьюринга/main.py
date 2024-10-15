class TuringMachine:
    def __init__(self, tape, alphabet, program):
        self.alphabet = alphabet.strip().split()  # Алфавит должен инициализироваться первым
        self.tape = list(tape.strip()) + ['_'] * 20  # Лента с зазором для вычислений
        self.head_position = 0  # Положение головки
        self.state = 'q0'  # Начальное состояние
        self.program = self.parse_program(program)  # Программа инициализируется после алфавита

    def parse_program(self, program_text):
        program = {}
        for line in program_text.strip().splitlines():
            line = line.split('#')[0].strip()  # Удаляем комментарии и лишние пробелы
            if not line:
                continue  # Игнорируем пустые строки
            parts = line.split()
            if len(parts) == 6:
                state, symbol, arrow, next_state, new_symbol, move = parts
                if arrow == '->':  # Проверка правильного формата
                    program[(state, symbol)] = (new_symbol, move, next_state)
                else:
                    self.write_output(f"Ошибка в формате команды: {line}")
            else:
                self.write_output(f"Неверное количество частей в команде: {line}")

        # Проверка на корректность символов в программе
        for (state, symbol) in program.keys():
            if symbol not in self.alphabet:
                self.write_output(f"Ошибка: символ '{symbol}' в команде ({state}, {symbol}) не в алфавите")

        return program

    def step(self):
        if self.head_position < 0 or self.head_position >= len(self.tape):
            self.write_output("Ошибка: головка вышла за пределы ленты")
            return False  # Остановить выполнение

        state = self.state
        symbol = self.tape[self.head_position]

        # Проверка на наличие символа в алфавите
        if symbol not in self.alphabet:
            self.write_output(f"Ошибка: символ '{symbol}' не в алфавите")
            return False  # Остановить выполнение

        # Проверка на состояние qz
        if state == '!':
            self.write_output(f"Достигнуто !. Завершение работы.")
            return False  # Завершение выполнения

        # Находим подходящую команду для текущего состояния и символа
        if (state, symbol) in self.program:
            new_symbol, move, new_state = self.program[(state, symbol)]

            # Записываем текущее состояние ленты перед выполнением команды
            self.write_output(self.get_tape_state())

            # Записываем команду в файл
            self.write_output(f"Command: {state} {symbol} -> {new_state} {new_symbol} {move}")

            # Изменяем символ на ленте
            self.tape[self.head_position] = new_symbol

            # Двигаем головку вправо или влево
            if move == 'R':
                self.head_position += 1
            elif move == 'L':
                self.head_position -= 1

            # Проверка на выход головки за пределы ленты
            if self.head_position < 0 or self.head_position >= len(self.tape):
                self.write_output("Ошибка: головка вышла за пределы ленты после перемещения")
                return False  # Остановить выполнение

            # Меняем состояние машины
            self.state = new_state

            # Записываем текущее состояние ленты после выполнения команды
            self.write_output(self.get_tape_state())

            return True  # Возвращаем True для продолжения работы
        else:
            self.write_output(f"Ошибка: нет команды для состояния '{state}' и символа '{symbol}'")
            return False  # Остановить выполнение

    def get_tape_state(self):
        tape_str = ''.join(self.tape)
        head_str = ' ' * self.head_position + '^'
        return f"{tape_str}\n{head_str}\nState: {self.state}"

    def write_output(self, text):
        # Печатаем в консоль
        print(text)
        # Записываем в файл
        with open('output.txt', 'a') as f:
            f.write(text + '\n')

    def run(self, output_file):
        with open(output_file, 'w') as f:
            pass  # Очистка файла перед записью
        while self.step():
            pass
        print(f"Output written to {output_file}")


# Чтение данных из файлов
with open('tape.txt') as tape_file:
    tape = tape_file.read()

with open('alphabet.txt') as alphabet_file:
    alphabet = alphabet_file.read()

with open('program.txt') as program_file:
    program = program_file.read()

# Создание машины Тьюринга и запуск программы
tm = TuringMachine(tape, alphabet, program)
tm.run('output.txt')