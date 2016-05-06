// QUANTUS
// led.hpp

#ifndef __LED_HPP__
#define __LED_HPP__


#include <math.h>
#include "globals.hpp"
#include "sd.hpp"


#define LED_ON  255
#define LED_OFF   0


extern volatile uint8_t PULSE_COUNT;

// The PULSE_A array represents the output values of the respiration equation
//  for the first half of the function's period. PULSE_B represents the Output
//  values of the second half of the function's period.
//
// Respiration equation:
// f(x) = (exp(sin(x))-1/e)(255/(e-1/e))
//
// First half of f(x) (i.e. f(0) to f(63))
// Common cathode
// const uint8_t PULSE_A[] = {  70,  72,  74,  78,  80,  84,  86,  90,  92,  96,  100,
//       102, 106, 110, 112, 116, 120, 124, 128, 130, 134, 138, 142, 146, 150,
//       154, 158, 162, 166, 170, 174, 178, 182, 184, 188, 192, 196, 200, 204,
//       206, 210, 214, 216, 220, 224, 226, 230, 232, 234, 236, 239, 242, 244,
//       246, 248, 248, 250, 252, 252, 254, 254, 254, 254, 254 };
// // Second half of f(x) (i.e. f(0) to f(63))
// const uint8_t PULSE_B[] = {  68,  66,  63,  60,  58,  56,  54,  50,  48,  46,  44,
//        42,  40,  38,  38,  36,  34,  32,  30,  28,  28,  26,  24,  24,  22,
//        20,  20,  18,  18,  16,  16,  14,  14,  12,  12,  10,  10,   10,   8,
//         8,   8,   6,   6,   6,   6,   4,   4,   4,   4,   4,   2,   2,   2,
//         2,   2,   2,   2,   0,   0,   0,   0,   0,   0,   0 };




const uint8_t PULSE_A[] = {  69,  71,  74,  77,  80,  83,  86,  89,  92,  95,  99,
      102, 105, 109, 112, 116, 119, 123, 127, 130, 134, 138, 142, 146, 150,
      153, 157, 161, 165, 169, 173, 177, 181, 184, 188, 192, 196, 199, 203,
      206, 210, 213, 216, 220, 223, 226, 229, 231, 234, 236, 239, 241, 243,
      245, 247, 248, 250, 251, 252, 253, 254, 254, 255, 255 };
// Second half of f(x) (i.e. f(0) to f(63))
const uint8_t PULSE_B[] = {  67,  65,  62,  60,  57,  55,  53,  50,  48,  46,  44,
       42,  40,  38,  37,  35,  33,  32,  30,  28,  27,  26,  24,  23,  22,
       20,  19,  18,  17,  16,  15,  14,  13,  12,  11,  10,  10,   9,   8,
        8,   7,   6,   6,   5,   5,   4,   4,   3,   3,   3,   2,   2,   2,
        1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   0 };

// Common anode
// const uint8_t PULSE_A[] = { 187, 184, 181, 179, 176, 173, 170, 167, 164, 160,
//   157, 154, 150, 147, 143, 140, 136, 133, 129, 125, 122, 118, 114, 110, 106,
//   102, 99, 95, 91, 87, 83, 79, 75, 72, 68, 64, 60, 57, 53, 50, 46, 43, 40, 36,
//   33, 30, 27, 25, 22, 20, 17, 15, 13, 11, 9, 8, 6, 5, 4, 3, 2, 1, 1, 1, 0 };
// const uint8_t PULSE_B[] = { 68, 65, 63, 60, 58, 56, 53, 51, 49, 47, 45, 43, 41,
//   39, 37, 35, 34, 32, 30, 29, 27, 26, 24, 23, 22, 21, 19, 18, 17, 16, 15, 14,
//   13, 12, 11, 10, 10, 9, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 2, 1, 1, 1, 0,
//   0, 0, 0, 0, 0, 0, 0, 0 };


void    ledOff();
void    ledWhite();
void    ledRed();
void    ledYellow();
void    ledGreen();
void    ledCyan();
void    ledBlue();
void    ledMagenta();
uint8_t pulse();
void    ledCountdown();
void    led();


#endif
