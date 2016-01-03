// QUANTUS
// globals.hpp

#ifndef __GLOBALS_HPP__
#define __GLOBALS_HPP__

#include <Arduino.h>

// Arduino digital pins
// Unused                     0
// Unused                     1
#define BUTTON                2
// SD_CD                      3 // (CD)
#define CHIP_SELECT           4 // (CS)                                     - INPUT
#define LED_RED               5 // Use 150-ohm resistor
#define LED_GREEN             6 // Use 100-ohm resistor (calculated 90 Ohms)
#define ULTRASONIC_TRIGGER    7
#define ULTRASONIC_ECHO       8
#define LED_BLUE              9 // Use 100-ohm resistor (calculated 90 Ohms)
// SD_RESERVED               10 // ()    Must remain unused
// MOSI                      11 // (DI)  Must remain unused                 - INPUT
// MISO                      12 // (DO)  Must remain unused                 - ???INPUT??? (0.17V)
// CLK                       13 // (SCK) Must remain unused



// Arduino analog pins
#define TEMPERATURE_PIN       0
// Unused                     1
// Unused                     2
// Unused                     3
// Unused                     4
// Unused                     5



// States
#define STATE_NO_SD           0
#define STATE_SD_SETUP        1
#define STATE_STANDBY         2
#define STATE_DATA_SETUP      3
#define STATE_DATA_COLLECT    4
#define STATE_DATA_CONCLUDE   5
#define STATE_WARNING         6
#define STATE_ERROR           7




extern volatile uint8_t STATE;
extern volatile uint8_t NEXT_STATE;



// Settings struct
typedef struct {
  bool    rawData;         // Set whether raw data should be included
  uint8_t countDown;       // Countdown to data collection (seconds)
  uint8_t frequency;       // Data collection frequency (Hertz)
  double  pressure;        // Atmospheric pressure (Pascales)
  double  humidity;        // Relative humidity (fraction)
  double  CO2MoleFraction; // Carbon dioxide mole fraction (fraction)
  bool    autoTemperature; // Determine whether
  double  temperature;     // temperature (degrees Celsius)
} systemSettings;

// Measurement struct
typedef struct {
  double time;
  double pingTime;
  double temperature;
  double speedOfSound;
  double distance;
} measurement;

// Measurement struct
// For use with fixed-point calculations
// Scale factor: 10^6
typedef struct {
  uint32_t time;
  uint32_t pingTime;
  uint32_t temperature;
  uint32_t speedOfSound;
  uint32_t distance;
} measurement_fp;



extern systemSettings SETTINGS;

// Default parameters
const systemSettings defaultSettings =  {
    true,     // rawData
    3,        // countDown
    10,       // frequency
    101325,   // pressure
    0.66,     // humidity
    3.14e-4,  // CO2MoleFraction
    true,     // autoTemperature
    20        // temperature
  };

// Lowest acceptable parameters
const systemSettings minimumSettings = {
    false,    // rawData
    0,        // countDown
    1,        // frequency
    75000,    // pressure
    0,        // humidity
    0,        // CO2MoleFraction
    false,    // autoTemperature
    0         // temperature
  };

// Highest acceptable parameters
const systemSettings maximumSettings = {
    true,     // rawData
    60,       // countDown
    20,       // frequency
    102000,   // pressure
    1,        // humidity             // CHECK!!! Formula rated up to 0.06 H20 mole fraction
    0.01,     // CO2MoleFraction
    true,     // autoTemperature
    30        // temperature
  };

#endif
