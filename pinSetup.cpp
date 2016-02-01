// QUANTUS
// pinSetup.cpp

#include "pinSetup.hpp"

// Digital pin setup
void pinSetup() {

  // Button (interrupt)
  pinMode(BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPress,  RISING);

  // RGB LED
  pinMode(LED_RED,    OUTPUT);
  pinMode(LED_GREEN,  OUTPUT);
  pinMode(LED_BLUE,   OUTPUT);

  // SD card
  pinMode(CHIP_SELECT, OUTPUT);
  pinMode(CARD_DETECT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CARD_DETECT), sdChange, CHANGE);

  // Ultrasonic sensor
  pinMode(ULTRASONIC_TRIGGER, OUTPUT);
  pinMode(ULTRASONIC_ECHO,    INPUT);

  // Temperature sensor
  // TMP36 temperature sensor using 3.3 V (not 5 V)
  analogReference(EXTERNAL);

} // End of pinSetup
