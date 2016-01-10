// QUANTUS
// led.hpp

#ifndef __LED_HPP__
#define __LED_HPP__

#include "globals.hpp"
#include "sd.hpp"

extern volatile uint8_t PULSE_COUNT;


// Formula: f(x) = (exp(sin(x))-1/e)(255/(e-1/e))
// f(0) to f(63)
const uint8_t PULSE_A[] = {  69,  71,  74,  77,  80,  83,  86,  89,  92,  95,  99,
      102, 105, 109, 112, 116, 119, 123, 127, 130, 134, 138, 142, 146, 150,
      153, 157, 161, 165, 169, 173, 177, 181, 184, 188, 192, 196, 199, 203,
      206, 210, 213, 216, 220, 223, 226, 229, 231, 234, 236, 239, 241, 243,
      245, 247, 248, 250, 251, 252, 253, 254, 254, 255, 255 };
// f(128) to f(191)
const uint8_t PULSE_B[] = {  67,  65,  62,  60,  57,  55,  53,  50,  48,  46,  44,
       42,  40,  38,  37,  35,  33,  32,  30,  28,  27,  26,  24,  23,  22,
       20,  19,  18,  17,  16,  15,  14,  13,  12,  11,  10,  10,   9,   8,
        8,   7,   6,   6,   5,   5,   4,   4,   3,   3,   3,   2,   2,   2,
        1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   0 };

void ledOff();
void ledWhite();
void ledRed();
void ledYellow();
void ledGreen();
void ledCyan();
void ledBlue();
void ledMagenta();
uint8_t pulse();
void ledCountdown();
void led();

#endif
