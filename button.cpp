// QUANTUS
// button.cpp

// Attributions
// Debounce code adapted from https://www.arduino.cc/en/Tutorial/Debounce

#include "button.h"


bool buttonPress() {

  // !!! Implement debounce code later

  if (digitalRead(BUTTON) == HIGH) {
    return 0;
  }
  else {
    return 1;
  }

}
