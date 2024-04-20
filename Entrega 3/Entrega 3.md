# Entrega 3

![Esquemático](/Entrega%203/img/Esquemático.png)

A partir do código e da arquitetura disponível no EdSim51, pode-se entender o funcionamento do algoritmo a partir dos seguintes pontos:

1. Ativa-se o bit P0.7 para 1 para ativar o decoder que possibilita a escolha do display de 7 segmentos

2. Configuram-se os bits 3 e 4 do porta 3 para 1. Estes bits foram usadas para selecionar a saída do decodificador. No caso, A0 e A1 iguais a 1 selecionam o display 3 (o mais a esquerda da imagem).

4. É movido ao registrador R3 o valor decimal de 10, que será usado como contador no loop de contagem.

5. **Main: MOV DPTR,#display**: Inicia uma label chamada "Main" e move o endereço da tabela "display" (0200h) para o DPTR (Data Pointer).

6. Inicia a label "Contagem" e limpa o acumulador A para garantir que está zerado antes de começar a operação. Dentro dessa label, ocorre a contagem dos dígitos no display da seguinte forma:

    1. Limpa o valor do acumulador A e o substitui pelo conteúdo da memória apontada por DPTR + o valor de A. Na primeira iteração, o endereço movido para A vai ser o do primeiro valor da tabela display (dígito 0)
    3. Move-se o valor do acumulador A para porta 1, para configurar os segmentos do display na configuração do dígito atual
    4. É acionada a rotina de delay
    5. Incrementa o valor de DPTR para apontar para o próximo valor da tabela
    7. Decrementa R3 e, se não for 0, repete o looping da label "Contagem", substituindo o valor de A para endereçar o próximo valor da tabela 
    8. Após completar a contagem, salta para a label "Init" para repetir o processo

9. **Delay: MOV R1, #100**: Inicia a sub-rotina "Delay" e configura o registrador R1 com o valor 100.

14. **Loop: MOV R0, #250**: Inicia um loop dentro de "Delay", colocando 250 em R0.

15. **DJNZ R0, $**: Decrementa R0 e salta para o próprio comando se R0 não é zero, criando um loop interno.

16. **DJNZ R1, Loop**: Decrementa R1 e retorna ao início de "Loop" se R1 não é zero, criando um loop externo.

17. **RET**: Retorna da sub-rotina "Delay".

18. **Org 0200h**: Define um novo endereço base para os dados subsequentes.

19. **display: DB 0C0h, 0F9h, 0A4h, 0B0h, 99h, 92h, 82h, 0F8h, 80h, 90h**: Define uma tabela chamada "display" com valores hexadecimais, para representar os padrões de segmentos para um display de 7 segmentos.

20. **End**: Indica o fim do programa.

