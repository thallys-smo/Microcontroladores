			Org 0000h
Select:		
SETB P0.7   ;ativar decoder
SETB P3.3   ;selecionar A0=1
SETB P3.4   ;selecionar A1=1
; A0=A1=1 seleciona o display 3 (o mais a esquerda)
				
Init:
MOV R3,#00Ah 	;contador

Main:
MOV DPTR,#display

Contagem:
CLR A
MOVC A,@A+DPTR
MOV P1,A
ACALL Delay
INC DPTR
DJNZ R3,Contagem
SJMP Init

Delay: 		
MOV	R1, #100

Loop:
MOV R0, #250
DJNZ R0, $
DJNZ R1, Loop

RET
			
Org 0200h

display:
DB 0C0h, 0F9h, 0A4h, 0B0h, 99h, 92h, 82h, 0F8h, 80h, 90h
	
End
