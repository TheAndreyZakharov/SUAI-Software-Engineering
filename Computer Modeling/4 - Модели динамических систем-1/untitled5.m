% Открываем новую модель Simulink
modelName = 'my_model_fixed';
open_system(new_system(modelName));

% Блок Constant (вместо Clock)
add_block('simulink/Sources/Constant', [modelName, '/Time']);
set_param([modelName, '/Time'], 'Value', '0.5', 'Position', [50, 50, 100, 100]);

% Блок Интегратора для решения уравнения
add_block('simulink/Continuous/Integrator', [modelName, '/Integrator']);
set_param([modelName, '/Integrator'], 'Position', [200, 50, 250, 100]);

% Блок для вычисления sqrt(1 + t^2)
add_block('simulink/Math Operations/Math Function', [modelName, '/Sqrt']);
set_param([modelName, '/Sqrt'], 'Function', 'sqrt', 'Position', [50, 150, 100, 200]);

% Блок для возведения t^2
add_block('simulink/Math Operations/Product', [modelName, '/Square']);
set_param([modelName, '/Square'], 'Position', [50, 100, 100, 150]);

% Блок для 1 + t^2
add_block('simulink/Math Operations/Sum', [modelName, '/Sum1']);
set_param([modelName, '/Sum1'], 'Inputs', '|++', 'Position', [150, 100, 200, 150]);

% Блок для t * y
add_block('simulink/Math Operations/Product', [modelName, '/Product1']);
set_param([modelName, '/Product1'], 'Position', [150, 200, 200, 250]);

% Блок для y * sqrt(1 + t^2)
add_block('simulink/Math Operations/Product', [modelName, '/Product2']);
set_param([modelName, '/Product2'], 'Position', [150, 250, 200, 300]);

% Блок для t * y - y * sqrt(1 + t^2)
add_block('simulink/Math Operations/Sum', [modelName, '/Sum2']);
set_param([modelName, '/Sum2'], 'Inputs', '|+-', 'Position', [250, 200, 300, 250]);

% Блок для деления на (1 + t^2)
add_block('simulink/Math Operations/Divide', [modelName, '/Divide']);
set_param([modelName, '/Divide'], 'Position', [300, 250, 350, 300]);

% Блок Scope для графика решения
add_block('simulink/Sinks/Scope', [modelName, '/Scope']);
set_param([modelName, '/Scope'], 'Position', [400, 50, 450, 100]);

% Блок XY Graph для фазового портрета
add_block('simulink/Sinks/XY Graph', [modelName, '/XY Graph']);
set_param([modelName, '/XY Graph'], 'Position', [400, 150, 450, 200]);

% Соединяем блоки

% Подключаем блоки для вычисления 1 + t^2
add_line(modelName, 'Time/1', 'Square/1');  % t -> t^2
add_line(modelName, 'Square/1', 'Sum1/2'); % t^2 -> 1 + t^2
add_block('simulink/Sources/Constant', [modelName, '/Constant_One']);
set_param([modelName, '/Constant_One'], 'Value', '1', 'Position', [100, 50, 150, 100]);
add_line(modelName, 'Constant_One/1', 'Sum1/1'); % 1 -> 1 + t^2
add_line(modelName, 'Sum1/1', 'Sqrt/1');  % 1 + t^2 -> sqrt(1 + t^2)

% Вычисляем t * y
add_line(modelName, 'Time/1', 'Product1/1'); % t
add_line(modelName, 'Integrator/1', 'Product1/2'); % y

% Вычисляем y * sqrt(1 + t^2)
add_line(modelName, 'Integrator/1', 'Product2/1'); % y
add_line(modelName, 'Sqrt/1', 'Product2/2');       % sqrt(1 + t^2)

% Подключаем к сумматору t * y - y * sqrt(1 + t^2)
add_line(modelName, 'Product1/1', 'Sum2/1'); % t * y
add_line(modelName, 'Product2/1', 'Sum2/2'); % - y * sqrt(1 + t^2)

% Деление на (1 + t^2)
add_line(modelName, 'Sum2/1', 'Divide/1'); % числитель
add_line(modelName, 'Sum1/1', 'Divide/2'); % знаменатель

% Связываем делитель с интегратором
add_line(modelName, 'Divide/1', 'Integrator/1'); % dy/dt -> y

% Подключаем Scope
add_line(modelName, 'Integrator/1', 'Scope/1'); % y -> Scope

% Подключаем XY Graph для фазового портрета
add_line(modelName, 'Integrator/1', 'XY Graph/1'); % y -> ось X
add_line(modelName, 'Divide/1', 'XY Graph/2');     % dy/dt -> ось Y

% Настраиваем начальное условие интегратора
set_param([modelName, '/Integrator'], 'InitialCondition', '1');

% Настраиваем параметры моделирования
set_param(modelName, 'Solver', 'ode45', 'StartTime', '0', 'StopTime', '10', 'MaxStep', '0.01');

% Запускаем моделирование
sim(modelName);

% Открываем Scope
open_system([modelName, '/Scope']);