% Параметры системы
alpha = 2;
beta = 6;
gamma = 1.5;
mu = 2.0;
lambda = 3.16;
delta = 0.9;
T1 = 0.1;
rho = 0.5;

% Управляющее воздействие
control = @(Y1, Y2, Y3) Y1 - rho * Y2 - (Y1 - rho * Y2) / T1;



% Система дифференциальных уравнений с управлением
dynamics = @(t, Y) [
    alpha * Y(2) * Y(3) - gamma * Y(1) + control(Y(1), Y(2), Y(3));
   mu * (Y(2) + Y(3)) - beta * Y(1) * Y(3);
    delta * Y(2) - lambda * Y(3)
];

% Система дифференциальных уравнений без управления
dynamics = @(t, Y) [
    alpha * Y(2) * Y(3) - gamma * Y(1);
    mu * (Y(2) + Y(3)) - beta * Y(1) * Y(3);
    delta * Y(2) - lambda * Y(3)
];



% Начальные условия и временной интервал
Y0 = [0.5; 0.5; 0.5];
tspan = [0 30];

% Решение системы
[t, Y] = ode45(dynamics, tspan, Y0);

% Рассчёт производных
Y_dot = zeros(size(Y));
for i = 1:length(t)
    Y_dot(i, :) = dynamics(t(i), Y(i, :)')';
end

% Построение траекторий и фазовых портретов
figure;


% Траектории Y1, Y2, Y3 от времени
subplot(2, 3, [1, 2, 3]);
plot(t, Y(:, 1), 'r', t, Y(:, 2), 'b', t, Y(:, 3), 'g');
xlabel('Время t');
ylabel('Y_1, Y_2, Y_3');
legend('Y_1', 'Y_2', 'Y_3');
title('Траектории Y_1, Y_2, Y_3');


% Фазовый портрет Y1 vs Y1'
subplot(2, 3, 4);
plot(Y(:, 1), Y_dot(:, 1), 'r');
xlabel('Y_1'); ylabel("Y'_1");
title("Фазовый портрет Y_1 vs Y'_1");


% Фазовый портрет Y2 vs Y2'
subplot(2, 3, 5);
plot(Y(:, 2), Y_dot(:, 2), 'b');
xlabel('Y_2'); ylabel("Y'_2");
title("Фазовый портрет Y_2 vs Y'_2");


% Фазовый портрет Y3 vs Y3'
subplot(2, 3, 6);
plot(Y(:, 3), Y_dot(:, 3), 'g');
xlabel('Y_3'); ylabel("Y'_3");
title("Фазовый портрет Y_3 vs Y'_3");



