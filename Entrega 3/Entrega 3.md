# Entrega 3

```
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
```

Comentário dos código: 

1. **Org 0000h**: Define o endereço inicial do programa na memória, que é 0000h.

2. **SETB P0.7**: Configura o bit 7 do porto 0 para 1. Isso pode ser usado para ativar um decoder ou algum outro dispositivo externo.

3. **SETB P3.3 e SETB P3.4**: Configuram os bits 3 e 4 do porto 3 para 1. Estes bits podem ser usados para selecionar entradas de um multiplexador ou decodificador. No comentário, indica que A0 e A1 iguais a 1 selecionam o display 3.

4. **Init: MOV R3,#00Ah**: Inicia uma label chamada "Init" e move o valor 10 (hexadecimal 0A) para o registrador R3, que será usado como contador no loop de contagem.

5. **Main: MOV DPTR,#display**: Inicia uma label chamada "Main" e move o endereço da tabela "display" para o DPTR (Data Pointer), que é usado para acessar dados na memória externa.

6. **Contagem: CLR A**: Inicia a label "Contagem", limpa o acumulador A para garantir que está zerado antes de começar a operação.

7. **MOVC A,@A+DPTR**: Move para o acumulador A o conteúdo da memória apontada por DPTR + o valor de A. Como A foi zerado, pega o primeiro valor da tabela "display".

8. **MOV P1,A**: Move o valor do acumulador A para o porto 1, provavelmente para enviar este valor a um display ou outra interface.

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

19. **display: DB 0C0h, 0F9h, 0A4h, 0B0h, 99h, 92h, 82h, 0F8h, 80h, 90h**: Define uma tabela chamada "display" com valores hexadecimais, possivelmente representando padrões de segmentos para um display de 7 segmentos.

20. **End**: Indica o fim do programa.

Este código parece ser um programa para microcontrolador que exibe uma sequência de números em um display de 7 segmentos, usando um loop e delays para controlar a exibição e a taxa de atualização.