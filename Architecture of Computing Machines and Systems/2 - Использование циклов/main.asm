
	.global _c_int00 ;точка входа
_c_int00:
 .data
array1: .byte 1,2,3,4, 5
size .set 5 ;РАЗМЕР

 .text
 MVK .S1 array1, A10 ;АДРЕСА ЭЛЕМЕНТОВ
 MVK .S2 array1, B10

 MVK .S2 size,B4
 SUB .L2 B4, 2, B4 ;ЧИСЛО ПОВТОРЕНИЙ

 MVK .S2 2, B11 ;A11=0 B11=2 НАЧАЛЬНЫЕ ИНДЕКСЫ

 SHL .S1 B4,31,A2     ;ПРОВЕРКА ЧЁТНОСТИ ЧИСЛА ЭЛЕМЕНТОВ
 [A2]LDB  .D1 *A10, A5            ;ЕСЛИ НЕЧЁТНО
 [A2]LDB  .D2 *B10[1],  ]  B5
 NOP 4
 [A2]MV .L2X A5, B6
 [A2]MV .L1X B5, A6
 [A2]STB .D1  A6,  *A10
 [A2]STB .D2  B6, *B10[1]

LOOP: ;DO

 LDB  .D1 *A10[A11], A5   ;ЗАГРУЗКА ЭЛЕМЕНТОВ
 LDB  .D2 *B10[B11], B5
 NOP 4

 MV .L2X A5, B6            ;ОБМЕН МЕСТАМИ
 MV .L1X B5, A6
 STB .D1  A6,  *A10[A11]   ;ЗАГРУЗКА В ПАМЯТЬ
 STB .D2  B6, *B10[B11]

 ADD .L1  A11,1,A11      ;УВЕЛИЧЕНИЕ ИНДЕКСЫ
 ADD .L2  B11,1,B11

 CMPEQ .L2 B11,size, B2  ;ЕСЛИ ИНДЕКС БОЛЬШЕ SIZE ТО ОБНУЛЯЕМ
 [B2] MVK .S2 0, B11

 CMPEQ .L1 A11,B4, A0    ;ПРОВЕРКА ОКОНЧАНИЯ ЦИКЛА
 [!A0] B .S2 LOOP
 NOP 5
