# Entrega 3

```
; Inicializa o endereço de início do programa
Org 0000h

; Configurações iniciais dos portos de saída
Select:		
SETB P0.7   ; Ativa o bit 7 do porto 0, geralmente para ativar um decoder
SETB P3.3   ; Configura o bit 3 do porto 3 para alto (1), selecionando A0=1
SETB P3.4   ; Configura o bit 4 do porto 3 para alto (1), selecionando A1=1
            ; A0=A1=1 seleciona o display 3 (o mais à esquerda)

; Inicialização de variáveis
Init:
MOV R3, #00Ah 	; Carrega o contador com 10

; Definição do ponto de início principal do programa
Main:
MOV DPTR, #display ; Aponta o DPTR para o início da tabela 'display'

; Loop principal para atualização do display
Contagem:
CLR A              ; Limpa o acumulador
MOVC A, @A+DPTR    ; Move para o acumulador o conteúdo apontado por DPTR
MOV P1, A          ; Envia o valor do acumulador para o porto 1 (display)
ACALL Delay        ; Chama a sub-rotina de delay para temporização
INC DPTR           ; Incrementa o DPTR para apontar para o próximo elemento da tabela
DJNZ R3, Contagem  ; Decrementa R3 e se não for zero, repete o loop
SJMP Init          ; Após completar a contagem, salta para 'Init' e reinicia o processo

; Sub-rotina para criar um atraso
Delay: 		
MOV	R1, #100       ; Inicializa R1 com 100 para o primeiro contador de delay

; Loop de delay externo
Loop:
MOV R0, #250      ; Inicializa R0 com 250 para o contador interno de delay
DJNZ R0, $        ; Decrementa R0 e se não for zero, continua no mesmo lugar
DJNZ R1, Loop     ; Decrementa R1 e se não for zero, repete o loop externo

RET               ; Retorna da sub-rotina Delay

; Definição de um novo bloco de memória para dados
Org 0200h

; Tabela de dados para display de 7 segmentos
display:
DB 0C0h, 0F9h, 0A4h, 0B0h, 99h, 92h, 82h, 0F8h, 80h, 90h ; Valores hexadecimais para os dígitos de 0 a 9

; Final do programa
End

```
Comentário dos código: 

![Esquemático](/Entrega%203/img/Esquemático.png)

1. **Org 0000h**: Define o endereço inicial do programa na memória, que é 0000h.

2. **SETB P0.7**: Configura o bit 7 do porta 0 para 1. Isso foi usado para ativar um decoder ou algum outro dispositivo externo.

3. **SETB P3.3 e SETB P3.4**: Configuram os bits 3 e 4 do porta 3 para 1. Estes bits foram usadas para selecionar entradas de um multiplexador ou decodificador. No comentário, indica que A0 e A1 iguais a 1 selecionam o display 3.

4. **Init: MOV R3,#00Ah**: Inicia uma label chamada "Init" e move o valor 10 (hexadecimal 0A) para o registrador R3, que será usado como contador no loop de contagem.

5. **Main: MOV DPTR,#display**: Inicia uma label chamada "Main" e move o endereço da tabela "display" para o DPTR (Data Pointer), que é usado para acessar dados na memória externa.

6. **Contagem: CLR A**: Inicia a label "Contagem", limpa o acumulador A para garantir que está zerado antes de começar a operação.

7. **MOVC A,@A+DPTR**: Move para o acumulador A o conteúdo da memória apontada por DPTR + o valor de A. Como A foi zerado, pega o primeiro valor da tabela "display".

8. **MOV P1,A**: Move o valor do acumulador A para o porto 1, para enviar este valor a um display ou outra interface.

9. **ACALL Delay**: Chama uma sub-rotina chamada "Delay" para criar um atraso, geralmente usado para controlar a velocidade de atualização do display.

10. **INC DPTR**: Incrementa o DPTR para apontar para o próximo elemento na tabela "display".

11. **DJNZ R3,Contagem**: Decrementa R3 e se R3 não for zero, salta para a label "Contagem". Isso cria um loop que repete a exibição dos valores da tabela "display".

12. **SJMP Init**: Um salto incondicional para "Init", o que reinicia o processo.

13. **Delay: MOV R1, #100**: Inicia a sub-rotina "Delay" e configura o registrador R1 com o valor 100.

14. **Loop: MOV R0, #250**: Inicia um loop dentro de "Delay", colocando 250 em R0.

15. **DJNZ R0, $**: Decrementa R0 e salta para o próprio comando se R0 não é zero, criando um loop interno.

16. **DJNZ R1, Loop**: Decrementa R1 e retorna ao início de "Loop" se R1 não é zero, criando um loop externo.

17. **RET**: Retorna da sub-rotina "Delay".

18. **Org 0200h**: Define um novo endereço base para os dados subsequentes.

19. **display: DB 0C0h, 0F9h, 0A4h, 0B0h, 99h, 92h, 82h, 0F8h, 80h, 90h**: Define uma tabela chamada "display" com valores hexadecimais, para representar os padrões de segmentos para um display de 7 segmentos.

20. **End**: Indica o fim do programa.

