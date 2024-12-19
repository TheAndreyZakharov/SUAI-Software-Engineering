% Очистка рабочей среды и закрытие моделей
clear; clc; close all;
bdclose all;

%% Название модели
modelName = 'linearSystemModel';
new_system(modelName); % Создание новой модели
open_system(modelName);

%% Параметры системы
% dx/dt = 2x - y
% dy/dt = x + 2y

% Начальные условия
x0 = -1; % x(0)
y0 = 0;  % y(0)

% Размеры блоков для удобства размещения
blockWidth = 50;
blockHeight = 30;

% Позиции блоков
x_pos = 100; y_pos = 100; % Интеграторы
x_out_pos = x_pos + 300; % Выход x
y_out_pos = y_pos + 200; % Выход y

%% Добавление блоков

% Интеграторы для x и y
add_block('simulink/Continuous/Integrator', [modelName '/Integrator_x'], ...
    'Position', [x_pos, y_pos, x_pos + blockWidth, y_pos + blockHeight], ...
    'InitialCondition', num2str(x0));

add_block('simulink/Continuous/Integrator', [modelName '/Integrator_y'], ...
    'Position', [x_pos, y_pos + 100, x_pos + blockWidth, y_pos + 100 + blockHeight], ...
    'InitialCondition', num2str(y0));

% Сумматоры для dx/dt и dy/dt
add_block('simulink/Math Operations/Sum', [modelName '/Sum_x'], ...
    'Inputs', '++', ...
    'Position', [x_pos - 100, y_pos, x_pos - 100 + blockWidth, y_pos + blockHeight]);

add_block('simulink/Math Operations/Sum', [modelName '/Sum_y'], ...
    'Inputs', '++', ...
    'Position', [x_pos - 100, y_pos + 100, x_pos - 100 + blockWidth, y_pos + 100 + blockHeight]);

% Gain блоки для коэффициентов
add_block('simulink/Math Operations/Gain', [modelName '/Gain_2x'], ...
    'Gain', '2', ...
    'Position', [x_pos - 200, y_pos, x_pos - 200 + blockWidth, y_pos + blockHeight]);

add_block('simulink/Math Operations/Gain', [modelName '/Gain_neg_y'], ...
    'Gain', '-1', ...
    'Position', [x_pos - 200, y_pos + 50, x_pos - 200 + blockWidth, y_pos + 50 + blockHeight]);

add_block('simulink/Math Operations/Gain', [modelName '/Gain_x'], ...
    'Gain', '1', ...
    'Position', [x_pos - 200, y_pos + 100, x_pos - 200 + blockWidth, y_pos + 100 + blockHeight]);

add_block('simulink/Math Operations/Gain', [modelName '/Gain_2y'], ...
    'Gain', '2', ...
    'Position', [x_pos - 200, y_pos + 150, x_pos - 200 + blockWidth, y_pos + 150 + blockHeight]);

% Scopes для визуализации результатов
add_block('simulink/Sinks/Scope', [modelName '/Scope_x'], ...
    'Position', [x_out_pos, y_pos, x_out_pos + blockWidth, y_pos + blockHeight]);

add_block('simulink/Sinks/Scope', [modelName '/Scope_y'], ...
    'Position', [x_out_pos, y_pos + 100, x_out_pos + blockWidth, y_pos + 100 + blockHeight]);

%% Соединение блоков

% Сумматоры -> Интеграторы
add_line(modelName, 'Sum_x/1', 'Integrator_x/1');
add_line(modelName, 'Sum_y/1', 'Integrator_y/1');

% Интеграторы -> Scopes
add_line(modelName, 'Integrator_x/1', 'Scope_x/1');
add_line(modelName, 'Integrator_y/1', 'Scope_y/1');

% Gain блоки -> Сумматоры (dx/dt = 2x - y)
add_line(modelName, 'Gain_2x/1', 'Sum_x/1');
add_line(modelName, 'Gain_neg_y/1', 'Sum_x/2');

% Gain блоки -> Сумматоры (dy/dt = x + 2y)
add_line(modelName, 'Gain_x/1', 'Sum_y/1');
add_line(modelName, 'Gain_2y/1', 'Sum_y/2');

% Обратная связь от интеграторов -> Gain блоки
add_line(modelName, 'Integrator_x/1', 'Gain_2x/1');
add_line(modelName, 'Integrator_x/1', 'Gain_x/1');
add_line(modelName, 'Integrator_y/1', 'Gain_neg_y/1');
add_line(modelName, 'Integrator_y/1', 'Gain_2y/1');

%% Сохранение и запуск модели
save_system(modelName);
disp('Модель Simulink успешно создана и сохранена.');

% Запуск симуляции
simOut = sim(modelName, 'StartTime', '0', 'StopTime', '10');

% Открытие модели
open_system(modelName);