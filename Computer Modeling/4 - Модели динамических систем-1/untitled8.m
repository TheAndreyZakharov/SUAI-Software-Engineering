% Начальные условия
y0 = 1;           % y(0)
tspan = [0, 5];   % Временной интервал

% Шаги дискретизации
h_values = [1, 0.5, 0.1, 0.05, 0.01];

% Определение правой части уравнения
dydt = @(t, y) (t * y - y * sqrt(1 + t^2)) / (1 + t^2);

figure; hold on;

% Цикл по разным шагам дискретизации
for h = h_values
    % Число точек дискретизации
    N = ceil((tspan(2) - tspan(1)) / h) + 1;
    t = linspace(tspan(1), tspan(2), N);
    
    % Инициализация массива для y
    y = zeros(1, N);
    y(1) = y0; % Начальное значение
    
    % Метод Эйлера
    for n = 1:N-1
        y(n+1) = y(n) + h * dydt(t(n), y(n));
    end
    
    % Построение графика
    plot(t, y, 'LineWidth', 1.5, 'DisplayName', sprintf('h = %.4f', h));
end

xlabel('t');
ylabel('y');
title('Решение методом Эйлера для различных шагов h');
legend show;
grid on;


% Решение уравнения с ode45
[t_ode, y_ode] = ode45(dydt, tspan, y0);

% График решения
figure;
plot(t_ode, y_ode, 'b-', 'LineWidth', 1.5);
xlabel('t');
ylabel('y');
title('Решение уравнения с помощью ode45');
grid on;


% Вычисление производной y' для фазового портрета
dy_vals = (t_ode .* y_ode - y_ode .* sqrt(1 + t_ode.^2)) ./ (1 + t_ode.^2);

% Построение фазового портрета
figure;
plot(y_ode, dy_vals, 'r-', 'LineWidth', 1.5);
xlabel('y');
ylabel("dy/dt");
title('Фазовый портрет');
grid on;