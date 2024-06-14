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
