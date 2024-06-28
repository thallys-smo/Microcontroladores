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

  // Aguardar um pequeno intervalo antes de atualizar o ciclo de trabalho novamente
  delay(100);
}