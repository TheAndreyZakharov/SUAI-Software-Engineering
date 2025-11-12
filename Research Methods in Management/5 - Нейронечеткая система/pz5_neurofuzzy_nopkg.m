clear; clc; close all; rng(2025);

outDir = 'output_PZ5'; if ~exist(outDir,'dir'), mkdir(outDir); end
logFile   = fullfile(outDir,'PZ5_results.txt');
diaryFile = fullfile(outDir,'PZ5_log.txt');

% включаем «дневник» командного окна
diary(diaryFile);
fid = fopen(logFile,'w');

banner('СТАРТ PZ-5 (NEURO-FUZZY, без тулбоксов)');

%% ========================== ЧАСТЬ A. НЕП ===============================
banner('Часть A. НЕП (регрессия)');

NEP = [ ...
4  2  6  9  4;  9 10  1  5  7;  9  2  3  1  3;  1  2  3  1  1;  4  4  6  4  5; ...
4  4  9  5  7;  5  4 10  8  8; 10  3 10  1  8;  7  8 10  5  9;  4  8  4  8  7; ...
2  3  2  4  3;  5  6  4 10  7;  1  3  1  9  4;  2  3  8  7  5;  8  8  2  2  6; ...
8  7  3  5  6;  6  7  6  3  7; 10  7  6  8  9;  8  3  3  9  8;  2  2  8  8  6];

Xn = NEP(:,1:4); yn = NEP(:,5);
trainIdx = 1:14; testIdx = 15:20;
XtrA = Xn(trainIdx,:); ytrA = yn(trainIdx);
XtsA = Xn(testIdx,:);  ytsA = yn(testIdx);

% Рис.4-аналог (train/test точки)
fig = figure('Color','w'); hold on; grid on;
scatter(1:14, yn(1:14), 50,'b','filled');
scatter(15:20, yn(15:20), 60,'r','filled');
xlabel('Номер наблюдения'); ylabel('Eff');
title('NEP: обучающие (синие) и тестовые (красные)'); legend('Train','Test','Location','best');
saveas(fig, fullfile(outDir,'NEP_data_loaded.png')); close(fig);

% --- Параметры FIS/обучения (НЕП, анти-коллапс) ---
numRules     = 5;      % компактнее для 14 обучающих
roi          = 0.8;    % шире МФ
squashFactor = 1.0;    % без доп. «сжатия»
epochs       = 100;     % дольше учим
eps_denom    = 1e-12;
lambda_ridge = 1e-2;
mFuzzy       = 2.0;    % «размягчаем» членства при апдейте центров

% 1) Инициализация центров k-means++ и стартовых сигм
[centA, ~] = simpleKMeansPP_noToolbox(XtrA, numRules, 200);
centA      = uniqueizeCenters(centA, XtrA);
sigA       = initSigmas(XtrA, centA, roi);

% 2) Обучение
trainMSEA = zeros(epochs,1); checkMSEA = zeros(epochs,1);
thetaA = [];
for ep = 1:epochs
    [wbar_tr, w_tr] = firingStrengths(XtrA, centA, sigA, eps_denom);
    [wbar_ts, ~]    = firingStrengths(XtsA, centA, sigA, eps_denom);

    thetaA  = solveConsequentsRidge(wbar_tr, XtrA, ytrA, lambda_ridge);

    yhat_tr = anfisPredict(wbar_tr, XtrA, thetaA);
    yhat_ts = anfisPredict(wbar_ts, XtsA, thetaA);

    trainMSEA(ep) = mean((yhat_tr - ytrA).^2);
    checkMSEA(ep) = mean((yhat_ts - ytsA).^2);

    [centA, sigA] = updatePremiseFCM_soft(XtrA, w_tr, centA, sigA, ...
                                          squashFactor, roi, eps_denom, mFuzzy);
end

% 3) Кривая обучения 
fig = figure('Color','w'); hold on; grid on;
plot(trainMSEA,'-o','LineWidth',1);
plot(checkMSEA,'-s','LineWidth',1);
xlabel('Эпоха'); ylabel('MSE'); legend('Train','Check','Location','northeast');
title('NEP: кривая обучения');
saveas(fig, fullfile(outDir,'NEP_learning.png')); close(fig);

% 4) Тест 
[wb_tsA,~] = firingStrengths(XtsA, centA, sigA, eps_denom);
yhat_tsA = anfisPredict(wb_tsA, XtsA, thetaA);

MAE_A  = mean(abs(yhat_tsA - ytsA));
RMSE_A = sqrt(mean((yhat_tsA - ytsA).^2));
R2_A   = 1 - sum((ytsA - yhat_tsA).^2) / (sum((ytsA - mean(ytsA)).^2) + eps);

fig = figure('Color','w'); hold on; grid on;
plot(ytsA,'k*','MarkerSize',7);
plot(yhat_tsA,'r*','MarkerSize',9);
legend('Истина (тест)','Предсказание');
xlabel('Тестовые образцы'); ylabel('Eff');
title(sprintf('NEP Test: MAE=%.3f, RMSE=%.3f, R^2=%.3f', MAE_A, RMSE_A, R2_A));
saveas(fig, fullfile(outDir,'NEP_test_true_vs_pred.png')); close(fig);

% 5) Просмотр МФ 
inNamesA = {'X1','X2','X3','X4'};
fig = plotRuleMFs(centA, sigA, inNamesA);
saveas(fig, fullfile(outDir,'NEP_rule_mfs.png')); close(fig);

% 5b) Rule Viewer-аналог
x_sampleA = XtsA(1,:);
fig = ruleViewerAnalog(x_sampleA, centA, sigA, thetaA, inNamesA, 'Eff');
saveas(fig, fullfile(outDir,'NEP_rule_viewer_point.png')); close(fig);

% 6) 3D-поверхность
fixValsA = mean(XtrA,1);
fig = plotSurface2D(centA, sigA, thetaA, 1,2, fixValsA, inNamesA, 'Eff');
saveas(fig, fullfile(outDir,'NEP_surface_X1X2.png')); close(fig);

% 7) ЛОГ ПО НЕП
logw(fid, '--- [NEP] Метрики теста ---');
logw(fid, sprintf('MAE  = %.6f', MAE_A));
logw(fid, sprintf('RMSE = %.6f', RMSE_A));
logw(fid, sprintf('R^2  = %.6f', R2_A));
logw(fid, sprintf('\n[NEP] Центры правил:'));
printMatrix(fid, centA);
logw(fid, sprintf('\n[NEP] Сигмы МФ:'));
printMatrix(fid, sigA);
logw(fid, sprintf('\n[NEP] База правил (линейные следствия):'));
ruleStrA = getRuleBaseAsText(thetaA, numel(inNamesA), inNamesA, 'Eff');
logw(fid, ruleStrA);

% 8) CSV
writematrix([ytsA(:), yhat_tsA(:)], fullfile(outDir,'NEP_test_truth_vs_pred.csv'));
writematrix([trainMSEA(:), checkMSEA(:)], fullfile(outDir,'NEP_learning_curves.csv'));

%% =================== ЧАСТЬ B. Компетенции персонала ====================
banner('Часть B. Компетенции персонала (классификация через регрессию)');

clip = @(x) max(1,min(10,x));
N = 20;
R1 = clip(8.0 + 1.0*randn(N,1)); S1 = clip(7.8 + 1.1*randn(N,1));
C1 = clip(7.9 + 1.0*randn(N,1)); A1 = clip(8.2 + 0.9*randn(N,1)); Y1 = ones(N,1);
R2 = clip(3.2 + 1.2*randn(N,1)); S2 = clip(3.5 + 1.1*randn(N,1));
C2 = clip(3.0 + 1.3*randn(N,1)); A2 = clip(3.4 + 1.0*randn(N,1)); Y2 = 2*ones(N,1);

XC = [[R1;R2],[S1;S2],[C1;C2],[A1;A2]];  YC = [Y1;Y2];

idxC = randperm(40); trC = idxC(1:30); tsC = idxC(31:40);
XtrB = XC(trC,:); ytrB = YC(trC);
XtsB = XC(tsC,:); ytsB = YC(tsC);

% Скаттер (1-й против 4-го признака)
fig = figure('Color','w'); hold on; grid on;
mask1 = (YC==1); mask2 = ~mask1;
scatter(XC(mask1,1), XC(mask1,4), 45,'b','filled');
scatter(XC(mask2,1), XC(mask2,4), 55,'r','filled');
xlabel('Руководитель'); ylabel('Самооценка');
title('Компетенции: распределение классов'); legend('Класс 1','Класс 2','Location','best');
saveas(fig, fullfile(outDir,'COMP_data_scatter.png')); close(fig);

% Параметры
numRulesB     = 6;  roiB = 0.5; squashFactorB = 1.25; epochsB = 50;
eps_denomB    = 1e-12; lambda_ridgeB = 1e-3; mFuzzyB = 2.0;

[centB, ~] = simpleKMeansPP_noToolbox(XtrB, numRulesB, 200);
centB      = uniqueizeCenters(centB, XtrB);
sigB       = initSigmas(XtrB, centB, roiB);

trainMSEB = zeros(epochsB,1); checkMSEB = zeros(epochsB,1);
thetaB = [];
for ep = 1:epochsB
    [wbar_trB, w_trB] = firingStrengths(XtrB, centB, sigB, eps_denomB);
    [wbar_tsB, ~]     = firingStrengths(XtsB, centB, sigB, eps_denomB);

    thetaB   = solveConsequentsRidge(wbar_trB, XtrB, ytrB, lambda_ridgeB);
    yhat_trB = anfisPredict(wbar_trB, XtrB, thetaB);
    yhat_tsB = anfisPredict(wbar_tsB, XtsB, thetaB);

    trainMSEB(ep) = mean((yhat_trB - ytrB).^2);
    checkMSEB(ep) = mean((yhat_tsB - ytsB).^2);

    [centB, sigB] = updatePremiseFCM_soft(XtrB, w_trB, centB, sigB, ...
                                          squashFactorB, roiB, eps_denomB, mFuzzyB);
end

% Кривая обучения
fig = figure('Color','w'); hold on; grid on;
plot(trainMSEB,'-o'); plot(checkMSEB,'-s');
xlabel('Эпоха'); ylabel('MSE'); legend('Train','Check','Location','best');
title('Компетенции: кривая обучения');
saveas(fig, fullfile(outDir,'COMP_learning.png')); close(fig);

% Классификация из регрессии
[wb_tsB, ~] = firingStrengths(XtsB, centB, sigB, eps_denomB);
yregB = anfisPredict(wb_tsB, XtsB, thetaB);
yhatB = 1 + (yregB > 1.5);      % при желании подстрой: 1.6–1.8
accB  = mean(yhatB == ytsB);

TP = sum((ytsB==1) & (yhatB==1));
TN = sum((ytsB==2) & (yhatB==2));
FP = sum((ytsB==2) & (yhatB==1));
FN = sum((ytsB==1) & (yhatB==2));
precB = TP / max(TP+FP,1);
recB  = TP / max(TP+FN,1);
f1B   = 2*precB*recB / max(precB+recB, eps);

fig = figure('Color','w'); hold on; grid on;
stem(ytsB,'filled','LineWidth',1.2); stem(yhatB,'r','filled','LineWidth',1.2);
xlabel('Тестовые образцы'); ylabel('Класс (1/2)');
legend('Истина','Предсказано','Location','best');
title(sprintf('Компетенции: точность = %.0f%%',100*accB));
saveas(fig, fullfile(outDir,'COMP_test_accuracy.png')); close(fig);

% Просмотр МФ и Rule Viewer
inNamesB = {'Рук-ль','Подчин.','Коллеги','Самооц.'};
fig = plotRuleMFs(centB, sigB, inNamesB);
saveas(fig, fullfile(outDir,'COMP_rule_mfs.png')); close(fig);

x_sampleB = XtsB(1,:);
fig = ruleViewerAnalog(x_sampleB, centB, sigB, thetaB, inNamesB, 'Класс (регр.)');
saveas(fig, fullfile(outDir,'COMP_rule_viewer_point.png')); close(fig);

% Поверхность по (Руководитель, Самооценка)
fixValsB = mean(XtrB,1);
fig = plotSurface2D(centB, sigB, thetaB, 1,4, fixValsB, inNamesB, 'Класс (регр.)');
saveas(fig, fullfile(outDir,'COMP_surface_R_A.png')); close(fig);

% ЛОГ по Компетенциям
logw(fid, '--- [COMP] Метрики теста ---');
logw(fid, sprintf('Accuracy   = %.2f%%', 100*accB));
logw(fid, sprintf('Precision1 = %.4f', precB));
logw(fid, sprintf('Recall1    = %.4f', recB));
logw(fid, sprintf('F1-Score1  = %.4f', f1B));
logw(fid, sprintf('Confusion [TP TN; FP FN] = [%d %d; %d %d]', TP,TN,FP,FN));
logw(fid, sprintf('\n[COMP] Центры правил:'));
printMatrix(fid, centB);
logw(fid, sprintf('\n[COMP] Сигмы МФ:'));
printMatrix(fid, sigB);
logw(fid, sprintf('\n[COMP] База правил (линейные следствия):'));
ruleStrB = getRuleBaseAsText(thetaB, numel(inNamesB), inNamesB, 'Класс(регр.)');
logw(fid, ruleStrB);

% CSV
writematrix([ytsB(:), yregB(:), yhatB(:)], fullfile(outDir,'COMP_test_truth_reg_pred.csv'));
writematrix([trainMSEB(:), checkMSEB(:)], fullfile(outDir,'COMP_learning_curves.csv'));
writematrix([TP TN; FP FN],                fullfile(outDir,'COMP_confusion_2x2.csv'));

%% ====================== Сохранение снепшота .MAT =======================
save(fullfile(outDir,'PZ5_workspace.mat'), ...
     'NEP','Xn','yn','trainIdx','testIdx','XtrA','ytrA','XtsA','ytsA', ...
     'centA','sigA','thetaA','trainMSEA','checkMSEA','yhat_tsA','MAE_A','RMSE_A','R2_A', ...
     'XC','YC','XtrB','ytrB','XtsB','ytsB','centB','sigB','thetaB', ...
     'trainMSEB','checkMSEB','yregB','yhatB','accB','TP','TN','FP','FN','precB','recB','f1B');

logw(fid, ['Все результаты сохранены в папке: ', outDir]);
fclose(fid);
diary off;

disp('ГОТОВО. Проверьте папку output_PZ5 (PNG/CSV/TXT/MAT).');

%% ======================== ЛОКАЛЬНЫЕ ФУНКЦИИ ============================

function banner(txt)
% Красивый разделитель в лог/командное окно (без rep!)
    line = repmat('-',1,70);
    fprintf('\n%s\n%s\n%s\n\n', line, txt, line);
end

function logw(fid, txt)
% Пишем строку и в командное окно, и в файл-лог
    if isstring(txt), txt = char(txt); end
    fprintf('%s\n', txt);
    if fid>0, fprintf(fid, '%s\n', txt); end
end

function [C, assign] = simpleKMeansPP_noToolbox(X, K, maxIter)
% k-means++ и Ллойд, без pdist2/randsample.
    [N,~] = size(X);
    C = zeros(K,size(X,2));
    % первый центр — случайная точка
    C(1,:) = X(randi(N),:);
    % инициализация остальных по D^2
    D2 = sum((X - C(1,:)).^2, 2);
    for k = 2:K
        s = sum(D2); if s<=eps, C(k,:) = X(randi(N),:); continue; end
        u = rand * s;
        idx = find(cumsum(D2) >= u, 1);
        if isempty(idx), idx = randi(N); end
        C(k,:) = X(idx,:);
        D2 = min(D2, sum((X - C(k,:)).^2,2));
    end
    % итерации Ллойда
    assign = zeros(N,1);
    for it = 1:maxIter
        D = zeros(N,K);
        for k = 1:K, diff = X - C(k,:); D(:,k) = sum(diff.^2,2); end
        [~, assign_new] = min(D, [], 2);
        if all(assign_new == assign), break; end
        assign = assign_new;
        for k = 1:K
            idx = (assign == k);
            if any(idx), C(k,:) = mean(X(idx,:),1);
            else,        C(k,:) = X(randi(N),:);
            end
        end
    end
end

function C = uniqueizeCenters(C, X)
% Если центры совпали — слегка «раздвинем» их джиттером.
    [K,d] = size(C);
    for k = 1:K
        for t = k+1:K
            if all(abs(C(k,:)-C(t,:))<1e-9)
                C(t,:) = C(t,:) + 0.05*(max(X)-min(X)).*(rand(1,d)-0.5);
            end
        end
    end
end

function S = initSigmas(X, C, roi)
% Ширины гауссиан по осям из диапазона данных и ROI (0..1).
    [K,~] = size(C);
    range = max(X) - min(X) + 1e-9;
    base  = roi * range;
    S = repmat(base, K, 1);
end

function [wbar, w] = firingStrengths(X, C, S, eps_denom)
% Гауссовы МФ; произведение по входам -> w; нормировка -> wbar.
    [N,~] = size(X); K = size(C,1);
    w = zeros(N,K);
    for k = 1:K
        z = (X - C(k,:)) ./ (S(k,:) + 1e-12);
        mu = exp(-0.5 * (z.^2));
        w(:,k) = prod(mu, 2);
    end
    sumw = sum(w,2) + eps_denom;
    wbar = w ./ sumw;
end

function theta = solveConsequentsRidge(wbar, X, y, lambda)
% Ридж-МНК для следствий Sugeno-1: theta = (A'A + λI)\(A'y)
% A = [wbar_k .* X, wbar_k] по всем правилам k.
    [N,d] = size(X);
    K = size(wbar,2);
    A = zeros(N, K*(d+1));
    for k = 1:K
        cols = (k-1)*(d+1) + (1:(d+1));
        A(:, cols) = [wbar(:,k).*X, wbar(:,k)];
    end
    I = eye(size(A,2));
    theta = (A.'*A + lambda*I) \ (A.'*y);
end

function yhat = anfisPredict(wbar, X, theta)
% Вычисление прогноза из параметров следствий.
    [N,d] = size(X); K = size(wbar,2);
    yhat = zeros(N,1);
    for k = 1:K
        cols = (k-1)*(d+1) + (1:(d+1));
        akbk = theta(cols);
        ak   = akbk(1:d);
        bk   = akbk(end);
        yhat = yhat + wbar(:,k) .* (X*ak + bk);
    end
end

function [Cnew, Snew] = updatePremiseFCM_soft(X, w_raw, C, S, squashFactor, roi, eps_denom, mFuzzy)
% FCM-like апдейт с «размягчением» членств (mFuzzy>1) и ограничением сигм.
    [K,d] = size(C);
    Cnew = zeros(K,d); Snew = zeros(K,d);

    sumw = sum(w_raw,2) + eps_denom;
    U = (w_raw ./ sumw) .^ mFuzzy;    % N×K
    denom = sum(U,1) + eps;

    for k = 1:K
        uk = U(:,k); W = denom(k);
        Cnew(k,:) = (uk.' * X) / W;                      % центр
        varw = ((X - Cnew(k,:)).^2)' * uk / W;           % дисперсия
        Snew(k,:) = sqrt(varw.' + 1e-9) * squashFactor;  % ширины
    end

    range = max(X) - min(X) + 1e-9;
    Smin = 0.10 * roi * range;   % минимум ширины
    Smax = 3.00 * roi * range;   % максимум ширины
    Snew = max(Snew, repmat(Smin, K, 1));
    Snew = min(Snew, repmat(Smax, K, 1));
end

function fig = plotRuleMFs(C, S, inNames)
% График гауссовых МФ по входам.
    [K,d] = size(C);
    fig = figure('Color','w','Position',[100 100 1000 260*d]);
    for j = 1:d
        subplot(d,1,j); hold on; grid on;
        xmin = min(C(:,j) - 3*S(:,j)); xmax = max(C(:,j) + 3*S(:,j));
        xs = linspace(xmin, xmax, 400);
        for k = 1:K
            mu = exp(-0.5 * ((xs - C(k,j)) ./ (S(k,j)+1e-12)).^2);
            plot(xs, mu, 'LineWidth', 1.5);
        end
        title(sprintf('МФ для входа %s', inNames{j}));
        xlabel(inNames{j}); ylabel('\mu'); ylim([0 1.05]);
    end
end

function fig = ruleViewerAnalog(x, C, S, theta, inNames, outName)
% Rule Viewer-аналог: w̄_k, f_k(x), w̄_k f_k.
    d = numel(inNames); K = size(C,1);
    w = zeros(1,K);
    for k = 1:K
        z = (x - C(k,:)) ./ (S(k,:) + 1e-12);
        mu = exp(-0.5 * (z.^2));
        w(k) = prod(mu);
    end
    wbar = w / (sum(w) + 1e-12);
    fk = zeros(1,K); y = 0;
    for k = 1:K
        cols = (k-1)*(d+1) + (1:(d+1));
        akbk = theta(cols); ak = akbk(1:d); bk = akbk(end);
        fk(k) = sum(x.*ak(:)') + bk;
        y = y + wbar(k)*fk(k);
    end
    fig = figure('Color','w','Position',[100 100 1100 380]);
    subplot(1,3,1); bar(wbar); ylim([0 1.05]); grid on;
    title('Нормированные firing strengths'); xlabel('Правило'); ylabel('w̄_k');
    subplot(1,3,2); bar(fk); grid on;
    title('Выходы правил f_k(x)'); xlabel('Правило'); ylabel('f_k');
    subplot(1,3,3); bar(wbar.*fk); grid on;
    title(sprintf('Вклад правил в %s (итог y=%.3f)', outName, y));
    xlabel('Правило'); ylabel('w̄_k * f_k'); sgtitle('Rule Viewer (аналог)');
end

function fig = plotSurface2D(C, S, theta, i1, i2, fixVals, inNames, outName)
% 3D-поверхность по двум входам (i1,i2); остальные фиксированы.
    d = size(C,2); K = size(C,1);
    x1 = linspace(min(C(:,i1)-2*S(:,i1)), max(C(:,i1)+2*S(:,i1)), 40);
    x2 = linspace(min(C(:,i2)-2*S(:,i2)), max(C(:,i2)+2*S(:,i2)), 40);
    [Xg,Yg] = meshgrid(x1,x2);
    Z = zeros(size(Xg));
    for t = 1:numel(Xg)
        x = fixVals;
        x(i1) = Xg(t); x(i2) = Yg(t);
        w = zeros(1,K);
        for k = 1:K
            z = (x - C(k,:)) ./ (S(k,:) + 1e-12);
            mu = exp(-0.5 * (z.^2)); w(k) = prod(mu);
        end
        wbar = w / (sum(w) + 1e-12);
        y = 0;
        for k = 1:K
            cols = (k-1)*(d+1) + (1:(d+1));
            akbk = theta(cols); ak = akbk(1:d); bk = akbk(end);
            y = y + wbar(k) * (sum(x.*ak(:)') + bk);
        end
        Z(t) = y;
    end
    fig = figure('Color','w'); surf(Xg,Yg,Z, 'EdgeColor','none'); grid on;
    xlabel(inNames{i1}); ylabel(inNames{i2}); zlabel(outName);
    title(sprintf('Поверхность %s по (%s,%s)', outName, inNames{i1}, inNames{i2}));
end

function printMatrix(fid, M)
% Красиво печатаем матрицу и в лог, и в окно.
    [r,c] = size(M);
    for i = 1:r
        line = '  ';
        for j = 1:c
            line = [line, sprintf('%10.6f', M(i,j))]; %#ok<AGROW>
        end
        fprintf('%s\n', line);
        if fid>0, fprintf(fid,'%s\n', line); end
    end
end

function ruleTxt = getRuleBaseAsText(theta, d, inNames, outName)
% Возвращает текст базы правил Sugeno-1: y = a1*x1 + ... + ad*xd + b
    K = numel(theta)/(d+1);
    lines = cell(K,1);
    for k = 1:K
        cols = (k-1)*(d+1) + (1:(d+1));
        akbk = theta(cols); ak = akbk(1:d); bk = akbk(end);
        parts = cell(1,d);
        for j = 1:d
            parts{j} = sprintf('a%d*%s', j, inNames{j});
        end
        left = strjoin(parts,' + ');
        lines{k} = sprintf('Правило %2d: %s = %s + b;   a=[%s], b=%.3f', ...
                           k, outName, left, sprintf('%.3f ', ak), bk);
    end
    ruleTxt = strjoin(lines, sprintf('\n'));
end