function [out] = read_num(text)
out = input (text, 's');
    while( isnan(str2double(out)))
    disp ('Вы ввели не число, нужно ввести число');
    out = input('Введите число:','s');
    end
out = str2double(out);
end
