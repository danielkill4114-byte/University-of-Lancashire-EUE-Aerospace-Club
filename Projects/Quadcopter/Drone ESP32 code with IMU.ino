#include <Arduino.h>
#include <Wire.h>

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


float RateRoll, RatePitch, RateYaw;
float RateCalibrationRoll, RateCalibrationPitch, RateCalibrationYaw;
int RateCalibrationNumber;



void gyro_signals(void) {
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission(); 
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission(); 
  Wire.requestFrom(0x68,6);
  int16_t GyroX=Wire.read()<<8 | Wire.read();
  int16_t GyroY=Wire.read()<<8 | Wire.read();
  int16_t GyroZ=Wire.read()<<8 | Wire.read();
  RateRoll=(float)GyroX/65.5;
  RatePitch=(float)GyroY/65.5;
  RateYaw=(float)GyroZ/65.5;
}
void setup() {
  


  Serial.begin(115200);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Wire.setClock(400000);
  Wire.begin();
  delay(250);

Serial.begin(115200);
  Wire.beginTransmission(0x68); 
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  for (RateCalibrationNumber=0;
         RateCalibrationNumber<100; 
         RateCalibrationNumber ++) {
    gyro_signals();
    RateCalibrationRoll+=RateRoll;
    RateCalibrationPitch+=RatePitch;
    RateCalibrationYaw+=RateYaw;
    delay(1);
  }
  RateCalibrationRoll/=100;
  RateCalibrationPitch/=100;
  RateCalibrationYaw/=100;   

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
void loop() {
    
  gyro_signals();
  RateRoll-=RateCalibrationRoll;
  RatePitch-=RateCalibrationPitch;
  RateYaw-=RateCalibrationYaw;
  Serial.print("Roll rate [°/s]= ");
  Serial.print(RateRoll); 
  Serial.print(",");
  Serial.print(" Pitch Rate [°/s]= ");
  Serial.print(RatePitch);
  Serial.print(",");
  Serial.print(" Yaw Rate [°/s]= ");
  Serial.println(RateYaw);
  delay(50);
   
}
