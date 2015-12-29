// QUANTUS
// pinSetup.cpp

#include "pinSetup.hpp"


void pinSetup() {


  // Digital pin setup

  // Button (interrupt)
  pinMode(BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPress,  FALLING);

  // RGB LED
  pinMode(LED_RED,    OUTPUT);
  pinMode(LED_GREEN,  OUTPUT);
  pinMode(LED_BLUE,   OUTPUT);

  // SD card
  pinMode(CHIP_SELECT, OUTPUT);

  // !!!! Attach CD pin as interrupt
  // https://developer.mbed.org/cookbook/SD-Card-File-System



  // Ultrasonic sensor
  pinMode(ULTRASONIC_TRIGGER, OUTPUT);
  pinMode(ULTRASONIC_ECHO,    INPUT);


} // End of pinSetup
