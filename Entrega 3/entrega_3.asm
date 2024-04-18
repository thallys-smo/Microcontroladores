			Org 0000h
Select:		
SETB P0.7   ;ativar decoder
SETB P3.3   ;selecionar A0=1
SETB P3.4   ;selecionar A1=1
; A0=A1=1 seleciona o display 3 (o mais a esquerda)
				
Init:
MOV R3,#00Ah	

Main:
MOV DPTR,#display

Back:
CLR A
MOVC A,@A+DPTR
MOV P1,A
ACALL Delay
INC DPTR
DJNZ R3,Back
SJMP Init

Delay: 		
MOV	R0, #05h  ; Outer loop

Again: 		
MOV	R1, #0BCh  ; inner loop

Here:  		
DJNZ R1, Here   ; jump if r1 not 0
DJNZ R0, Again  ; jump if r0 not 0
RET
			
Org 0200h

display:
DB 0C0h, 0F9h, 0A4h, 0B0h, 99h, 92h, 82h, 0F8h, 80h, 90h
	
End