tspan = [0, 5];
y0 = 1;

dydt = @(t, y) (t * y - y * sqrt(1 + t^2)) / (1 + t^2);

[t, y] = ode45(dydt, tspan, y0);

% График решения
figure;
plot(t, y, 'b-', 'LineWidth', 1.5);
xlabel('t');
ylabel('y');
title('Решение первого уравнения');
grid on;

% Фазовый портрет
dy_vals = (t .* y - y .* sqrt(1 + t.^2)) ./ (1 + t.^2);

figure;
plot(y, dy_vals, 'r-', 'LineWidth', 1.5);
xlabel('y');
ylabel("dy/dt");
title('Фазовый портрет первого уравнения');
grid on;