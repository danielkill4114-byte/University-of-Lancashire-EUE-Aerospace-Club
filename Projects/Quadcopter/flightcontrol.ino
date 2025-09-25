#include <Servo.h>

Servo esc;  // Create a Servo object to handle the ESC signal
Servo esc2;
Servo esc3;
Servo esc4;

// Set the ESC signal pin (must be a pin that supports PWM on Arduino Uno)
const int ESC_PIN = 6; //4
const int ESC_PIN2 = 9; //1
const int ESC_PIN3 = 5; //2
const int ESC_PIN4 = 11; //3

// Minimum and maximum pulse widths (microseconds) for your ESC/motor.
// Adjust these if needed (commonly 1000µs to 2000µs):
const int MIN_PULSE = 1000;
const int MAX_PULSE = 2000;

void setup() {
  // Attach the ESC on pin 9, use default 544 to 2400 µs range or specify your own
  esc.attach(ESC_PIN, MIN_PULSE, MAX_PULSE);
  esc2.attach(ESC_PIN2, MIN_PULSE, MAX_PULSE);
  esc3.attach(ESC_PIN3, MIN_PULSE, MAX_PULSE);
  esc4.attach(ESC_PIN4, MIN_PULSE, MAX_PULSE);

  // ESCs often need an arming sequence:
  // 1. Send minimum throttle
  esc.writeMicroseconds(MIN_PULSE);
  esc2.writeMicroseconds(MIN_PULSE);
  esc3.writeMicroseconds(MIN_PULSE);
  esc4.writeMicroseconds(MIN_PULSE);
  delay(300); // Wait for ESC to initialize
}

void loop() {
  // Example: Ramp up from MIN_PULSE to MAX_PULSE
  for (int pulse = MIN_PULSE; pulse <= MAX_PULSE; pulse += 10) {
    esc.writeMicroseconds(pulse);
    esc2.writeMicroseconds(pulse);
    esc3.writeMicroseconds(pulse);
    esc4.writeMicroseconds(pulse);
    delay(500);
  }

  // Ramp down from MAX_PULSE to MIN_PULSE
   for (int pulse = MIN_PULSE; pulse <= MAX_PULSE; pulse += 10) {
    esc.writeMicroseconds(pulse);
    esc2.writeMicroseconds(pulse);
    esc3.writeMicroseconds(pulse);
    esc4.writeMicroseconds(pulse);
    delay(500);
   }
}
