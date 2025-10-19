#include <Arduino.h>

#include <ESP32Servo.h> 
 


Servo ESC1;  // create servo object to control a servo
Servo ESC2;
Servo ESC3;
Servo ESC4;

 // Possible PWM GPIO pins on the ESP32: 0(used by on-board button),2,4,5(used by on-board LED),12-19,21-23,25-27,32-33 
int servoPin = 13;      // GPIO pin used to connect the servo control (digital out)
int servoPin2 = 26;
int servoPin3 = 12;
int servoPin4 = 27 ;



void setup() {
  


Serial.begin(115200);


	// Allow allocation of all timers
	//ESP32PWM::allocateTimer(0);
	//ESP32PWM::allocateTimer(1);
	//ESP32PWM::allocateTimer(2);
	//ESP32PWM::allocateTimer(3);
  ESC1.setPeriodHertz(50);// Standard 50hz servo
  ESC2.setPeriodHertz(50);// Standard 50hz servo
  ESC3.setPeriodHertz(50);
  ESC4.setPeriodHertz(50);
  ESC1.attach(servoPin, 1000, 2500);   // attaches the servo on pin 18 to the servo object
                                         // using SG90 servo min/max of 500us and 2400us
                                         // for MG995 large servo, use 1000us and 2000us,
                                         // which are the defaults, so this line could be
                                         // "ESC1.attach(servoPin);"
  ESC2.attach(servoPin2, 1000, 2500);
  ESC3.attach(servoPin3, 1000, 2500);
  ESC4.attach(servoPin4, 1000, 2500);   


                       
}

void loop() {

    //val = analogRead(potPin);            // read the value of the potentiometer (value between 0 and 1023)
  for (float value = 1000; value <= 2500; value += 180) {
		// Write a unit vector value from 0.0 to 1.0
		int throttle = value;
    throttle = map(throttle, 1000, 2500, 0, 60);     // scale it to use it with the servo (value between 0 and 180)
     ESC1.write(throttle);                  // set the servo position according to the scaled value
     ESC2.write(throttle); 
     ESC3.write(throttle);
     ESC4.write(throttle);
    Serial.print(", throttle: "); Serial.println(throttle);
		delay(1000);     
  }           
}