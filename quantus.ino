// QUANTUS
// quantus.ino

#include "quantus.hpp"


void setup() {

  // Begin serial monitor
  Serial.begin(9600);

  // Set up pins
  pinSetup();

  // Timer interrupt
  // Run the function ten times per second
  Timer1.initialize(10000);
  Timer1.attachInterrupt(led); // attach the service routine here
  PULSE_COUNT = 0;

  sdChange();

} // End of setup


void loop() {

  // Serial.println(F("-3"));

  state();

} // End of loop


// That's all folks!
