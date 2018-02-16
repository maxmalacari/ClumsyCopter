#ifndef ReadRx_h
#define ReadRx_h

#include <Arduino.h>
#include "../libraries/EnableInterrupt/EnableInterrupt.h"

int channel[5] = {0,1,2,3,4};
int inputPin[5] = {5,7,6,4,3}; // default pins for throttle, roll, pitch, yaw, arm
uint16_t rc_values[5] = {1000,1500,1500,1500,1000}; // start at sensible values
uint32_t rc_start[5];
volatile uint16_t rc_shared[5];

// Main function to call each loop to read the Rx values
// Turns off interrupts (so no data is written to rc_shared while we read it)
// Copies this constantly changing array into an array that won't change during the loop
void ReadRx() {
  noInterrupts();
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}

// If interrupt triggers on input_pin, calculate the width of the pulse
// If beginning of pulse (going high) record the time in rc_start for this channel
// If end of pulse calculate the time difference to the start of the pulse and save
// it in rc_shared. rc_shared will be copied to an array for reading when ReadRx() is called
void calc_input(uint8_t channel, uint8_t input_pin) {
  if (digitalRead(input_pin) == HIGH) {
    rc_start[channel] = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
    rc_shared[channel] = rc_compare;
  }
}

// Functions to call for each pin interrupt
void calc_ch1() { calc_input(channel[0], inputPin[0]); }
void calc_ch2() { calc_input(channel[1], inputPin[1]); }
void calc_ch3() { calc_input(channel[2], inputPin[2]); }
void calc_ch4() { calc_input(channel[3], inputPin[3]); }
void calc_ch5() { calc_input(channel[4], inputPin[4]); }

void ReadRxInit(int pins[]) {

  for (int i=0; i<5; i++){
    inputPin[i] = pins[i];
    pinMode(inputPin[i], INPUT);
  }

  enableInterrupt(inputPin[0], calc_ch1, CHANGE); // interrupt pin, function to call if triggered
  enableInterrupt(inputPin[1], calc_ch2, CHANGE);
  enableInterrupt(inputPin[2], calc_ch3, CHANGE);
  enableInterrupt(inputPin[3], calc_ch4, CHANGE);
  enableInterrupt(inputPin[4], calc_ch5, CHANGE);
}

int GetThrottleVal() { return rc_values[0]; }
int GetRollVal() { return rc_values[1]; }
int GetPitchVal() { return rc_values[2]; }
int GetYawVal() { return rc_values[3]; }
bool Armed() {
  if (rc_values[4] > 1500) return true;
  else return false;
}

#endif
