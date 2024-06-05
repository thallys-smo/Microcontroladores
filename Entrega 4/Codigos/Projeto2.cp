#line 1 "C:/Users/pcarr/OneDrive/Graduação/9° Período/Aplicação de Microprocessadores/Repositorio_Git/Microcontroladores/Entrega 4/Projeto2.c"
const unsigned short int displayValues[10] = {
 0b11111100,
 0b01100000,
 0b11011010,
 0b11110010,
 0b01100110,
 0b10110110,
 0b10111110,
 0b11100000,
 0b11111110,
 0b11110110,
};



short int pressedButton = -1;

unsigned short int counterIndex = 0;

void interruptHandler();

void configureTimer();

void configureGlobalInterruptions();

void configureTimer0();

void configureButtonInterruptions();




void main() {






 ADCON1 |= 0x0F;
 INTCON2.RBPU = 0;


 TRISD = 0;
 PORTD = 0;
 configureTimer();
 configureGlobalInterruptions();
 configureTimer0();
 configureButtonInterruptions();
 while(1) {
#line 55 "C:/Users/pcarr/OneDrive/Graduação/9° Período/Aplicação de Microprocessadores/Repositorio_Git/Microcontroladores/Entrega 4/Projeto2.c"
 }
}




void interruptHandler() iv 0x0008 ics ICS_AUTO {
 if(INTCON.INT0IF ==1) {
 pressedButton = 0;
 INTCON.INT0IF = 0;
 }

 if(INTCON3.INT1IF == 1) {
 pressedButton = 1;
 INTCON3.INT1IF = 0;
 }

 if(INTCON.TMR0IF == 1 && pressedButton != -1) {
 PORTD = displayValues[counterIndex];
 if(counterIndex<9) {
 counterIndex+=1;
 }
 else {
 counterIndex=0;
 }

 T0CON.TMR0ON = 0;

 if(pressedButton == 0) {
 T0CON = 0b00000100;
 }
 else if(pressedButton == 1) {
 T0CON = 0b00000010;
 }

 TMR0L = 0xDC;

 TMR0H = 0x0B;

 T0CON.TMR0ON = 1;

 T0CON.TMR0IF = 0;

 }
}

void configureTimer() {
 T0CON = 0b00000110;
 INTCON.TMR0IF = 0;
 T0CON.TMR0ON = 1;
}

void configureGlobalInterruptions() {
 INTCON.GIEH = 1;
 INTCON.GIEL = 1;
 RCON.IPEN = 1;
}

void configureTimer0() {
 INTCON.TMR0IF = 1;
 INTCON2.TMR0IP = 1;
 INTCON.TMR0IE = 1;
}

void configureButtonInterruptions() {
 INTCON.INT0IF = 0;
 INTCON.INT0IE = 1;

 INTCON.INT1IF = 0;
 INTCON.INT1IP = 1;
 INTCON.INT1IE = 1;

 INTCON2.INTEDG0 = 1;

 TRISB.RB0 = 1;
 TRISB.RB1 = 1;
}
