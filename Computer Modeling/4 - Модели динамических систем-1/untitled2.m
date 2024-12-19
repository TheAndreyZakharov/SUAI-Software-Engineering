% Решение системы уравнений:
% dx/dt = 2x - y, dy/dt = x + 2y, x(0) = -1, y(0) = 0
tspan = [0, 1]; % Интервал времени
xy0 = [-1; 0]; % Начальные условия [x(0); y(0)]

% Определение правой части системы
dxy = @(t, xy) [2 * xy(1) - xy(2); xy(1) + 2 * xy(2)];

% Решение системы с использованием метода Рунге-Кутты 4-го порядка
options = odeset('RelTol', 1e-8, 'AbsTol', 1e-10);  % Установка параметров точности
[t, xy] = ode45(dxy, tspan, xy0, options);

% Построение графиков x(t) и y(t)
figure;
plot(t, xy(:, 1), 'r-', 'LineWidth', 1.5); hold on;
plot(t, xy(:, 2), 'g-', 'LineWidth', 1.5);
xlabel('t');
ylabel('x(t), y(t)');
legend('x(t)', 'y(t)');
title('Решение системы уравнений');
grid on;