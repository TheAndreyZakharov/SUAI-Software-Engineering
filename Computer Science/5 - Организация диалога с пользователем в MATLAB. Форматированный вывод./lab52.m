function [xmax,xmin] = more_less
    while true
        xmax = check_number('\nВведите левую границу интервала:\nxmax='); 
        xmin = check_number('\nВведите правую границу интервала:\nxmin=');  
        if xmax<xmin
            disp(' ')
            disp('Ошибка!!!') 
            disp('xMax должен быть больше xMin')
            disp('повторите ввод')
            disp(' ')
        else
            break   
        end
 
    end
end
