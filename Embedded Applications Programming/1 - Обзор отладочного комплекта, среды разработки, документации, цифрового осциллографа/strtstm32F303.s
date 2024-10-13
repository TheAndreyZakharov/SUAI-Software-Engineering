Stack_Size EQU 0x00000E00
		AREA STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem SPACE Stack_Size
__initial_sp
Heap_Size EQU 0x00000E00
		AREA HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem SPACE Heap_Size
__heap_limit
		PRESERVE8
		THUMB
		AREA RESET, DATA, READONLY
		EXPORT __Vectors
__Vectors DCD __initial_sp
		DCD Reset_Handler
__Vectors_End
__Vectors_Size EQU __Vectors_End - __Vectors
		AREA |.text|, CODE, READONLY
Reset_Handler PROC
		IMPORT main
		LDR R0, =main
		BX R0
		ENDP
		EXPORT __initial_sp
		EXPORT __heap_base
		EXPORT __heap_limit
	END
