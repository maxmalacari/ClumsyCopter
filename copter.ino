#include "./ReadRx/ReadRx.h"
#include <Servo.h>

// Define receiver pins
#define THROTTLE_PIN 4
#define ROLL_PIN 2
#define PITCH_PIN 3
#define YAW_PIN 5
#define ARM_PIN 7

// Define motor pins
#define MOTOR_1 6
#define MOTOR_2 9
#define MOTOR_3 10
#define MOTOR_4 11

Servo motors[4];

const int inputPins[5] = {THROTTLE_PIN,ROLL_PIN,PITCH_PIN,YAW_PIN,ARM_PIN};
const int motorPins[5] = {MOTOR_1,MOTOR_2,MOTOR_3,MOTOR_4};

void setup(){
  //Serial.begin(9600);
  ReadRxInit(inputPins); // Set up receiver with correct pins (later could make checking more sophisticated)
  for (int i=0; i<4; i++){
    motors[i].attach(motorPins[i]);
    motors[i].writeMicroseconds(1000);
  }
}

void loop(){
  ReadRx(); // Read the Rx values every loop iteration

  if (Armed()){
      motors[0].writeMicroseconds(GetThrottleVal());
      motors[1].writeMicroseconds(GetThrottleVal());
      motors[2].writeMicroseconds(GetThrottleVal());
      motors[3].writeMicroseconds(GetThrottleVal());
  }
  else{
    motors[0].writeMicroseconds(1000);
    motors[1].writeMicroseconds(1000);
    motors[2].writeMicroseconds(1000);
    motors[3].writeMicroseconds(1000);
  }

}