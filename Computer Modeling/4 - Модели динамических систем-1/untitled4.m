% Параметры и шаги дискретизации
h_values = [1, 0.5, 0.1, 0.01, 0.001, 0.0001]; % Шаги дискретизации
t_end = 5; % Конечное время
figure;
hold on;

for h = h_values
    N = ceil(t_end / h) + 1; % Количество точек
    t = linspace(0, t_end, N); % Временная шкала

    x = zeros(1, N); % Значения x
    y = zeros(1, N); % Значения y
    x(1) = -1; % Начальное значение x
    y(1) = 0; % Начальное значение y

    for k = 1:N-1
        % Вычисление x(k+1) и y(k+1) методом Эйлера
        x_next = x(k) + h * (2*x(k) - y(k));
        y_next = y(k) + h * (x(k) + 2*y(k));
        x(k+1) = x_next;
        y(k+1) = y_next;
    end

    plot(t, x, 'LineWidth', 1.5, 'DisplayName', sprintf('h = %.2f', h));
end

xlabel('t');
ylabel('x');
title('Дискретное решение второго уравнения с разными шагами');
legend show;
grid on;