// QUANTUS
// globals.h

#ifndef ___GLOBALS_H_
#define ___GLOBALS_H_

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>



// Arduino Degital Pins

// Pin 0: Unused
// Pin 1: Unused
#define BUTTON                2
#define LED_RED               3
#define CHIP_SELECT           4
#define LED_GREEN             5
#define LED_BLUE              6
#define ULTRASONIC_TRIGGER    7
#define ULTRASONIC_ECHO       8
// Pin 9: Unused
#define SD_RESERVED          10
// #define MOSI                 11
// #define MISO                 12
// #define CLK                  13



/*
const int BUTTON              =  0;
const int LED_RED             =  1;
const int LED_GREEN           =  2;
const int LED_BLUE            =  3;
const int CHIP_SELECT         =  4;
const int ULTRASONIC_TRIGGER  =  5;
const int ULTRASONIC_ECHO     =  6;
const int FREQUENCY_SELECT_1  =  7;
const int FREQUENCY_SELECT_2  =  8;
const int FREQUENCY_SELECT_3  =  9;
const int SD_RESERVED         = 10; // Pin 10 must be unused (and set as an ouput) to use SD
// Pin 11: MOSI for SD
// Pin 12: MISO for SD
// Pin 13: CLK for SD
*/




// Arduino analog pins
#define TEMPERATURE_PIN      0
// Pin 1: Unused
// Pin 2: Unused
// Pin 3: Unused
// Pin 4: Unused
// Pin 5: Unused




// Default values

// Atmospheric pressure
const double defaultAtmosphericPressure = 101325; // Pascales
  // source: http://www.wolframalpha.com/input/?i=atm
  //         Accessed 2015-11-09
const double minimumAtmosphericPressure = 87000; // Pascales
  // source: http://www.aoml.noaa.gov/hrd/tcfaq/E1.html (Accessed 2015-11-09)
  //         Accessed 2015-11-09
const double maximumAtmosphericPressure = 108750; // Pascales
  // source: http://wmo.asu.edu/highest-sea-lvl-air-pressure-above-700m
  //         Accessed 2015-11-09

// humidity
const double defaultHumidity = 0.6619;
  // source: http://www.wolframalpha.com/input/?i=humidity
  //         Accessed 2015-11-09
const double minimumHumidity = 0;
const double maximumHumidity = 1;



#endif
