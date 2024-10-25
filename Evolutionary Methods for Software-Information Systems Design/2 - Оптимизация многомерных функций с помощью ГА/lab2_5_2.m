% Параметры генетического алгоритма
N = 100; % Размер популяции
generations = 100; % Количество поколений
mutationRate = 0.05; % Вероятность мутации
crossoverRate = 0.8; % Вероятность кроссинговера

% Диапазон значений x
x_min = -100; % Измененный диапазон
x_max = 100; % Измененный диапазон

% Инициализация начальной популяции (двумерная)
population = (x_max - x_min) * rand(N, 2) + x_min;

% Функция, которую оптимизируем (функция Эасома)
fitnessFunction = @(x) -cos(x(:, 1)) .* cos(x(:, 2)) .* exp(-((x(:, 1) - pi).^2 + (x(:, 2) - pi).^2));

bestFitnessHistory = zeros(generations, 1);
bestSolution = population(1, :);
bestFitness = fitnessFunction(bestSolution);

% Начало отсчета времени
tic;

for generation = 1:generations
    % Оценка популяции
    fitnessValues = fitnessFunction(population);
    
    % Поиск лучшего решения
    [currentBestFitness, bestIdx] = min(fitnessValues);
    if currentBestFitness < bestFitness
        bestFitness = currentBestFitness;
        bestSolution = population(bestIdx, :);
    end
    
    % Селекция: турнирный отбор
    newPopulation = population;
    for i = 1:2:N
        parents = tournamentSelection(population, fitnessValues);
        
        % Кроссинговер
        if rand < crossoverRate
            [child1, child2] = crossover(parents(1, :), parents(2, :));
        else
            child1 = parents(1, :);
            child2 = parents(2, :);
        end
        
        % Мутация
        child1 = mutate(child1, mutationRate, x_min, x_max);
        child2 = mutate(child2, mutationRate, x_min, x_max);
        
        newPopulation(i, :) = child1;
        newPopulation(i + 1, :) = child2;
    end
    
    population = newPopulation;
    bestFitnessHistory(generation) = bestFitness;
end

% Конец отсчета времени
executionTime = toc;

% Вывод результатов для вашего алгоритма
fprintf('Лучшее найденное решение (мой ГА): (%f, %f)\n', bestSolution(1), bestSolution(2));
fprintf('Значение функции в этой точке (мой ГА): %f\n', bestFitness);
fprintf('Время выполнения (мой ГА): %f секунд\n', executionTime);

% Построение графика функции
[x1, x2] = meshgrid(linspace(x_min, x_max, 100), linspace(x_min, x_max, 100));
y_values = fitnessFunction([x1(:), x2(:)]);
y_values = reshape(y_values, size(x1));

figure;
surf(x1, x2, y_values);
hold on;

% Отображение текущей популяции
scatter3(population(:, 1), population(:, 2), fitnessFunction(population), 'go', 'filled');

% Отображение найденного экстремума (ваш ГА)
plot3(bestSolution(1), bestSolution(2), bestFitness, 'ro', 'MarkerSize', 10, 'MarkerFaceColor', 'r');

title('Оптимизация функции Эасома с помощью ГА');
xlabel('x1');
ylabel('x2');
zlabel('f(x1, x2)');
legend('Функция', 'Точки популяции', 'Найденный минимум (мой ГА)');
grid on;
hold off;

% Встроенный ГА из MATLAB для сравнения
options = optimoptions('ga', 'PopulationSize', N, 'MaxGenerations', generations, ...
    'CrossoverFraction', crossoverRate, 'MutationFcn', @mutationadaptfeasible);
tic; % Начало отсчета времени для встроенного ГА
[gaBestSolution, gaBestFitness] = ga(@(x) -fitnessFunction(x), 2, [], [], [], [], ...
    [x_min, x_min], [x_max, x_max], [], options);
gaExecutionTime = toc; % Время выполнения для встроенного ГА

% Вывод результатов для встроенного ГА
fprintf('Лучшее найденное решение (встроенный ГА): (%f, %f)\n', gaBestSolution(1), gaBestSolution(2));
fprintf('Значение функции в этой точке (встроенный ГА): %f\n', -gaBestFitness); % Знак минус, т.к. мы максимизируем
fprintf('Время выполнения (встроенный ГА): %f секунд\n', gaExecutionTime);

% Добавление найденного решения встроенного ГА на график
hold on;
plot3(gaBestSolution(1), gaBestSolution(2), -gaBestFitness, 'bo', 'MarkerSize', 10, 'MarkerFaceColor', 'b');
legend('Функция', 'Точки популяции', 'Найденный минимум (мой ГА)', 'Найденный минимум (встроенный ГА)');
hold off;

% Функции для отбора, кроссинговера и мутации (ваш ГА)
function parents = tournamentSelection(population, fitnessValues)
    % Турнирный отбор двух особей
    idx1 = randi(length(population));
    idx2 = randi(length(population));
    if fitnessValues(idx1) < fitnessValues(idx2)
        parents(1, :) = population(idx1, :);
    else
        parents(1, :) = population(idx2, :);
    end
    
    idx1 = randi(length(population));
    idx2 = randi(length(population));
    if fitnessValues(idx1) < fitnessValues(idx2)
        parents(2, :) = population(idx1, :);
    else
        parents(2, :) = population(idx2, :);
    end
end

function [child1, child2] = crossover(parent1, parent2)
    % Двухточечный кроссинговер
    alpha = rand(2, 1);
    child1 = alpha(1) * parent1 + (1 - alpha(1)) * parent2;
    child2 = (1 - alpha(2)) * parent1 + alpha(2) * parent2;
end

function mutated = mutate(individual, mutationRate, x_min, x_max)
    % Мутация с заданной вероятностью
    if rand < mutationRate
        mutated = (x_max - x_min) * rand(1, 2) + x_min; % Изменен для 2D
    else
        mutated = individual;
    end
end