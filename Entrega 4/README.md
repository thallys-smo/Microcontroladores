# Entrega 4

## Projeto Cronometro

- Arquivos: [Projeto 2 - Cronômetro Digital](/Entrega%204/Projeto%202%20-%20Cronometro/) <br>

```c
// Variaveis globais

const unsigned short int displayValues[10] = { // o arranjo com todas as possiveis configuracoes do display
    0b11111100, // 0
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b10111110, // 6
    0b11100000, // 7
    0b11111110, // 8
    0b11110110, // 9
};
unsigned short int pressedButton = 0; // indica qual botao foi pressionado: 1 para RB0 e 2 para RB1
unsigned short int counterIndex = 0; // indice para contagem do display


// Definir funcoes auxiliares

void interruptHandler() iv 0x0008 ics ICS_AUTO { // checa interrupcao de alta prioridade acionada -> manipula intervalo de tempo de acordo com bot?o pressionado
    if(INTCON.INT0IF ==1) { // checa acionamento do botao RB0
      pressedButton = 1; // botao RB0 -> botao = 1
      INTCON.INT0IF = 0; // limpar valor do botao de interrupcao
    }

    if(INTCON3.INT1IF == 1) { // checa acionamento do bot?o RB1
        pressedButton = 2; // botao RB1 -> botao = 2
        INTCON3.INT1IF = 0; // limpar valor do botao de interrupcao
    }

    if(INTCON.TMR0IF == 1 && pressedButton != 0) { // checa interrupcao pelo Timer 0
        PORTD = displayValues[counterIndex]; // exibe o digito atual no display
        if(counterIndex<9) {
            counterIndex+=1; // enquanto nao estiver no final, incrementa 1 no contador
        }
        else {
            counterIndex=0; // quando chega no final, reinicia a contagem
        }

        T0CON.TMR0ON = 0; // desativa o timer

        if(pressedButton == 1) {
            T0CON = 0b00000100; // configura o intervalo de mudanca de numero para 1s
        }
        else if(pressedButton == 2) {
            T0CON = 0b00000010; // configura o intervalo de mudan?a de numero para 0.25s
        }

        TMR0L = 0xDC; // set do limite inferior do timer em hexadecimal

        TMR0H = 0x0B; // set do limite superior do timer em hexadecimal

        T0CON.TMR0ON = 1; // Liga o timer

        INTCON.TMR0IF = 0; // limpa a interrupcao do timer

    }
}

void configureTimer() { // configura o timer do microcontrolador
    T0CON = 0b00000110; // configura timer de 16 bits
    INTCON.TMR0IF = 0; // limpa interupcao do timer
    T0CON.TMR0ON = 1; // liga o timer
}

void configureGlobalInterruptions() { // Ativa interrupcoes globais
    INTCON.GIEH = 1; // Ativa interrupcoes de alta prioridade
    INTCON.GIEL = 1; // Ativa interrupcoes de baixa prioridade
    RCON.IPEN = 1; // Ativa o seletor de prioridades das interrupcoes
}

void configureTimer0() { // Configura o Timer 0
    INTCON.TMR0IF = 1; // Configura botao de interrupcao do timer
    INTCON2.TMR0IP = 1; // Muda prioridade de interrupcao do timer para alta
    INTCON.TMR0IE = 1; // Ativa a interrupcao do timer
}

void configureButtonInterruptions() { //  configura as interrupcoes dos botoes INT0 e INT1
    INTCON.INT0IF = 0; // Limpa flag de interrupcao do INT0
    INTCON.INT0IE = 1; // Ativa a flag de interrupcao do INT0

    INTCON.INT1IF = 0; // Limpa flag de interrupcao do INT1
    INTCON.INT1IP = 1; // Muda prioridade de interrupcao de INT1 para alta
    INTCON.INT1IE = 1; // Limpa flag de interrupcao do INT1

    INTCON2.INTEDG0 = 1; // Configura borda de ativa??o de interrupcao do INT0 como subida

    TRISB.RB0 = 1; // Configura pino RB0 com entrada da PORTB
    TRISB.RB1 = 1; // Configura pino RB1 como entrada da PORTB
}


// Codigo principal

void main() {
    #ifdef P18F45K22
      ANSELB = 0; // desativa entradas analogicas da PORTB
      ANSELD = 0; // desativa entradas analogicas da PORTD
      INTCON2.RBPU = 0; // Habilita chave global dos resistores pull-up presente no PORTB
      WPUB.WPUB0 = 1; // Habilita o resistor pull-up interno no pino RB0
    #else
      ADCON1 |= 0x0F;
    #endif

    TRISD = 0;
    PORTD = 0; // apaga todos os segmentos do display
    configureTimer();
    configureGlobalInterruptions();
    configureTimer0();
    configureButtonInterruptions();
    while(1) {
        /*
        O programa entra em um looping indeterminado aqui,
        e a funcao interruptHandler() eh ativada pelos botoes e timer por conta da ativacao de alta prioridade
        */
    }
}
```

## Projeto Termometro:

- Arquivos: [Projeto 3 - Termometro Digital](/Entrega%204/Projeto%203%20-%20Termometro/) <br>

```c
// Configuração de pinos do LCD (PORTB)
#define TRUE 1 // Define TRUE como 1 para usar em loops

// Configuração dos pinos para o LCD
sbit LCD_RS at LATB4_bit;
sbit LCD_EN at LATB5_bit;
sbit LCD_D4 at LATB0_bit;
sbit LCD_D5 at LATB1_bit;
sbit LCD_D6 at LATB2_bit;
sbit LCD_D7 at LATB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;

// Programa Principal
void main() {
    unsigned int Valor_ADC = 0;  // Variável do valor analógico
    unsigned char Tensao[20];    // Arranjo textual para exibir no display

    TRISA.RA5 = 1; // RA5 = AN4, configura pino de entrada

    // Configuração do conversor AD
    ADCON0 = 0b00010001; // Configura canal AN4 como canal analógico, conversão AD habilitada mas não iniciada
    ADCON1 = 0b00111010; // Configura canais AN4-AN0 como canais de entrada analógica, tensão de ref externa
    ADCON2 = 0b10101010; // Justificação para direita, FOSC/32 (tempo entre 2 e 25 us) e 12 TAD (tempo de conversão de cada bit + 2 TAD)

    // Configuração do módulo LCD
    Lcd_Init();                 // Inicializa a biblioteca Lcd
    Lcd_Cmd(_LCD_CLEAR);        // Limpa o display
    Lcd_Cmd(_LCD_CURSOR_OFF);   // Cursor off
    Lcd_Out(1, 1, "TEMP:");     // Escreve no LCD o texto TEMP:

    while (TRUE) {
        ADCON0.GO_DONE = 1;           // Liga a leitura e inicia a conversão do ADC
        while (ADCON0.GO_DONE == 1);   // Aguarda o término da conversão (quando o bit volta a 0)

        Valor_ADC = ((ADRESH << 8) | ADRESL); // Combina os dois registradores da conversão

        // Ajustes de escala dos valores de conversão para colocar no formato float
        // de 2 casas após a vírgula, sem declarar variável float.
        Valor_ADC = Valor_ADC * (1000 / 1023.0); // Altera a escala do valor de 0-1023 para 0-1000

        Tensao[0] = (Valor_ADC / 1000) + '0'; // Converte o valor para ASCII para exibir no display
        Tensao[1] = (Valor_ADC / 100) % 10 + '0';
        Tensao[2] = (Valor_ADC / 10) % 10 + '0';
        Tensao[3] = '.';
        Tensao[4] = (Valor_ADC) % 10 + '0';
        Tensao[5] = 0xDF; // Código HEX para o símbolo de grau
        Tensao[6] = 'C'; // Temperatura em graus Celsius
        Tensao[7] = 0; // Terminador NULL

        // Exibir os valores no display LCD:
        Lcd_Out(2, 1, Tensao); // Mostra os valores no display
        Delay_ms(200);         // Atualizar display
    }
}


```