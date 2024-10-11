clc
clear all
f2 = @(x)((cos(3.*x.^2+2))./(8.^x+7.^-x)+exp(3.*x+2));
x = -3:0.001:0;
for i = 1:length(x)
    y1(i) = f1(x(i));
    y2(i) = f2(x(i));
end
plot(x,y1,x,y2) 
xlabel x
ylabel y
legend('f1(x) = функция',' f2(x) = (cos(3.*x.^2+2))./(8.^x+7.^-x)+exp(3.*x+2) ')
grid on
