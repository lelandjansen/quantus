// QUANTUS
// temperature.cpp

#include "temperature.hpp"

// Measure ambient air temperature
// Hardware: Analog Devices TMP36
double measureTemperature() {

  double voltage, temperature;

  if (SETTINGS.autoTemperature) {
    // Get the voltage reading from the analog pin
    // Convert 0 to 1023 value returned by analogRead to voltage between 0 and 5
    voltage = analogRead(TEMPERATURE_PIN) * (3.3 / 1024.);

    // Convert voltage to degrees Celsius
    // Formula specified in TMP36 datasheet
    temperature = (voltage - 0.5) * 100.;
  }
  else {
    temperature = SETTINGS.temperature;
  }

  return temperature;

} // End of measureTemperature


// Measure ambient air temperature
// Fixed-point calculation
// Scale factor: 10^6
uint32_t measureTemperature_fp() {

  uint32_t voltage, temperature;

  if (SETTINGS.autoTemperature) {
    
    // Get the voltage reading from the analog pin
    // Convert 0 to 1023 value returned by analogRead to voltage between
    // 0 and 3.3e
    // (3.3/1024)e9 = 3,222,656.25 ~= 3222656
    voltage = (uint32_t)analogRead(TEMPERATURE_PIN) * 3222656;

    // Convert voltage to degrees Celsius
    // Formula specified in TMP36 datasheet
    temperature  = voltage - 500000000;
    temperature /= 10;

  }
  else {
    temperature = (uint32_t)((SETTINGS.temperature)*1e6);
  }

  return temperature;

} // End of measureTemperatureInt
