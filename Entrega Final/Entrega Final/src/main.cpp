// #define CUSTOM_SETTINGS
// #define INCLUDE_TERMINAL_MODULE
// #include <DabbleESP32.h>
#include <Arduino.h>

#define R 19
#define G 5
#define B 16

String Serialdata = "";
bool dataflag = 0;
int DutyCycle_R = 0;
int DutyCycle_G = 0;
int DutyCycle_B = 0;
int increment = 1; // Declaração da variável incremento

void setup() {
  Serial.begin(115200); // Configura a comunicação serial com uma taxa de transmissão de dados de 115200 bits por segundo.
  // Dabble.begin("MyEsp32-Pedro-Thallys-Renan"); // Define o nome do Bluetooth do dispositivo

  // Inicializar as saídas PWM para controle do LED
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {
  // Dabble.processInput(); // Função usada para atualizar dados obtidos do smartphone.

  // while (Serial.available() != 0) {
  //   /*
  //   A estrutura "while (Serial.available() != 0)" verifica se há dados disponíveis para leitura na porta serial.
  //   Se houver dados disponíveis, eles são lidos e concatenados na variável "Serialdata" até que nenhum dado esteja mais disponível.
  //   A variável "dataflag" é definida como 1 para indicar que dados foram recebidos.
  //   */
  //   Serialdata += char(Serial.read());
  //   dataflag = 1;
  // }

  // if (dataflag == 1) {
  //   // Impressão dos dados recebidos no Terminal
  //   Terminal.print(Serialdata);
  //   Serialdata = "";
  //   dataflag = 0;
  // }

  // if (Terminal.available() != 0) {
  //   Serial.write(Terminal.read());
  //   String command = Terminal.readString(); // Ler comando enviado pelo terminal
  //   increment = command.toInt(); // Converter o comando para um inteiro
  //   Terminal.print("Increment applied: ");
  //   Terminal.println(increment);
  //   Serial.println();
  // }

  // Atualizar o duty cycle para as cores do LED
  analogWrite(R, DutyCycle_R);
  analogWrite(G, DutyCycle_G);
  analogWrite(B, DutyCycle_B);

  // Aumentar o duty cycle de cada canal
  DutyCycle_R += 2 * increment;
  if (DutyCycle_R > 255) {
    DutyCycle_R = 0;
  }

  DutyCycle_G += increment;
  if (DutyCycle_G > 255) {
    DutyCycle_G = 0;
  }

  DutyCycle_B += 3 * increment;
  if (DutyCycle_B > 255) {
    DutyCycle_B = 0;
  }

  /*
  // Opcional: Printar o duty cycle
  Terminal.print("Red duty cycle: ");
  Terminal.println(DutyCycle_R);
  Terminal.print("Green duty cycle: ");
  Terminal.println(DutyCycle_G);
  Terminal.print("Blue duty cycle: ");
  Terminal.println(DutyCycle_B);
  */

  // Aguardar um pequeno intervalo antes de atualizar o ciclo de trabalho novamente
  delay(100);
}
