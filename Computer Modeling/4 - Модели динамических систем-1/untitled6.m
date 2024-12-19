% Название модели
modelName = 'second_equation_model_adjusted'; % Уникальное имя модели
new_system(modelName); % Создание новой модели

% Открываем модель
open_system(modelName);

%% Добавление блоков в модель Simulink

% Позиции блоков (x, y, ширина, высота)
blockSize = [30, 30]; % Размер блоков

% Добавляем интеграторы для x и y
add_block('simulink/Continuous/Integrator', [modelName '/Integrator_x'], ...
    'Position', [100, 100, 100+blockSize(1), 100+blockSize(2)], ...
    'InitialCondition', '0.5'); % Начальное условие для x(t)

add_block('simulink/Continuous/Integrator', [modelName '/Integrator_y'], ...
    'Position', [100, 200, 100+blockSize(1), 200+blockSize(2)], ...
    'InitialCondition', '0'); % Начальное условие для y(t)

% Добавляем сумматоры для dx/dt и dy/dt
add_block('simulink/Math Operations/Sum', [modelName '/Sum_x'], ...
    'Position', [250, 100, 250+blockSize(1), 100+blockSize(2)], ...
    'Inputs', '++');

add_block('simulink/Math Operations/Sum', [modelName '/Sum_y'], ...
    'Position', [250, 200, 250+blockSize(1), 200+blockSize(2)], ...
    'Inputs', '+-');

% Добавляем коэффициенты (Gain) для x и y
add_block('simulink/Math Operations/Gain', [modelName '/Gain_4x'], ...
    'Position', [400, 50, 400+blockSize(1), 50+blockSize(2)], ...
    'Gain', '4'); % Увеличенный коэффициент для x

add_block('simulink/Math Operations/Gain', [modelName '/Gain_1y'], ...
    'Position', [400, 150, 400+blockSize(1), 150+blockSize(2)], ...
    'Gain', '1'); % Коэффициент для y

add_block('simulink/Math Operations/Gain', [modelName '/Gain_neg05x'], ...
    'Position', [400, 250, 400+blockSize(1), 250+blockSize(2)], ...
    'Gain', '-0.5'); % Отрицательный коэффициент для x

add_block('simulink/Math Operations/Gain', [modelName '/Gain_2y'], ...
    'Position', [400, 350, 400+blockSize(1), 350+blockSize(2)], ...
    'Gain', '2'); % Увеличенный коэффициент для y

% Добавляем линии соединений
% Линии для dx/dt = 4x - y
add_line(modelName, 'Integrator_x/1', 'Gain_4x/1');
add_line(modelName, 'Integrator_y/1', 'Gain_1y/1');
add_line(modelName, 'Gain_4x/1', 'Sum_x/1');
add_line(modelName, 'Gain_1y/1', 'Sum_x/2');
add_line(modelName, 'Sum_x/1', 'Integrator_x/1', 'autorouting', 'on');

% Линии для dy/dt = -0.5x - 2y
add_line(modelName, 'Integrator_x/1', 'Gain_neg05x/1');
add_line(modelName, 'Integrator_y/1', 'Gain_2y/1');
add_line(modelName, 'Gain_neg05x/1', 'Sum_y/1');
add_line(modelName, 'Gain_2y/1', 'Sum_y/2');
add_line(modelName, 'Sum_y/1', 'Integrator_y/1', 'autorouting', 'on');

% Добавляем блок Scope для отображения x(t) и y(t)
add_block('simulink/Sinks/Scope', [modelName '/Scope'], ...
    'Position', [600, 150, 650, 200]);

% Настройка Scope для отображения двух сигналов
set_param([modelName, '/Scope'], 'NumInputPorts', '2'); % Установка двух входов

% Соединяем Scope с выходами интеграторов
add_line(modelName, 'Integrator_x/1', 'Scope/1'); % Подключаем x(t)
add_line(modelName, 'Integrator_y/1', 'Scope/2'); % Подключаем y(t)

%% Сохранение и запуск модели
save_system(modelName);
disp('Модель Simulink успешно создана.');

% Открываем модель
open_system(modelName);

% Запуск симуляции на 5 секунд
simOut = sim(modelName, 'StopTime', '5');

% Отображение результатов
disp('Симуляция завершена. Проверьте результаты на Scope.');