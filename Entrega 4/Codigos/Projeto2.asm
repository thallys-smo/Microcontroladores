
_main:

;Projeto2.c,33 :: 		void main() {
;Projeto2.c,40 :: 		ADCON1 |= 0x0F;
	MOVLW       15
	IORWF       ADCON1+0, 1 
;Projeto2.c,41 :: 		INTCON2.RBPU = 0; // habilita chave global dos resistores pull-up presente no PORTB
	BCF         INTCON2+0, 7 
;Projeto2.c,44 :: 		TRISD = 0;
	CLRF        TRISD+0 
;Projeto2.c,45 :: 		PORTD = 0; // apaga todos os segmentos do display
	CLRF        PORTD+0 
;Projeto2.c,46 :: 		configureTimer();
	CALL        _configureTimer+0, 0
;Projeto2.c,47 :: 		configureGlobalInterruptions();
	CALL        _configureGlobalInterruptions+0, 0
;Projeto2.c,48 :: 		configureTimer0();
	CALL        _configureTimer0+0, 0
;Projeto2.c,49 :: 		configureButtonInterruptions();
	CALL        _configureButtonInterruptions+0, 0
;Projeto2.c,50 :: 		while(1) {
L_main0:
;Projeto2.c,55 :: 		}
	GOTO        L_main0
;Projeto2.c,56 :: 		}
L_end_main:
	GOTO        $+0
; end of _main

_interruptHandler:

;Projeto2.c,61 :: 		void interruptHandler() iv 0x0008 ics ICS_AUTO {
;Projeto2.c,62 :: 		if(INTCON.INT0IF ==1) { // checa acionamento do botão RB0
	BTFSS       INTCON+0, 1 
	GOTO        L_interruptHandler2
;Projeto2.c,63 :: 		pressedButton = 0; // botao RB0 -> botao = 0
	CLRF        _pressedButton+0 
;Projeto2.c,64 :: 		INTCON.INT0IF = 0; // limpar valor do botao de interrupcao
	BCF         INTCON+0, 1 
;Projeto2.c,65 :: 		}
L_interruptHandler2:
;Projeto2.c,67 :: 		if(INTCON3.INT1IF == 1) { // checa acionamento do botão RB1
	BTFSS       INTCON3+0, 0 
	GOTO        L_interruptHandler3
;Projeto2.c,68 :: 		pressedButton = 1; // botao RB1 -> botao = 1
	MOVLW       1
	MOVWF       _pressedButton+0 
;Projeto2.c,69 :: 		INTCON3.INT1IF = 0; // limpar valor do botao de interrupcao
	BCF         INTCON3+0, 0 
;Projeto2.c,70 :: 		}
L_interruptHandler3:
;Projeto2.c,72 :: 		if(INTCON.TMR0IF == 1 && pressedButton != -1) { // checa interrupcao pelo Timer 0
	BTFSS       INTCON+0, 2 
	GOTO        L_interruptHandler6
	MOVF        _pressedButton+0, 0 
	XORLW       255
	BTFSC       STATUS+0, 2 
	GOTO        L_interruptHandler6
L__interruptHandler12:
;Projeto2.c,73 :: 		PORTD = displayValues[counterIndex]; // exibe o digito atual no display
	MOVLW       _displayValues+0
	ADDWF       _counterIndex+0, 0 
	MOVWF       TBLPTR+0 
	MOVLW       hi_addr(_displayValues+0)
	MOVWF       TBLPTR+1 
	MOVLW       0
	ADDWFC      TBLPTR+1, 1 
	MOVLW       higher_addr(_displayValues+0)
	MOVWF       TBLPTR+2 
	MOVLW       0
	ADDWFC      TBLPTR+2, 1 
	TBLRD*+
	MOVFF       TABLAT+0, PORTD+0
;Projeto2.c,74 :: 		if(counterIndex<9) {
	MOVLW       9
	SUBWF       _counterIndex+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_interruptHandler7
;Projeto2.c,75 :: 		counterIndex+=1; // enquanto não estiver no final, incrementa 1 no contador
	INCF        _counterIndex+0, 1 
;Projeto2.c,76 :: 		}
	GOTO        L_interruptHandler8
L_interruptHandler7:
;Projeto2.c,78 :: 		counterIndex=0; // quando chega no final, reinicia a contagem
	CLRF        _counterIndex+0 
;Projeto2.c,79 :: 		}
L_interruptHandler8:
;Projeto2.c,81 :: 		T0CON.TMR0ON = 0; // desativa o timer
	BCF         T0CON+0, 7 
;Projeto2.c,83 :: 		if(pressedButton == 0) {
	MOVF        _pressedButton+0, 0 
	XORLW       0
	BTFSS       STATUS+0, 2 
	GOTO        L_interruptHandler9
;Projeto2.c,84 :: 		T0CON = 0b00000100; // configura o intervalo de mudança de numero para 1s
	MOVLW       4
	MOVWF       T0CON+0 
;Projeto2.c,85 :: 		}
	GOTO        L_interruptHandler10
L_interruptHandler9:
;Projeto2.c,86 :: 		else if(pressedButton == 1) {
	MOVF        _pressedButton+0, 0 
	XORLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L_interruptHandler11
;Projeto2.c,87 :: 		T0CON = 0b00000010; // configura o intervalo de mudança de numero para 0.25s
	MOVLW       2
	MOVWF       T0CON+0 
;Projeto2.c,88 :: 		}
L_interruptHandler11:
L_interruptHandler10:
;Projeto2.c,90 :: 		TMR0L = 0xDC; // set do limite inferior do timer em hexadecimal
	MOVLW       220
	MOVWF       TMR0L+0 
;Projeto2.c,92 :: 		TMR0H = 0x0B; // set do limite superior do timer em hexadecimal
	MOVLW       11
	MOVWF       TMR0H+0 
;Projeto2.c,94 :: 		T0CON.TMR0ON = 1; // Liga o timer
	BSF         T0CON+0, 7 
;Projeto2.c,96 :: 		T0CON.TMR0IF = 0; // limpa a interrupção do timer
	BCF         T0CON+0, 2 
;Projeto2.c,98 :: 		}
L_interruptHandler6:
;Projeto2.c,99 :: 		}
L_end_interruptHandler:
L__interruptHandler15:
	RETFIE      1
; end of _interruptHandler

_configureTimer:

;Projeto2.c,101 :: 		void configureTimer() {
;Projeto2.c,102 :: 		T0CON = 0b00000110; // configura timer de 16 bits
	MOVLW       6
	MOVWF       T0CON+0 
;Projeto2.c,103 :: 		INTCON.TMR0IF = 0; // limpa interupção do timer
	BCF         INTCON+0, 2 
;Projeto2.c,104 :: 		T0CON.TMR0ON = 1; // liga o timer
	BSF         T0CON+0, 7 
;Projeto2.c,105 :: 		}
L_end_configureTimer:
	RETURN      0
; end of _configureTimer

_configureGlobalInterruptions:

;Projeto2.c,107 :: 		void configureGlobalInterruptions() {
;Projeto2.c,108 :: 		INTCON.GIEH = 1; // Ativa interrupcoes de alta prioridade
	BSF         INTCON+0, 7 
;Projeto2.c,109 :: 		INTCON.GIEL = 1; // Ativa interrupcoes de baixa prioridade
	BSF         INTCON+0, 6 
;Projeto2.c,110 :: 		RCON.IPEN = 1; // Ativa o seletor de prioridades das interrupcoes
	BSF         RCON+0, 7 
;Projeto2.c,111 :: 		}
L_end_configureGlobalInterruptions:
	RETURN      0
; end of _configureGlobalInterruptions

_configureTimer0:

;Projeto2.c,113 :: 		void configureTimer0() {
;Projeto2.c,114 :: 		INTCON.TMR0IF = 1; // Configura botao de interrupcao do timer
	BSF         INTCON+0, 2 
;Projeto2.c,115 :: 		INTCON2.TMR0IP = 1; // Muda prioridade de interrupcao do timer para alta
	BSF         INTCON2+0, 2 
;Projeto2.c,116 :: 		INTCON.TMR0IE = 1; // Ativa a interrupcao do timer
	BSF         INTCON+0, 5 
;Projeto2.c,117 :: 		}
L_end_configureTimer0:
	RETURN      0
; end of _configureTimer0

_configureButtonInterruptions:

;Projeto2.c,119 :: 		void configureButtonInterruptions() {
;Projeto2.c,120 :: 		INTCON.INT0IF = 0; // Limpa flag de interrupcao do INT0
	BCF         INTCON+0, 1 
;Projeto2.c,121 :: 		INTCON.INT0IE = 1; // Ativa a flag de interrupcao do INT0
	BSF         INTCON+0, 4 
;Projeto2.c,123 :: 		INTCON.INT1IF = 0; // Limpa flag de interrupcao do INT1
	BCF         INTCON+0, 0 
;Projeto2.c,124 :: 		INTCON.INT1IP = 1; // Muda prioridade de interrupção de INT1 para alta
	BSF         INTCON+0, 6 
;Projeto2.c,125 :: 		INTCON.INT1IE = 1; // Limpa flag de interrupcao do INT1
	BSF         INTCON+0, 3 
;Projeto2.c,127 :: 		INTCON2.INTEDG0 = 1; // Configura borda de ativação de interrupcao do INT0 como subida
	BSF         INTCON2+0, 6 
;Projeto2.c,129 :: 		TRISB.RB0 = 1; // Configura pino RB0 com entrada da PORTB
	BSF         TRISB+0, 0 
;Projeto2.c,130 :: 		TRISB.RB1 = 1; // Configura pino RB1 como entrada da PORTB
	BSF         TRISB+0, 1 
;Projeto2.c,131 :: 		}
L_end_configureButtonInterruptions:
	RETURN      0
; end of _configureButtonInterruptions
