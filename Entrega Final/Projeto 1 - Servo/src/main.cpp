#include <ESP32Servo.h>
#include <Arduino.h>

const int servoPin = 18;        // Servo signal pin
const int buttonStartPin = 4;   // Start button pin
const int buttonStopPin = 2;    // Stop button pin
const int buttonDelay = 50;     // Delay to debounce the button (in milliseconds)
const int servoIncrement = 1;   // Angle increment for each iteration
const int servoDelayUp = 100;   // Delay between angle increments when moving up (in milliseconds)
const int servoDelayDown = 200; // Delay between angle increments when moving down (in milliseconds)
const int servoWaitTime = 1000; // Wait time at 180 degrees (in milliseconds)

Servo servo;
int currentAngle = 0;           // To track the current angle of the servo
bool startPressed = false;      // Flag to track if the start button has been pressed
bool stopPressed = false;       // Flag to track if the stop button has been pressed

void setup() {
  servo.attach(servoPin, 500, 2500); // Attach the servo to the pin with min and max pulse width
  pinMode(buttonStartPin, INPUT_PULLUP); // Set start button pin as input with pull-up
  pinMode(buttonStopPin, INPUT_PULLUP);  // Set stop button pin as input with pull-up
  servo.write(currentAngle);             // Set initial position to 0 degrees
}

void loop() {
  if (digitalRead(buttonStartPin) == LOW && !startPressed) {
    delay(buttonDelay); // Debounce delay
    if (digitalRead(buttonStartPin) == LOW) { // Confirm the button press
      startPressed = true;
      stopPressed = false;
      moveServo();
    }
  }

  if (digitalRead(buttonStopPin) == LOW && !stopPressed) {
    delay(buttonDelay); // Debounce delay
    if (digitalRead(buttonStopPin) == LOW) { // Confirm the button press
      stopPressed = true;
      startPressed = false;
      servo.detach(); // Detach the servo to stop it
    }
  }
}

void moveServo() {
  // Move the servo from 0° to 180°
  while (currentAngle < 180 && startPressed && !stopPressed) {
    currentAngle += servoIncrement;
    servo.write(currentAngle);
    delay(servoDelayUp);
  }

  delay(servoWaitTime); // Wait for 1 second at 180°

  // Move the servo from 180° back to 0°
  while (currentAngle > 0 && startPressed && !stopPressed) {
    currentAngle -= servoIncrement;
    servo.write(currentAngle);
    delay(servoDelayDown);
  }

  // Reset the servo position to 0° and reattach it for the next cycle
  currentAngle = 0;
  servo.write(currentAngle);
  if (startPressed && !stopPressed) {
    delay(servoDelayDown); // Small delay before the next cycle
    moveServo(); // Recursively call the function to repeat the process
  }
}