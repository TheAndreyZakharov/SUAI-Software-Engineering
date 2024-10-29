syms x C1 C2

% Общее решение уравнения
y_general = (x^2)/2 + C1*x + C2;

% Граничные условия
boundary_eq1 = subs(y_general, x, pi/4) == -log(sqrt(2));
boundary_eq2 = subs(y_general, x, pi/2) == 0;

% Решаем систему уравнений для C1 и C2
constants = solve([boundary_eq1, boundary_eq2], [C1, C2]);

% Подставляем найденные константы в общее решение
y_solution = subs(y_general, constants);

% Отображаем решение
disp('Решение:');
disp(vpa(y_solution));

% Визуализация
fplot(matlabFunction(y_solution), [pi/4, pi/2]);
title('Решение задачи оптимизации');
xlabel('x');
ylabel('y(x)');
grid on;