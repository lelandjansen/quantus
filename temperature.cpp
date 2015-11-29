// QUANTUS
// temperature.cpp

#include "temperature.h"

// !!! Replace 5V with measured voltage


// Measure ambient air temperature
// Hardware: Analog Devices TMP36
// Returns the air temperature in degrees Celsius
double measureTemperature() {

  double voltage, temperature;

  // Get the voltage reading from the analog pin
  // Convert 0 to 2023 value returned by analogRead to voltage between 0 and 5
  voltage = analogRead(TEMPERATURE_PIN) * (5. / 1024.);

  // Convert voltage to degrees Celsius
  // Formula specified in TMP36 datasheet
  temperature = (voltage - 0.5) * 100.;

  return temperature;

}
