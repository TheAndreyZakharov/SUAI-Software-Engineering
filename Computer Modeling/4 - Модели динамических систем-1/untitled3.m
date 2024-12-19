% Параметры и шаги дискретизации
h_values = [1, 0.5, 0.1, 0.01, 0.001, 0.0001]; % Шаги дискретизации
t_end = 5; % Конечное время
figure;
hold on;

for h = h_values
    N = ceil(t_end / h) + 1; % Количество точек
    t = linspace(0, t_end, N); % Временная шкала
    
    y = zeros(1, N); % Значения y
    y(1) = 1; % Начальное значение y
    
    for k = 1:N-1
        % Вычисление y(k+1) методом Эйлера
        y_prime = (t(k) * y(k) - y(k) * sqrt(1 + t(k)^2)) / (1 + t(k)^2);
        y(k+1) = y(k) + h * y_prime;
    end
    
    plot(t, y, 'LineWidth', 1.5, 'DisplayName', sprintf('h = %.2f', h));
end

xlabel('t');
ylabel('y');
title('Дискретное решение первого уравнения с разными шагами');
legend show;
grid on;