% Параметры генетического алгоритма
populationSizes = [50, 100, 150]; % Размеры популяции для тестирования
mutationRates = [0.01, 0.05, 0.1]; % Вероятности мутации для тестирования
crossoverRates = [0.6, 0.8, 1.0]; % Вероятности кроссинговера для тестирования
maxStagnation = 10; % Максимальное количество поколений без улучшения
maxGenerations = 100; % Максимальное количество поколений

% Диапазон значений x
x_min = -100;
x_max = 100;

% Функция, которую оптимизируем (функция Эасома)
fitnessFunction = @(x) -cos(x(:,1)) .* cos(x(:,2)) .* exp(-((x(:,1) - pi).^2 + (x(:,2) - pi).^2));

% Для хранения результатов
results = struct('N', [], 'mutationRate', [], 'crossoverRate', [], 'bestSolution', [], 'bestFitness', [], 'elapsedTime', [], 'generations', []);

% Проход по всем параметрам
for N = populationSizes
    for mutationRate = mutationRates
        for crossoverRate = crossoverRates
            % Инициализация начальной популяции
            population = (x_max - x_min) * rand(N, 2) + x_min;

            bestFitnessHistory = zeros(maxGenerations, 1);
            bestSolution = population(1, :);
            bestFitness = fitnessFunction(population(1, :));

            stagnationCounter = 0;

            % Начало измерения времени
            tic;

            for generation = 1:maxGenerations
                % Оценка популяции
                fitnessValues = fitnessFunction(population);
                
                % Поиск лучшего решения
                [currentBestFitness, bestIdx] = min(fitnessValues);
                if currentBestFitness < bestFitness
                    bestFitness = currentBestFitness;
                    bestSolution = population(bestIdx, :);
                    stagnationCounter = 0; % Сброс счетчика застоя
                else
                    stagnationCounter = stagnationCounter + 1; % Увеличение счетчика застоя
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
                
                % Проверка условий остановки
                if stagnationCounter >= maxStagnation
                    fprintf('Остановка на поколении %d для N=%d, mutationRate=%.2f, crossoverRate=%.2f\n', generation, N, mutationRate, crossoverRate);
                    break;
                end
            end

            % Конец измерения времени
            elapsedTime = toc;

            % Сохранение результатов
            results(end + 1) = struct('N', N, 'mutationRate', mutationRate, 'crossoverRate', crossoverRate, ...
                                       'bestSolution', bestSolution, 'bestFitness', bestFitness, ...
                                       'elapsedTime', elapsedTime, 'generations', generation);
        end
    end
end

% Визуализация результатов для числа особей в популяции
figure;
subplot(3, 1, 1);
hold on;
for mutationRate = mutationRates
    idx = find([results.mutationRate] == mutationRate);
    plot([results(idx).N], [results(idx).bestFitness], '-o', 'DisplayName', sprintf('Mutation Rate: %.2f', mutationRate));
end
xlabel('Число особей в популяции');
ylabel('Лучшее значение фитнеса');
title('Зависимость лучшего значения фитнеса от числа особей в популяции');
legend;
grid on;

subplot(3, 1, 2);
hold on;
for mutationRate = mutationRates
    idx = find([results.mutationRate] == mutationRate);
    plot([results(idx).N], [results(idx).elapsedTime], '-o', 'DisplayName', sprintf('Mutation Rate: %.2f', mutationRate));
end
xlabel('Число особей в популяции');
ylabel('Время выполнения (секунды)');
title('Зависимость времени выполнения от числа особей в популяции');
legend;
grid on;

subplot(3, 1, 3);
hold on;
for mutationRate = mutationRates
    idx = find([results.mutationRate] == mutationRate);
    plot([results(idx).N], [results(idx).generations], '-o', 'DisplayName', sprintf('Mutation Rate: %.2f', mutationRate));
end
xlabel('Число особей в популяции');
ylabel('Количество поколений');
title('Зависимость количества поколений от числа особей в популяции');
legend;
grid on;

% Визуализация результатов для вероятности кроссинговера
figure;
subplot(3, 1, 1);
hold on;
for crossoverRate = crossoverRates
    idx = find([results.crossoverRate] == crossoverRate);
    plot([results(idx).mutationRate], [results(idx).bestFitness], '-o', 'DisplayName', sprintf('Crossover Rate: %.2f', crossoverRate));
end
xlabel('Вероятность мутации');
ylabel('Лучшее значение фитнеса');
title('Зависимость лучшего значения фитнеса от вероятности кроссинговера');
legend;
grid on;

subplot(3, 1, 2);
hold on;
for crossoverRate = crossoverRates
    idx = find([results.crossoverRate] == crossoverRate);
    plot([results(idx).mutationRate], [results(idx).elapsedTime], '-o', 'DisplayName', sprintf('Crossover Rate: %.2f', crossoverRate));
end
xlabel('Вероятность мутации');
ylabel('Время выполнения (секунды)');
title('Зависимость времени выполнения от вероятности кроссинговера');
legend;
grid on;

subplot(3, 1, 3);
hold on;
for crossoverRate = crossoverRates
    idx = find([results.crossoverRate] == crossoverRate);
    plot([results(idx).mutationRate], [results(idx).generations], '-o', 'DisplayName', sprintf('Crossover Rate: %.2f', crossoverRate));
end
xlabel('Вероятность мутации');
ylabel('Количество поколений');
title('Зависимость количества поколений от вероятности кроссинговера');
legend;
grid on;

% Визуализация результатов для вероятности мутации
figure;
subplot(3, 1, 1);
hold on;
for N = populationSizes
    idx = find([results.N] == N);
    plot([results(idx).mutationRate], [results(idx).bestFitness], '-o', 'DisplayName', sprintf('Population Size: %d', N));
end
xlabel('Вероятность мутации');
ylabel('Лучшее значение фитнеса');
title('Зависимость лучшего значения фитнеса от вероятности мутации');
legend;
grid on;

subplot(3, 1, 2);
hold on;
for N = populationSizes
    idx = find([results.N] == N);
    plot([results(idx).mutationRate], [results(idx).elapsedTime], '-o', 'DisplayName', sprintf('Population Size: %d', N));
end
xlabel('Вероятность мутации');
ylabel('Время выполнения (секунды)');
title('Зависимость времени выполнения от вероятности мутации');
legend;
grid on;

subplot(3, 1, 3);
hold on;
for N = populationSizes
    idx = find([results.N] == N);
    plot([results(idx).mutationRate], [results(idx).generations], '-o', 'DisplayName', sprintf('Population Size: %d', N));
end
xlabel('Вероятность мутации');
ylabel('Количество поколений');
title('Зависимость количества поколений от вероятности мутации');
legend;
grid on;

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
    % Одноточечный кроссинговер
    alpha = rand;
    child1 = alpha * parent1 + (1 - alpha) * parent2;
    child2 = alpha * parent2 + (1 - alpha) * parent1;
end

function mutated = mutate(individual, mutationRate, x_min, x_max)
    % Мутация
    if rand < mutationRate
        individual = individual + (x_max - x_min) * (rand(size(individual)) - 0.5);
    end
    % Ограничение на диапазон
    mutated = max(min(individual, x_max), x_min);
end