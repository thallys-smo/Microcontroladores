## Entrega 1 e 2

## Entrega 1: Questões

Questão 1: Apresentar a definição formal de um sistema embarcado, indicando a referência primária do IEEE (Institute of Electrical and Electronics Engineers) que subsidie esta definição. Em seguida fazer uma
explanação breve e objetiva sobre as principais características, funcionalidades e o que difere um sistema embarcado de um computador de propósito geral.

> Resposta: 

Questão 2: De acordo com os Relatórios de Pesquisa sobre o Mercado de Sistemas Embarcados acima referidos (listar os itens abaixo com base nos 2 relatórios disponibilizados):

- I: Das ferramentas para sistemas embarcados – quais as principais áreas de aplicação dos projetos no mercado brasileiro e o cenário internacional?

> Resposta:

- II: Quais as principais ferramentas de comunicação sem fio que estão sendo usadas no Brasil e no mundo?

> Resposta:

- III: Quais os principais kits/plataformas de prototipagem usados?

> Resposta:

- IV: Dos softwares para sistemas embarcados - qual a principal ferramenta de codificação, principal sistema de controle de versão, e principal linguagem de programação?

> Resposta:

- V: Dos microprocessadores/microcontroladores – quais os fabricantes/modelos mais citados na pesquisa?

> Resposta:

Questão 3: Recorra ao exemplo do microcontrolador aplicado ao controle de um elevador que foi apresentado em aula, disponível nas transparências do Cap. 2. Quais as vantagens de se utilizar um microcontrolador para aquele tipo de aplicação e qual deve ser o “perfil” de um microcontrolador ideal para aquela aplicação do elevador em termos de capacidade da CPU (baixa, média ou alta), quantidade de bits no barramento, e precisão no tratamento das informações (operação somente com inteiros ou ponto flutuante?)

> Resposta:

Questão 4: Quanto às portas paralelas de um microcontrolador:

() São somente de entrada. <br/> 
( ) São somente de saída.  <br/> 
( ) Cada palavra (A, B, C, P1, P2, P3…) pode ser configurada como entrada ou saída. <br/> 
( ) Cada bit pode ser configurado como entrada ou saída. <br/> 
( ) Cada palavra (A, B, C... P1, P2, P3…) pode ser configurada como entrada, saída ou bidirecional. <br/> 
( ) Cada bit pode ser configurado como entrada, saída ou bidirecional. <br/> 

Questão 5: Assinale V para verdadeiro e F para falso nas afirmações abaixo.

( ) No modelo de Von Neumann, o microprocessador segue as instruções armazenadas na
memória ROM (programas), lê as entradas e envia comandos sobre os canais de saída,
alterando as informações contidas na memória RAM. <br/> 
( ) Os registradores Special Function Registers localizam-se sempre internos à CPU. <br/> 
( ) O ciclo de máquina é composto pelo ciclo de busca mais o ciclo de execução, cada qual
demorando um pulso de clock. <br/> 
( ) A instrução “CLR A” não possui operando e gasta apenas 1 ciclo de máquina. <br/> 
( ) A arquitetura Von Neumann é considerada uma arquitetura mais simples do que a arquitetura
Harvard porque utiliza o mesmo barramento para o tráfego de dados e de instruções. <br/> 
( ) A técnica de pipeline é impossível de ser utilizada em computadores de arquitetura Von
Neumann. <br/> 

Questão 6: Indique quais afirmativas se aplicam a uma instrução CISC e quais a uma instrução RISC.

➔ Os programas são mais complexos <br/> 
➔ A maioria das instruções tem a mesma duração. <br/> 
➔ Mais instruções disponíveis. <br/> 
➔ Programas menores. <br/> 
➔ Utiliza menos espaço na memória de programa. <br/> 
➔ Processamento de cada instrução é mais lento. <br/> 
➔ Microcontroladores PIC, AVR, ARM. <br/> 
➔ Tempo de execução das instruções depende da frequência do clock. <br/> 

Questão 7: Abaixo é apresentado o diagrama de um microcontrolador. Qual a arquitetura utilizada e como
chegamos a essa conclusão? Quantas portas I/O bidirecional e quantas linhas (bits/pinos) são
endereçados de forma individual neste microcontrolador, com base no diagrama abaixo?

Imagem: questao_7

> Resposta: 

Questão 8: No simulador EdSim51, digite e execute (clicando em “Assm”) as instruções abaixo.

```
MOV R0, #22h
MOV 00h, #22h
```

Qual a diferença entre as duas instruções acima? Tente refletir porque possuem ciclos de
máquina diferentes se a operação é realizada na mesma posição de memória RAM (00h ou
R0 usa o mesmo espaço).

> Resposta:

```
MOV A, #22h
MOV ACC, #22h
```

Qual a diferença entre as duas instruções acima? Tente refletir sobre a diferença de usar A ou
ACC e sobre porque possuem ciclos de máquina diferentes se a operação realizada é a
mesma.

> Resposta:

Questão 9: A Figura abaixo mostra um microcontrolador genérico de 8 bits com 4 registradores internos à
CPU, os quais são: Instruction Register (IR), Program Counter (PC), Accumulator (ACC) e
Data Pointer (DPTR). Baseado na Figura abaixo, responda às questões com verdadeiro (V) ou
Falso (F). 

Imagem: questao_9

( ) Trata-se de um microcontrolador de arquitetura Harvard. <br/> 
( ) A memória EEPROM é de 4Kbytes e armazena as instruções que comandam o
microcontrolador. <br/> 
( ) A memória SRAM é de 512 bytes e armazena dados voláteis. <br/> 
( ) O registrador IR tem a função de armazenar a instrução lida da memória SRAM. <br/> 
( ) Para esse microcontrolador, o registrador IR deve ser de 8 bits. <br/> 
( ) O registrador PC armazena o endereço da instrução lida da memória EEPROM. <br/> 
( ) Para esse microcontrolador, o registrador PC deve ser de 10 bits. <br/> 
( ) Para esse microcontrolador, o registrador ACC deve ser de 8 bits. <br/> 
( ) O registrador DPTR é um ponteiro que aponta para a última instrução lida da memória. <br/> 
( ) Para esse microcontrolador, o registrador DPTR deve ser de 10 bits. <br/> 

Questão 10: Responder com Verdadeiro (V) ou Falso (F) às seguintes afirmações.

( ) A pilha é uma memória RAM sequencial do tipo FIFO. <br/> 
( ) A pilha geralmente é utilizada para armazenar endereço de retorno de subrotinas e também
de interrupções. <br/> 
( ) O ponteiro de pilha (Stack Pointer) é um registrador que aponta para um endereço da
memória ROM, que é o endereço de retorno do programa após o atendimento a uma interrupção
ou sub-rotina. <br/> 
( ) As instruções PUSH e POP são exclusivas para operações com pilha. <br/> 
( ) A instrução CALL <endereço> deve ser usada para indicar qual endereço o programa deve
desviar no caso de um atendimento à interrupção ou chamada de sub-rotina. <br/> 
( ) A instrução RET, colocada no final de uma sub-rotina, faz com que o último endereço
armazenado na pilha seja carregado no registrador PC (program counter). <br/> 
( ) A área da RAM interna dedicada à pilha é determinada pelo ponteiro SP, um dos SFRs, que
possui tamanho 8 bits, mesmo tamanho do barramento de endereço da CPU. <br/> 
( ) Geralmente são baseadas em flip-flops tipo D. <br/> 

Questão 11: Refletir se existe diferença entre o endereço armazenado em um espaço de pilha e o endereço
armazenado no Stack Pointer (SP)?

> Resposta: 

Questão 12: Colocou-se 3 LEDs nos endereços P1.0, P1.1 e P1.2 no microcontrolador e 3 chaves nos
endereços P2.0, P2.1 e P2.2. Considerando que os LEDs acendem quando é colocado nível
baixo na saída e as chaves, quando pressionadas, colocam nível baixo na porta, explique o
funcionamento do programa abaixo quando cada uma destas 3 chaves são pressionadas.

```
ORG 0000H
Leitura:
    JNB P2.0, PX
    JNB P2.1, PY
    JNB P2.2, PZ
    LCALL Leitura

PX:
    MOV P1, #0
    RET
PY:
    MOV P1, #00000101b
    RET
PZ:
    MOV A, P1
    CPL A
    MOV P1, A
    RET
FIM:
    SJMP FIM
```

## Entrega 2: 

Atividade prática de uso de set de instruções e manipulação de dados em registradores e endereços de memória em microcontroladores

- Apresentar diretamente no documento (mesmo documento da Entrega 1) as linhas de código (programa devidamente comentado e, quando for caso, as respostas às perguntas específicas ao final do programa).
- As respostas devem seguir a ordem do roteiro. Por exemplo:

1 - Manipulação de dados em registradores e endereços de memória por meio de instruções de transferência de dados:

```
codigo comentado ...
```

2 - Manipulação de dados em registradores e endereços de memória por meio de instruções Aritméticas:

```
codigo comentado ...
```

