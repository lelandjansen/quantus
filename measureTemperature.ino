/*
  Quantus
  measureTemperature.ino
  Copyright (c) Leland Jansen 2015. All rights reserved.
*/


// Measure ambient air temperature
// Hardware: Analog Devices TMP36
// Returns the air temperature in degrees Celsius
double measureTemperature() {

  // Global variable: temperaturePin (the analog pin to which the temperature sensor is connected)

  double voltage, temperature;

  // Get the voltage reading from the analog pin
  // Convert 0 to 2023 value returned by analogRead to voltage between 0 and 5
  voltage = analogRead(temperaturePin) * (5. / 1024.);

  // Convert voltage to degrees Celsius
  // Formula specified in TMP36 datasheet
  temperature = (voltage - 0.5) * 100.;

  /*
  Serial.print("temperature: \t");
  Serial.print(temperature, 4);
  Serial.println(" C");
  */

  return temperature;
  
}




/*
Implement this code if I choose to use digital temperature sensor

#include <OneWire.h>
#include <DallasTemperature.h>

// Measure ambient air temperature
// Hardware: Maxim Integrated (formerly Dallas) DS18B20
// Accepts one parameter: temperaturePin (the digital pin to which the temperature sensor is connected)
// Returns the air temperature in degrees Celsius
double measureTemperature(int temperaturePin) {

  // Code for this sensor goes here
}
*/
