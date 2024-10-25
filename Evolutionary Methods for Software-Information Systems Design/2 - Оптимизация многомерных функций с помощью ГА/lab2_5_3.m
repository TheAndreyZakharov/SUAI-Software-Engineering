% Параметры генетического алгоритма
N = 100; % Размер популяции
generations = 100; % Количество поколений
mutationRate = 0.05; % Вероятность мутации
crossoverRate = 0.8; % Вероятность кроссинговера

% Диапазон значений x
x_min = -100; 
x_max = 100; 

% Инициализация начальной популяции (трехмерная)
population = (x_max - x_min) * rand(N, 3) + x_min;

% Функция Эйзома, которую оптимизируем
fitnessFunction = @(x) -cos(x(:, 1)) .* cos(x(:, 2)) .* cos(x(:, 3)) .* ...
    exp(-((x(:, 1) - pi).^2 + (x(:, 2) - pi).^2 + (x(:, 3) - pi).^2));

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
fprintf('Лучшее найденное решение (мой ГА): x1 = %f, x2 = %f, x3 = %f\n', bestSolution(1), bestSolution(2), bestSolution(3));
fprintf('Значение функции в этой точке (мой ГА): %f\n', bestFitness);
fprintf('Время выполнения (мой ГА): %f секунд\n', executionTime);

% Встроенный ГА из MATLAB для сравнения
options = optimoptions('ga', 'PopulationSize', N, 'MaxGenerations', generations, ...
    'CrossoverFraction', crossoverRate, 'MutationFcn', @mutationadaptfeasible);
tic; % Начало отсчета времени для встроенного ГА
[gaBestSolution, gaBestFitness] = ga(@(x) fitnessFunction([x(1), x(2), x(3)]), 3, [], [], [], [], ...
    [x_min, x_min, x_min], [x_max, x_max, x_max], [], options);
gaExecutionTime = toc; % Время выполнения для встроенного ГА

% Вывод результатов для встроенного ГА
fprintf('Лучшее найденное решение (встроенный ГА): x1 = %f, x2 = %f, x3 = %f\n', gaBestSolution(1), gaBestSolution(2), gaBestSolution(3));
fprintf('Значение функции в этой точке (встроенный ГА): %f\n', gaBestFitness);
fprintf('Время выполнения (встроенный ГА): %f секунд\n', gaExecutionTime);

% Функции для отбора, кроссинговера и мутации (ваш ГА)
function parents = tournamentSelection(population, fitnessValues)
    % Турнирный отбор двух особей
    parents = zeros(2, 3); % Массив для хранения двух родителей
    for i = 1:2
        idx = randi(length(population)); % Случайный индекс
        parents(i, :) = population(idx, :);
    end
end

function [child1, child2] = crossover(parent1, parent2)
    % Одноточечный кроссинговер
    alpha = rand(1, 3);
    child1 = alpha .* parent1 + (1 - alpha) .* parent2;
    child2 = (1 - alpha) .* parent1 + alpha .* parent2;
end

function mutated = mutate(individual, mutationRate, x_min, x_max)
    % Мутация с заданной вероятностью
    if rand < mutationRate
        mutated = (x_max - x_min) * rand(1, 3) + x_min; % Изменен для 3D
    else
        mutated = individual;
    end
end