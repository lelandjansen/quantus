// QUANTUS
// pinSetup.cpp

#include "pinSetup.h"

void pinSetup() {

  // Digital pin setup
  pinMode(BUTTON,             INPUT);
  pinMode(LED_RED,            OUTPUT);
  pinMode(LED_GREEN,          OUTPUT);
  pinMode(LED_BLUE,           OUTPUT);
  pinMode(CHIP_SELECT,        OUTPUT);
  pinMode(ULTRASONIC_TRIGGER, OUTPUT);
  pinMode(ULTRASONIC_ECHO,    INPUT);
  pinMode(FREQUENCY_SELECT_1, INPUT);
  pinMode(FREQUENCY_SELECT_2, INPUT);
  pinMode(FREQUENCY_SELECT_3, INPUT);
  pinMode(SD_RESERVED,        OUTPUT);
  // Pin 11: MOSI for SD
  // Pin 12: MISO for SD
  // Pin 13: CLK for SD

}
