Сохранённая осциллограмма по варианту, расчёт амплитуды частоты


<img width="452" alt="image" src="https://github.com/user-attachments/assets/fdc208a1-9ce5-4345-a292-23782cbb0bb6">



1) Изучить состав отладочного комплекта Open32F3-D.
2) Создать проект на основе примера. Задать размеры стека и 'heap' 0x00000E00. Переменным: ‘a1, b1, c1, d1’ типа unsigned char; ‘a2, b2, c2, d2’ типа unsigned short; ‘a4, b4, c4, d4’ типа unsigned int; ‘a8, b8, c8, d8’ типа unsigned long long присвоить повторяющиеся значение E9, переменной 'name1' присвоить "Daniil" , переменной 'name2' "Mel'nikov", 'name3' "4133k".
3) Найти в файле карты компоновки (map-файле): затраты оперативной (RAM) и постоянной (ROM) памяти МК для вашего проекта; адрес расположения и размер стека; адрес расположения и размер таблицы векторов; адрес расположения и размер функции main ().
4) Проанализировать переменные 'a1÷d8, name1÷3' инструментами отладки ИСР Keil. Определить адреса переменных. По адресам определить расположение в памяти. Сохранить отпечаток всей области памяти этих переменных в файл logdat.txt.
5) Оформить отчёт.

