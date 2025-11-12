%% Генерация данных для задачи "Конкурентное окружение"
rng(2025);                      % можно убрать для полностью случайного набора
N = 15;                         % по 15 наблюдений на класс
clip = @(x) max(1, min(10, x)); % ограничение в диапазоне [1..10]

% Класс 1 (благоприятная): высокая аудитория, низкие угрозы
A1 = clip( 8.5 + 1.0*randn(N,1));  % Audience (высокая)
NE1= clip( 3.0 + 1.0*randn(N,1));  % NewEntrants (низкая)
S1 = clip( 3.0 + 1.0*randn(N,1));  % Suppliers (низкая зависимость)
Sub1= clip( 3.5 + 1.0*randn(N,1)); % Substitutes (низкая)
R1 = clip( 3.0 + 1.2*randn(N,1));  % Rivalry (низкая)

% Класс 3 (неблагоприятная): низкая аудитория, высокие угрозы
A3 = clip( 3.0 + 1.0*randn(N,1));
NE3= clip( 8.0 + 1.0*randn(N,1));
S3 = clip( 8.0 + 1.0*randn(N,1));
Sub3= clip( 7.8 + 1.0*randn(N,1));
R3 = clip( 8.5 + 1.0*randn(N,1));

% Класс 2 (средняя): промежуточные значения, создаём перекрытие классов
A2 = clip( 6.0 + 1.2*randn(N,1));
NE2= clip( 5.0 + 1.2*randn(N,1));
S2 = clip( 5.5 + 1.2*randn(N,1));
Sub2= clip( 5.0 + 1.3*randn(N,1));
R2 = clip( 5.0 + 1.3*randn(N,1));

% Собираем в одну матрицу (порядок классов: 1, 2, 3)
X = [ [A1;  A2;  A3], ...
      [NE1; NE2; NE3], ...
      [S1;  S2;  S3], ...
      [Sub1;Sub2;Sub3], ...
      [R1;  R2;  R3] ];

% Метки классов (categorical с подписями)
Y = categorical([ones(N,1); 2*ones(N,1); 3*ones(N,1)], ...
                [1 2 3], {'благоприятная','средняя','неблагоприятная'});

% Таблица предикторов + целевая переменная
compData = array2table(X, 'VariableNames', ...
   {'Audience','NewEntrants','Suppliers','Substitutes','Rivalry'});
compData.Y = Y;

% Быстрый предпросмотр в 2D (Аудитория vs Конкуренция)
figure('Name','Исходные данные (Audience vs Rivalry)');
gscatter(compData.Audience, compData.Rivalry, compData.Y);
xlabel('Audience (влияние аудитории)'); ylabel('Rivalry (уровень борьбы)');
grid on;

% (необязательно) Сохранить таблицу на диск
% writetable(compData, 'compData.csv');