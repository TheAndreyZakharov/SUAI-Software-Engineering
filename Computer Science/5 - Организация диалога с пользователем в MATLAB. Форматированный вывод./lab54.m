clear all
clc
 
func = input('Введите функцию: ', 's');
    
[xMin, xMax] = more_less();
 
x_v = xMin:0.1:xMax;
i = 0;
for x = x_v
    i = i + 1;
    y(i) = eval(func);
end
printTable(x_v, y)
plot(x_v, y)
xlabel('x')
ylabel('y')
legend(func)
