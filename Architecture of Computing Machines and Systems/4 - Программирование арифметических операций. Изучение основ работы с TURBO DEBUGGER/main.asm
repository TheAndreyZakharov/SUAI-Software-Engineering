Data SEGMENT 				;открыть сегмент данных
	A DB 5Ah			;инициализировать переменные
	B DB 55h
	C DB 11h
	D DB 8
	X DW ?
Data ENDS				;закрыть сегмент данных
Ourstack SEGMENT Stack			;открыть сегмент стека
	DB 100h DUP (?)			;отвести под стек 256 байт
Ourstack ENDS				;закрыть сегмент стека

ASSUME CS:Code, DS:Data, SS:Ourstack	;назначить сегментные регистры

Code SEGMENT				;открыть сегмент кодов
Start: mov AX, Data			;инициализировать 
	mov DS, AX			;сегментный регистр DS
	xor AX, AX			;очистить регистр
	mov AL, A			;поместить A в регистр AL
	xor CX, CX
	mov CL, 3			;поместить 3 в CL
	mul CL				;умножить AL на 3
	add AL, 48			;прибавить к результату 48
	xor DX, DX			
	mov DX, AX			;пометить (48+A*3) в DX
	xor AX, AX
	xor BX, BX
	mov AL, B			;поместить B в AL
	div C				;разделить B на C
	mul D				;умножить B/C на D
	sub DX, AX			;(48+A*3)-B/C*D
	mov AX,4C00h		;завершить программу
	int 21h				;с помощью DOS
Code ENDS				;закрыть сегмент кодов
END Start

