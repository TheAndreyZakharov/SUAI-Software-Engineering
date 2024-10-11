function create_chart(x_v, y, xmin, xmax, z)
    
    % вывод 1 графика
    subplot(2,1,1)
    hold on
    
    n_app = length(y);
    y1 = interpft(y, n_app);
    dx = length(y) / n_app;
    x1 = 0:dx:length(y) - dx;
    x1 = x1 + xmin;
    %x = 0:length(x1) - 1;
    
    plot(x1, y1, '--g', 'LineWidth', 2);
    plot(x1, y1, '*r', 'LineWidth', 2);
    
    
    % отображение минимума и максимума в 1 графике
    xMaxFunc = xmin:xmax;
    plot(xMaxFunc, ones(1, length(xMaxFunc)) * max(y1), '--r', 'LineWidth', 1.5);
    plot(xMaxFunc, ones(1, length(xMaxFunc)) * min(y1), '--r', 'LineWidth', 1.5);
    
    xlim([xmin, xmax])
    grid on
    
    % вывод 2 графика
    subplot(2,1,2)
    hold on
 
    plot(x_v, z, '-c', 'LineWidth', 2);
    
    % вывод минимума и максимума во 2 графике
    xMaxFunc = xmin:xmax;
    plot(xMaxFunc, ones(1, length(xMaxFunc)) * max(z), '--r', 'LineWidth', 1.5);
    plot(xMaxFunc, ones(1, length(xMaxFunc)) * min(z), '--r', 'LineWidth', 1.5);
    
    xlim([xmin, xmax])
    grid on
    
end

