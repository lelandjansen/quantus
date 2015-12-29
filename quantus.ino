// QUANTUS
// quantus.ino

#include "quantus.hpp"


void setup() {

  // Begin serial monitor
  Serial.begin(9600);

  // Set up pins
  pinSetup();

  // Timer interrupt
  // Run the function once every *** seconds
  Timer1.initialize(10000);
  Timer1.attachInterrupt(led); // attach the service routine here
  PULSE_COUNT = 0;

  STATE      = STATE_SD_SETUP;
  NEXT_STATE = STATE_SD_SETUP;

} // End of setup


void loop() {

  state();

} // End of loop


// That's all folks!
