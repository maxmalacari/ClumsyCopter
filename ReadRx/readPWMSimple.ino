#include "ReadRx.h"

// Define receiver pins
#define THROTTLE_PIN 5
#define ROLL_PIN 3
#define PITCH_PIN 4
#define YAW_PIN 6
#define ARM_PIN 7

const int inputPins[5] = {THROTTLE_PIN,ROLL_PIN,PITCH_PIN,YAW_PIN,ARM_PIN};

void setup(){
  Serial.begin(9600);
  ReadRxInit(inputPins); // Set up receiver with correct pins (later could make checking more sophisticated)
}

void loop(){
  ReadRx(); // Read the Rx values every loop iteration

  if (Armed()){
  Serial.print(GetThrottleVal()); Serial.print("\t");
  Serial.print(GetRollVal()); Serial.print("\t");
  Serial.print(GetPitchVal()); Serial.print("\t");
  Serial.print(GetYawVal()); Serial.print("\n");
  }

}

