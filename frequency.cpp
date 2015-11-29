// QUANTUS
// frequency.cpp

#include "frequency.h"

int getFrequency() {

  // Binary numbers A (least significant), B, C (most significant)
  int a, b, c;

  // If pin is high, variable value is 1. If pin is low, variable value is 0

  a = digitalRead(FREQUENCY_SELECT_1);
  b = digitalRead(FREQUENCY_SELECT_2);
  c = digitalRead(FREQUENCY_SELECT_3);

  int binary = (a * 1) + (b * 2) + (c * 4);

  int frequency = 1;
  for (int i = 0; i < binary; i++) {
    frequency *= 2;
  }

  return frequency;

}
