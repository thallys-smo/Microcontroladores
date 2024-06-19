// As linhas "#define CUSTOM_SETTINGS" e "#define INCLUDE_TERMINAL_MODULE" são usadas para definir configurações para o programa e incluir módulo Terminal na biblioteca DabbleESP32.
#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <DabbleESP32.h>
#define PIN  2

String Serialdata = "";
bool dataflag = 0;
int DutyCycle_R = 0;
int DutyCycle_G = 0;
int DutyCycle_B = 0;

void setup() {
  Serial.begin(115200);       //configura a comunicação serial com uma taxa de transmissão de dados de 115200 bits por segundo.
  Dabble.begin("MyEsp32-Pedro-Thallys-Renan");    //set bluetooth name of your device
  
  // Inicializar as saídas PWM para controle do LED 
  ledcSetup(0, 5000, 8); // escolhendo o canal PWM 0, ...
  //frequência = 5000 Hz e resolução de 8 bits = divide o sinal PWM em 256 níveis (incrementos do ciclo de trabalho)
  ledcSetup(1, 5000, 8); // escolhendo o canal PWM 1, ...
  //frequência = 5000 Hz e resolução de 8 bits = divide o sinal PWM em 256 níveis (incrementos do ciclo de trabalho)
  ledcSetup(2, 5000, 8); // escolhendo o canal PWM 2, ...
  //frequência = 5000 Hz e resolução de 8 bits = divide o sinal PWM em 256 níveis (incrementos do ciclo de trabalho)

  ledcAttachPin(PIN, 0);   // Vincular o canal 0 ao pino do LED
  ledcAttachPin(PIN, 1);   // Vincular o canal 1 ao pino do LED
  ledcAttachPin(PIN, 2);   // Vincular o canal 2 ao pino do LED

}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.
  while (Serial.available() != 0)
  /*
  A estrutura "while (Serial.available() != 0)" verifica se há dados disponíveis para leitura na porta serial.
  Se houver dados disponíveis, eles são lidos e concatenados na variável "Serialdata" até que nenhum dado esteja mais disponível.
  A variável "dataflag" é definida como 1 para indicar que dados foram recebidos.

  */
  {
    Serialdata = String(Serialdata + char(Serial.read()));
    dataflag = 1;
  }

  if (dataflag == 1)
  {
    //Impressão dos dados recebidos no Terminal: Se "dataflag" for igual a 1, isso significa que foram recebidos dados da porta serial.
    //A função "Terminal.print(Serialdata);" imprime os dados recebidos no Terminal
    Terminal.print(Serialdata);
    Serialdata = "";
    dataflag = 0;
  }

  if (Terminal.available() != 0)
  {
    Serial.write(Terminal.read());
    String command = Terminal.readString(); // ler comando enviado pelo terminal
    incremento = command.toInt(); // converter o comando para um inteiro
    Terminal.print("Increment applied: ")
    Terminal.println(incremento)
    Serial.println();
  }

  // Atualizar o duty cycle para as cores do LED
  ledcWrite(0, DutyCycle_R);
  ledcWrite(1, DutyCycle_G);
  ledcWrite(2, DutyCycle_B);

  // Aumentar o duty cycle de cada canal

  DutyCycle_R += 2*incremento;
  if (DutyCycle_R > 255) {
    DutyCycle_R = 0;
  }

  DutyCycle_G += incremento;
  if (DutyCycle_G > 255) {
    DutyCycle_G = 0;
  }

  DutyCycle_B += 3*incremento;
  if (DutyCycle_B > 255) {
    DutyCycle_B = 0;
  }

  /*// é pra printar o duty cycle?
  Terminal.print("Red duty cycle: ")
  Terminal.println(DutyCycle_R)
  Terminal.print("Green duty cycle: ")
  Terminal.println(DutyCycle_G)
  Terminal.print("Blue duty cycle: ")
  Terminal.println(DutyCycle_B)
  */

  // Aguardar um pequeno intervalo antes de atualizar o ciclo de trabalho novamente
  delay(100);
}