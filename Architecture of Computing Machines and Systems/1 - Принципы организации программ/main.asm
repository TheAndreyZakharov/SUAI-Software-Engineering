.global _c_int00
 .text
_c_int00:
 
MVK .S1 4,A0 ; variable A
MVK .S1 3,A1 ; variable B
MVK .S1 2,A2 ; variable C
 
MPY .M1 A2, A1, A1   ; A1 = C * B
NOP 2
 
ADD .L1 A0,A2,A2        ;  A2 = A + C
SUB .L1 A2,A1,A0.        ;  A0 = (A + C ) - (C * B)
