#include <Arduino.h>

#define R 19
#define G 5
#define B 16

int DutyCycle_R = 0;
int DutyCycle_G = 0;
int DutyCycle_B = 0;
int increment = 1; // Declaration of the increment variable

void setup() {
  Serial.begin(115200); // Configures serial communication with a data transmission rate of 115200 bits per second.
  
  // Initialize the PWM outputs for LED control
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {
  // Update duty cycle for LED colors
  analogWrite(R, DutyCycle_R);
  analogWrite(G, DutyCycle_G);
  analogWrite(B, DutyCycle_B);
  
  // Increase the duty cycle of each channel
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
  
  // Print increment and duty cycle values to Serial Monitor
  Serial.print("Increment: ");
  Serial.print(increment);
  Serial.print(", DutyCycle_R: ");
  Serial.print(DutyCycle_R);
  Serial.print(", DutyCycle_G: ");
  Serial.print(DutyCycle_G);
  Serial.print(", DutyCycle_B: ");
  Serial.println(DutyCycle_B);
  
  // Wait a short interval before updating the duty cycle again
  delay(100);
}
