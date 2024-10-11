function x = check_number(fBody)
while 1
        buffer = input(fBody, 's');%проверка на строку
        x = str2double(buffer); 
        if isnan(x)
            disp(' ')
            disp('Ошибка!!!')
            disp('Введенное данное содержит символы или пробел!')
            disp('Повторите ввод')
        elseif length(strfind(buffer, ','))>0 
            disp(' ')
            disp('Ошибка!!!')
            disp('Введенное данное содержит запятую!')
            disp('Для разделения целой и дробной части числа используйте точку и повторите ввод!')
        elseif abs(x) > abs(10)
            disp(' ') 
            disp('Ошибка!!!') 
            disp('Число по модулю больше 10')    
            disp('Повторите ввод')
            disp(' ')  
        else
            break
        end
end
end 
