% Решение системы уравнений методом Эйлера
% dx/dt = 2x - y, dy/dt = x + 2y, x(0) = -1, y(0) = 0

% Начальные условия
x0 = -1; % x(0)
y0 = 0;  % y(0)
tspan = [0, 1]; % Временной интервал

% Шаги дискретизации
h_values = [1, 0.5, 0.1, 0.01];

figure; hold on;

% Цикл по разным шагам дискретизации
for h = h_values
    N = ceil((tspan(2) - tspan(1)) / h) + 1;
    t = linspace(tspan(1), tspan(2), N);
    
    % Инициализация массивов
    x = zeros(1, N);
    y = zeros(1, N);
    
    % Начальные условия
    x(1) = x0;
    y(1) = y0;
    
    % Метод Эйлера
    for n = 1:N-1
        dx = 2 * x(n) - y(n);
        dy = x(n) + 2 * y(n);
        x(n+1) = x(n) + h * dx;
        y(n+1) = y(n) + h * dy;
    end
    
    % Построение графиков x(t) и y(t)
    plot(t, x, 'LineWidth', 1.5, 'DisplayName', sprintf('x(t), h = %.4f', h));
    plot(t, y, '--', 'LineWidth', 1.5, 'DisplayName', sprintf('y(t), h = %.4f', h));
end

xlabel('t');
ylabel('x(t), y(t)');
title('Дискретизация системы уравнений');
legend show;
grid on;