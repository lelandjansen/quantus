// QUANTUS
// temperature.cpp

#include "temperature.hpp"

// Measure ambient air temperature
// Hardware: Analog Devices TMP36
double measureTemperature() {

  double voltage, temperature;

  if (settings.autoTemperature) {
    // Get the voltage reading from the analog pin
    // Convert 0 to 2023 value returned by analogRead to voltage between 0 and 5
    voltage = analogRead(TEMPERATURE) * (5. / 1024.);

    // Convert voltage to degrees Celsius
    // Formula specified in TMP36 datasheet
    temperature = (voltage - 0.5) * 100.;
  }
  else {
    temperature = settings.temperature;
  }

  return temperature;

} // End of measureTemperature
