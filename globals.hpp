// QUANTUS
// globals.hpp

#ifndef __GLOBALS_HPP__
#define __GLOBALS_HPP__


#include <Arduino.h>
#include <TimerOne.h> // http://playground.arduino.cc/Code/Timer1


// Arduino digital pins
// Unused                     0
// Unused                     1
#define BUTTON                2
#define CARD_DETECT           3 // (CD)
#define CHIP_SELECT           4 // (CS)
#define LED_RED               5 // Use 150-ohm resistor
#define LED_GREEN             6 // Use 100-ohm resistor (calculated 90 Ohms)
#define ULTRASONIC_TRIGGER    7
#define ULTRASONIC_ECHO       8
#define LED_BLUE              9 // Use 100-ohm resistor (calculated 90 Ohms)
//      SD_RESERVED          10 // Must remain unused
//      MOSI                 11 // (DI)
//      MISO                 12 // (DO)
//      CLK                  13 // (SCK)


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

// State variables
extern volatile uint8_t STATE;
extern volatile uint8_t NEXT_STATE;
extern          bool    ERROR_ENCOUNTERED;



// Structs

// Settings struct
typedef struct {
  bool     rawData;         // Set whether raw data should be included
  uint8_t  countdown;       // Countdown to data collection (seconds)
  uint8_t  frequency;       // Data collection frequency (Hertz)
  double   pressure;        // Atmospheric pressure (Pascales)
  double   humidity;        // Relative humidity (fraction)
  double   CO2MoleFraction; // Carbon dioxide mole fraction (fraction)
  bool     autoTemperature; // Determine whether
  double   temperature;     // temperature (degrees Celsius)
  uint16_t maximumData;     // Maximum amount of data that can be collected
} systemSettings;

// Measurement struct
typedef struct {
  double time;
  double pingTime;
  double temperature;
  double speedOfSound;
  double distance;
} measurement_float;

// Measurement struct
// For use with fixed-point calculations
// Scale factor: 10^6
typedef struct {
  uint32_t time;
  uint32_t pingTime;
  uint32_t temperature;
  uint32_t speedOfSound;
  uint32_t distance;
} measurement_fixed;




// Settings
extern systemSettings SETTINGS;

// Default parameters
const systemSettings SETTINGS_DEFAULT =  {
  false,    // rawData
  3,        // countDown
  10,       // frequency
  101325,   // pressure
  0.66,     // humidity
  3.14e-4,  // CO2MoleFraction
  true,     // autoTemperature
  20,       // temperature
  1000      // maximumData
};

// Lowest acceptable parameters
const systemSettings SETTINGS_MINIMUM = {
  false,    // rawData
  0,        // countDown
  1,        // frequency
  75000,    // pressure
  0,        // humidity
  0,        // CO2MoleFraction
  false,    // autoTemperature
  0,        // temperature
  1         // maximumData
};

// Highest acceptable parameters
const systemSettings SETTINGS_MAXIMUM = {
  true,     // rawData
  60,       // countDown
  20,       // frequency
  102000,   // pressure
  1,        // humidity             // CHECK!!! Formula rated up to 0.06 H20 mole fraction
  0.01,     // CO2MoleFraction
  true,     // autoTemperature
  30,       // temperature
  65535     // maximumData (maximum uint16_t value)
};


#endif
