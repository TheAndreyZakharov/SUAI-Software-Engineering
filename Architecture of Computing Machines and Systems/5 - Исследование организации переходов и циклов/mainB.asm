.MODEL SMALL
.STACK 256
.DATA
MYTEXT DB 'abcdefghijklmnopqrstuvwxyz*,./*; ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890', 13, 10, '$'	;объявляем текстовую переменную
length = ($ - MYTEXT) - 3
.CODE

CHANGE PROC NEAR				;процедура находится в одном сегменте кода->near
NOP					;ожидание
	ADD AH,32			;сместить символ
MOV [BX],AH				;поместить полученное значение в исх.строку
RET					;возврат
CHANGE ENDP				;конец процедуры


Start:
	MOV AX,@DATA			;
	MOV DS,AX			;загрузить сегм.данных в DS
	XOR AX,AX			;очистить AX
	LEA DX,MYTEXT			;загрузить адрес MYTEXT в BX
	MOV AH,09h			;вывести переменную
	INT 21h
	MOV CX,length			;загрузить длину строки в CX

MT1: MOV AH,[BX]			;поместить в AH символ под номером BX
	CMP AH,41h			;сравнить тек.симв. и A-41h 
	JB MT2				;перейти к MT2, если тек.симв. <
	CMP AH,5Ah			;сравнить тек.симв. и Z-5Ah
	JA MT2				;перейти к MT3, если тек.симв. >
	CALL CHANGE			;вызвать DOWN


MT2: INC BX				;увеличить адрес

LOOP MT1
	LEA DX,MYTEXT			;повторить цикл, если (CX)!=0
	MOV AH,09h			;вывести переменную
	INT 21h				;MYTEXT на экран
	NOP				;холостая команда
	MOV AX,4C00h			;завершить
	INT 21h				;программу
END Start
