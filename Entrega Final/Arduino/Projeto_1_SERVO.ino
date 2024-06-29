#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); //criando projeto cahmado lcd como seu tamanho

// Servo
#define SPWM 32
Servo servo;

// Buttons
#define ButtonStart 4
#define ButtonStop 2

// Variables
int currentAngle = 0;            // To track the current angle of the servo
bool startPressed = false;       // Flag to track if the start button has been pressed
bool stopPressed = false;        // Flag to track if the stop button has been pressed
const int buttonDelay = 50;      // Delay to debounce the button (in milliseconds)
const int servoDelayUp = 100;    // Delay between angle increments when moving up (in milliseconds)
const int servoDelayDown = 200;  // Delay between angle increments when moving down (in milliseconds)
const int servoWaitTime = 1000;  // Wait time at 180 degrees (in milliseconds)

void IRAM_ATTR startButtonPressed() {
  startPressed = true;
  stopPressed = false;
}

void IRAM_ATTR stopButtonPressed() {
  stopPressed = true;
  startPressed = false;
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  // Set button pins as input with pull-up resistors
  pinMode(ButtonStart, INPUT_PULLUP);
  pinMode(ButtonStop, INPUT_PULLUP);

  // Attach interrupts to the button pins
  attachInterrupt(digitalPinToInterrupt(ButtonStart), startButtonPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(ButtonStop), stopButtonPressed, FALLING);

  // Attach the servo to the pin with min and max pulse width
  servo.attach(SPWM, 500, 2500);
  servo.write(currentAngle);  // Set initial position to 0 degrees

  lcd.setCursor(2,0);
  lcd.print("Projeto Servo e Esp32");
  lcd.setCursor(0,1);
  lcd.print("Microcontroladores");
  delay(4000); 
  lcd.clear(); 
}

void loop() {
  // Control servo movement based on the flags set by the buttons
  if (startPressed && !stopPressed) {
    moveServo();
  }

  // If stop button is pressed, stop the servo
  if (stopPressed) {
    servo.detach(); // Detach the servo to stop it
    stopPressed = false; // Reset the stop flag
    lcd.setCursor(2,0);
    lcd.print("Sistema Parado");
    lcd.setCursor(0,1);
    lcd.print("Microcontroladores");
    delay(4000); 
    lcd.clear();
  }
  
}

void moveServo() {
  // Move the servo from 0° to 180°
  for (currentAngle = 0; currentAngle <= 180; currentAngle++) {
    if (stopPressed) return;  // Exit if stop button is pressed
    servo.write(currentAngle);
    delay(servoDelayUp);
    lcd.setCursor(2,0);
    lcd.print("Direita");
    lcd.setCursor(0,1);
    lcd.print("Microcontroladores");
  }

  lcd.clear();

  delay(servoWaitTime); // Wait for 1 second at 180°

  // Move the servo from 180° back to 0°
  for (currentAngle = 180; currentAngle >= 0; currentAngle--) {
    if (stopPressed) return;  // Exit if stop button is pressed
    servo.write(currentAngle);
    delay(servoDelayDown);
    lcd.setCursor(2,0);
    lcd.print("Esquerda");
    lcd.setCursor(0,1);
    lcd.print("Microcontroladores");
    // 
  }

  lcd.clear();
}
