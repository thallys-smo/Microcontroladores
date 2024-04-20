Org 0000h	; Inicializa o endereço de início do programa

Select:		; Configurações iniciais dos portos de saída
SETB P0.7   ; Ativa o bit 7 do porta 0 para ativar o decoder
SETB P3.3   ; Configura o bit 3 da porta 3 para alto (1), selecionando A0=1
SETB P3.4   ; Configura o bit 4 da porta 3 para alto (1), selecionando A1=1
            ; A0=A1=1 seleciona o display 3 (o mais à esquerda)

Init:	; Inicialização de variáveis
MOV R3, #00Ah 	; Carrega o contador para 10 repetições

Main:	; Definição do ponto de início principal do programa
MOV DPTR, #display      ; Aponta o DPTR para o início da tabela 'display'

Contagem:	; Loop principal para atualização do display
CLR A              ; Limpa o acumulador
MOVC A, @A+DPTR    ; Move para o acumulador o conteúdo apontado pelo endereço A+DPTR
MOV P1, A          ; Envia o valor do acumulador para a porta 1 (display)
ACALL Delay        ; Chama a sub-rotina de delay para temporização
INC DPTR           ; Incrementa o DPTR para apontar para o próximo elemento da tabela
DJNZ R3, Contagem  ; Decrementa R3 e se não for zero, repete o loop
SJMP Init          ; Após completar a contagem, salta para 'Init' e reinicia o processo

Delay: 		; Sub-rotina para criar um atraso	
MOV R1, #100       ; Inicializa R1 com 100 para o primeiro contador de delay

Loop:	; Loop de delay externo
MOV R0, #250      ; Inicializa R0 com 250 para o contador interno de delay
DJNZ R0, $        ; Decrementa R0 e se não for zero, continua no mesmo lugar
DJNZ R1, Loop     ; Decrementa R1 e se não for zero, repete o loop externo

RET	; Retorna da sub-rotina Delay


Org 0200h         ; Definição de um novo bloco de memória para dados

display:	  ; Tabela de dados das combinações de cada dígito para o display de 7 segmentos
DB 0C0h, 0F9h, 0A4h, 0B0h, 99h, 92h, 82h, 0F8h, 80h, 90h ; Valores hexadecimais para os dígitos de 0 a 9        

End             ; Final do programa
