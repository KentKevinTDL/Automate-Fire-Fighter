#include <Adafruit_I2CDevice.h>
#include <AFMotor.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h> //include PWM Servo Driver library
#include <Servo.h>  //include servo.h library

Adafruit_PWMServoDriver firefight = Adafruit_PWMServoDriver();

int pos = 0;    
boolean fire = false;
 
#define Left 10      // left sensor
#define Right 12    // right sensor
#define Forward 13   //front sensor

//robo arm cnotroling servos
#define servo1 0 
#define servo2 1
#define servo3 2

#define LM1 3       // left motor
#define LM2 5       // left motor
#define RM1 6       // right motor
#define RM2 9       // right motor
#define pump 7
 
void setup()
{
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);

  firefight.begin();
  firefight.setPWMFreq(60);
  firefight.setPWM(servo1, 0, 340);
  firefight.setPWM(servo2, 0, 150);
  firefight.setPWM(servo3, 0, 300); 
}
 
void put_off_fire()
{
   delay (500);
 
   digitalWrite(LM1, LOW);
   digitalWrite(LM2, LOW);
   digitalWrite(RM1, LOW);
   digitalWrite(RM2, LOW);
     
  //robo arm motion 
  for (int S3value = 300; S3value <= 520; S3value++) {
    firefight.setPWM(servo3, 0, S3value);
    delay(10);
  }

   digitalWrite(pump, HIGH);
  
  for (int S2value = 150; S2value <= 190; S2value++) {
    firefight.setPWM(servo2, 0, S2value);
    delay(10);
  }
  for (int S1value = 340; S1value >= 150; S1value--) {
    firefight.setPWM(servo1, 0, S1value);
    delay(10);
  }
  for (int S2value = 190; S2value > 110; S2value--) {
    firefight.setPWM(servo2, 0, S2value);
    delay(10);
  }
  for (int S1value = 150; S1value < 530; S1value++) {
    firefight.setPWM(servo1, 0, S1value);
    delay(10);
  }
  for (int S2value = 110; S2value <= 150; S2value++) {
    firefight.setPWM(servo2, 0, S2value);
    delay(10);
  }
  for (int S1value = 530; S1value >= 340; S1value--) {
    firefight.setPWM(servo1, 0, S1value);
    delay(10);
  }

  digitalWrite(pump,LOW);
  
  for (int S3value = 520; S3value > 300; S3value--) {
    firefight.setPWM(servo3, 0, S3value);
    delay(10);
  }
  
  fire=false;
}
 
void loop()
{
  //robot moments through fire detection using fire sensors
    int motorSpeed = 150;  
 
    if (digitalRead(Left) ==1 && digitalRead(Right)==1 && digitalRead(Forward) ==1) 
    {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    }
    
    else if (digitalRead(Forward) ==0) 
    {
      analogWrite(LM1, motorSpeed);
      digitalWrite(LM2, LOW);
      analogWrite(RM1, motorSpeed);
      digitalWrite(RM2, LOW);
      fire = true;
    }
    
    else if (digitalRead(Left) ==0)
    {
      analogWrite(LM1, motorSpeed);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
    }
    
    else if (digitalRead(Right) ==0) 
    {
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      analogWrite(RM1, motorSpeed);
      digitalWrite(RM2, LOW);
    }
    
delay(100);//change this value to increase the distance between fire and the robot
 
     while (fire == true)
     {
      put_off_fire();
     }
}
