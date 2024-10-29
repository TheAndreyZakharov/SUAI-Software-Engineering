% Параметры
N = 14;
T1 = N;
T2 = N + 100;
lambda1 = (N + 8) / (N + 24);
lambda2 = (N + 9) / (N + 25);

% Функция генерации пуассоновского потока
function times = generate_poisson_process(T1, T2, lambda)
    time = T1;
    times = [];
    while time < T2
        u = rand();
        interval = -log(u) / lambda;  % Генерация интервала
        time = time + interval;
        if time < T2
            times = [times, time];
        end
    end
end

% Генерация потоков для двух разных λ
times1 = generate_poisson_process(T1, T2, lambda1);
times2 = generate_poisson_process(T1, T2, lambda2);

% Графическое представление
figure;
stairs(times1, 1:length(times1), 'DisplayName', sprintf('\\lambda1 = %.2f', lambda1));
hold on;
stairs(times2, 1:length(times2), 'DisplayName', sprintf('\\lambda2 = %.2f', lambda2));
title('Пуассоновские потоки');
xlabel('Время');
ylabel('Количество событий');
legend('show');
hold off;