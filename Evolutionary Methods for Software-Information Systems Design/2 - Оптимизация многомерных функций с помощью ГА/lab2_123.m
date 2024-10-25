% Название функции: Функция Эасома
% Оптимум: глобальный минимум; f(x1,x2)=-1; (x1,x2)=(pi,pi).

% Параметры генетического алгоритма
N = 100; % Размер популяции
generations = 100; % Количество поколений
mutationRate = 0.05; % Вероятность мутации
crossoverRate = 0.8; % Вероятность кроссинговера

% Диапазон значений x1 и x2
x_min = -100;
x_max = 100;

% Инициализация начальной популяции
population = (x_max - x_min) * rand(N, 2) + x_min;

% Функция Эасома
fEaso = @(x) -cos(x(:,1)) .* cos(x(:,2)) .* exp(-((x(:,1) - pi).^2 + (x(:,2) - pi).^2));

bestFitnessHistory = zeros(generations, 1);
bestSolution = population(1, :);
bestFitness = fEaso(bestSolution);

for generation = 1:generations
    % Оценка популяции
    fitnessValues = fEaso(population);
    
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

% Вывод результатов для вашего алгоритма
fprintf('Лучшее найденное решение (мой ГА): x1 = %f, x2 = %f\n', bestSolution(1), bestSolution(2));
fprintf('Значение функции в этой точке (мой ГА): %f\n', bestFitness);
fprintf('Известный оптимум: f(x1,x2) = -1 при (x1,x2) = (pi, pi)\n', pi, pi);

% Построение графика функции (сделаем простую визуализацию)
[x1, x2] = meshgrid(linspace(-100, 100, 100), linspace(-100, 100, 100));
z = fEaso([x1(:), x2(:)]);
z = reshape(z, size(x1));

figure;
surf(x1, x2, z);
hold on;

% Отображение текущей популяции
scatter3(population(:, 1), population(:, 2), fEaso(population), 'go', 'filled');

% Отображение найденного экстремума (ваш ГА)
plot3(bestSolution(1), bestSolution(2), bestFitness, 'ro', 'MarkerSize', 10, 'MarkerFaceColor', 'r');

title('Оптимизация функции Эасома с помощью ГА');
xlabel('x1');
ylabel('x2');
zlabel('f(x1,x2)');
grid on;
hold off;

% Встроенный ГА из MATLAB для сравнения
options = optimoptions('ga', 'PopulationSize', N, 'MaxGenerations', generations, ...
    'CrossoverFraction', crossoverRate, 'MutationFcn', @mutationadaptfeasible);
[gaBestSolution, gaBestFitness] = ga(@(x) fEaso(x), 2, [], [], [], [], [x_min x_min], [x_max x_max], [], options);

% Вывод результатов для встроенного ГА
fprintf('Лучшее найденное решение (встроенный ГА): x1 = %f, x2 = %f\n', gaBestSolution(1), gaBestSolution(2));
fprintf('Значение функции в этой точке (встроенный ГА): %f\n', gaBestFitness);

% Добавление найденного решения встроенного ГА на график
hold on;
plot3(gaBestSolution(1), gaBestSolution(2), gaBestFitness, 'bo', 'MarkerSize', 10, 'MarkerFaceColor', 'b');
legend('Поверхность функции', 'Точки популяции', 'Найденный минимум (мой ГА)', 'Найденный минимум (встроенный ГА)');
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
    % Одноточечный кроссинговер
    alpha = rand;
    child1 = alpha * parent1 + (1 - alpha) * parent2;
    child2 = (1 - alpha) * parent1 + alpha * parent2;
end

function mutated = mutate(individual, mutationRate, x_min, x_max)
    % Мутация с заданной вероятностью
    if rand < mutationRate
        mutated = (x_max - x_min) * rand(1, 2) + x_min; % Изменено для 2D
    else
        mutated = individual;
    end
end