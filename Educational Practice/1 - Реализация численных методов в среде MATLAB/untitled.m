clc; clear;
e = read_num("Введите погрешность(0.001): ");
disp("Введите коэффициенты a, b, c, d")
a = read_num("a(6): ");
b = read_num("b(1): ");
c = read_num("c(1): ");
d = read_num("d(1.8): ");
disp("Введите начало и конец отрезка")
A = read_num("Начало отрезка(0): ");
B = read_num("Конец отрезка(1): ");
x=iter(A,B,a,b,c,d,e);%высчитывание методом простых итераций
fprintf("Метод простых итераций: %f\n",(x))
fprintf("Встроенная функция Matlab: %f\n",(fzero(strcat(string(a),'*x.^3+',string(b),'*x^2+',string(c),'*x-',string(d)),A)))
