% Параметры задачи
N = 14;  % номер студента
T1 = N;
T2 = N + 100;
lambda1 = (N + 8) / (N + 24);
lambda2 = (N + 9) / (N + 25);

% Функция генерации пуассоновского потока
function times = generate_poisson_process(lambda_param, T1, T2)
    times = [];
    t = T1;
    while t < T2
        U = rand();  % Генерируем случайное число U из (0, 1)
        t = t + (-log(U) / lambda_param);  % Экспоненциальное распределение
        if t < T2
            times = [times, t];  % Добавляем событие
        end
    end
end

% Генерация двух потоков
times1 = generate_poisson_process(lambda1, T1, T2);
times2 = generate_poisson_process(lambda2, T1, T2);

% Вывод результатов
disp('Поток 1:');
disp(times1);
disp('Поток 2:');
disp(times2);