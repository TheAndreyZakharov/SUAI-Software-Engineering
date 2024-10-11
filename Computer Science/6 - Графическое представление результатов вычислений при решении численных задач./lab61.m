close all
clear all
clc
 
integ = @(func) strcat('for (x = xmin:step:x_)y(i) = y(i) + ', func, '; end');
 
func = input('Введите функцию: ', 's');
func = eval(['@(x)' func]);
 
[xmax, xmin] = more_less();
step = input_step(xmin, xmax);
x_v = xmin:step:xmax;
i = 0;
 
for i = 1:length(x_v)
    y(i) = func(x_v(i));
    z(i) = integral(func, xmin, x_v(i));
end
 
 
% вывод таблицы
printTable(x_v, y, z)
 
% вывод графиков
create_chart(x_v, y, xmin, xmax, z)
