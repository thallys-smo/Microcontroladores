const unsigned short int displayValues[10] = { // o arranjo com todas as possíveis configurações do display
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

// Declaração das funçoes utilizadas e variáveis globais

short int pressedButton = -1; // indica qual botao foi pressionado: 0 para RB0 e 1 para RB1

unsigned short int counterIndex = 0; // indice para contagem do display

void interruptHandler(); // checa interrupcao de alta prioridade acionada -> manipula intervalo de tempo de acordo com botão pressionado

void configureTimer(); // configura o timer do microcontrolador

void configureGlobalInterruptions(); // Ativa interrupções globais

void configureTimer0(); // Configura o Timer 0

void configureButtonInterruptions(); //  configura as interrupções dos botoes INT0 e INT1


// Código principal

void main() {
    #ifdef P18F45K22
      ANSELB = 0; // desativa entradas analogicas da PORTB
      ANSELD = 0; // desativa entradas analogicas da PORTD
      INTCON2.RBPU = 0; // Habilita chave global dos resistores pull-up presente no PORTB
      WPUB.WPUB0 = 1; // Habilita o resistor pull-up interno no pino RB0
    #else
      ADCON1 |= 0x0F;
      INTCON2.RBPU = 0; // habilita chave global dos resistores pull-up presente no PORTB
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
        e a funcao interruptHandler() é ativada pelos botoes e timer por conta da ativacao de alta prioridade
        */
    }
}


// Definição das funções

void interruptHandler() iv 0x0008 ics ICS_AUTO {
    if(INTCON.INT0IF ==1) { // checa acionamento do botão RB0
      pressedButton = 0; // botao RB0 -> botao = 0
      INTCON.INT0IF = 0; // limpar valor do botao de interrupcao
    }
    
    if(INTCON3.INT1IF == 1) { // checa acionamento do botão RB1
        pressedButton = 1; // botao RB1 -> botao = 1
        INTCON3.INT1IF = 0; // limpar valor do botao de interrupcao
    }
    
    if(INTCON.TMR0IF == 1 && pressedButton != -1) { // checa interrupcao pelo Timer 0
        PORTD = displayValues[counterIndex]; // exibe o digito atual no display
        if(counterIndex<9) {
            counterIndex+=1; // enquanto não estiver no final, incrementa 1 no contador
        }
        else {
            counterIndex=0; // quando chega no final, reinicia a contagem
        }
        
        T0CON.TMR0ON = 0; // desativa o timer
        
        if(pressedButton == 0) {
            T0CON = 0b00000100; // configura o intervalo de mudança de numero para 1s
        }
        else if(pressedButton == 1) {
            T0CON = 0b00000010; // configura o intervalo de mudança de numero para 0.25s
        }
        
        TMR0L = 0xDC; // set do limite inferior do timer em hexadecimal
        
        TMR0H = 0x0B; // set do limite superior do timer em hexadecimal
        
        T0CON.TMR0ON = 1; // Liga o timer
        
        T0CON.TMR0IF = 0; // limpa a interrupção do timer
        
    }
}

void configureTimer() {
    T0CON = 0b00000110; // configura timer de 16 bits
    INTCON.TMR0IF = 0; // limpa interupção do timer
    T0CON.TMR0ON = 1; // liga o timer
}

void configureGlobalInterruptions() {
    INTCON.GIEH = 1; // Ativa interrupcoes de alta prioridade
    INTCON.GIEL = 1; // Ativa interrupcoes de baixa prioridade
    RCON.IPEN = 1; // Ativa o seletor de prioridades das interrupcoes
}

void configureTimer0() {
    INTCON.TMR0IF = 1; // Configura botao de interrupcao do timer
    INTCON2.TMR0IP = 1; // Muda prioridade de interrupcao do timer para alta
    INTCON.TMR0IE = 1; // Ativa a interrupcao do timer
}

void configureButtonInterruptions() {
    INTCON.INT0IF = 0; // Limpa flag de interrupcao do INT0
    INTCON.INT0IE = 1; // Ativa a flag de interrupcao do INT0

    INTCON.INT1IF = 0; // Limpa flag de interrupcao do INT1
    INTCON.INT1IP = 1; // Muda prioridade de interrupção de INT1 para alta
    INTCON.INT1IE = 1; // Limpa flag de interrupcao do INT1

    INTCON2.INTEDG0 = 1; // Configura borda de ativação de interrupcao do INT0 como subida

    TRISB.RB0 = 1; // Configura pino RB0 com entrada da PORTB
    TRISB.RB1 = 1; // Configura pino RB1 como entrada da PORTB
}