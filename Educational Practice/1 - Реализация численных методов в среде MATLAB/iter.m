function [x] = iter(A,B,a,b,c,d,e)
x0 = (A+B)/2;
C = 1/(11);
x = x0-C*(a*x0^3+b*x0^2+c*x0-d);
while abs(x-x0) >= e%если текущие минус предыдущее больше чем погрешность, то...
    x0 = x;%предыдущему присваивается текущее
    x = x0-C*(a*x0^3+b*x0^2+c*x0-d);%расчет нового текущего значения
end

read_num.m:
function [out] = read_num(text)
out = input (text,'s');
while( isnan(str2double(out)))
disp ('Вы ввели не число');
out = input('Введите число:','s');
end
   out = str2double(out);
end
