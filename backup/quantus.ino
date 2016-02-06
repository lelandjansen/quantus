// QUANTUS
// quantus.ino

#include "quantus.hpp"

// Setup code (runs once)
void setup() {

  // Begin serial monitor (used for debugging)
  // Serial.begin(9600);


  pinSetup();

  // Set up timer interrupt
  // Run the led function ten times per second
  Timer1.initialize(10000);
  Timer1.attachInterrupt(led);
  PULSE_COUNT = 0;


  sdInserted() ? NEXT_STATE = STATE_SD_SETUP : NEXT_STATE = STATE_NO_SD;

} // End of setup



// Loop code (runs indefinitely)
void loop() {
  // State machine
  state();
} // End of loop


// That's all folks!
