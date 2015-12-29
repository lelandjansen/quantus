// QUANTUS
// led.hpp

#ifndef __LED_HPP__
#define __LED_HPP__

#include "globals.hpp"

extern volatile uint8_t PULSE_COUNT;

void ledOff();
void ledWhite();
void ledRed();
void ledYellow();
void ledGreen();
void ledCyan();
void ledBlue();
void ledMagenta();
uint8_t pulse();
void led();

#endif
