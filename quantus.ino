// QUANTUS
// quantus.cpp

#include "quantus.h"


void setup() {

  // Open serial communictions
  Serial.begin(9600);


  blueLED();

  // Set up Arduino pins
  pinSetup();

  // Initialize SD card
  sdSetup();


  uint32_t startTime;
  uint32_t pointTime;
  uint32_t computationDelay;
  uint32_t frequency         = getFrequency();
  uint32_t period            = 1.e6 / frequency;
  double   humidity          = getConstantsFromSD('H');
  double   pressure          = getConstantsFromSD('P');
  double   distance;
  double   temperature;
  double   pingTime;
  double   speedOfSound;

  Serial.println("Data file setup");
  dataFileSetup(frequency, humidity, pressure);
  Serial.println("Data file setup complete");


  // Loop indefinitely
  while (1) {
    // Make LED green to indicate standby
    cyanLED();


    while (!buttonPress()) {
      // Take no action
    }
    blueLED();
    delay(500);
    // When button has been pressed, count down for three seconds
    for (int i = 0; i < 3; i++) {
      greenLED();
      delay(100);
      blueLED();
      delay(800);
    }

    greenLED();

    startTime = micros();

    // While the button has not yet been pressed
    // Maximum number of data points in one session: 2048
    for (int i = 0; i < 2048; i++) {

      if (buttonPress()) {
        break;
      }

      pointTime    = micros();
      temperature  = measureTemperature();
      pingTime     = (double)measurePingTime(period);
      // If measurePingTime timed out
      if (!pingTime) {
        // Skip that measurement
        continue;
      }
      speedOfSound = calculateSpeedOfSound(temperature, humidity, pressure);
      distance     = calculateTargetDistance(pingTime, speedOfSound);

      if (distance >= 0.002 && distance <= 4.) {
        writeDataToFile(((double)(pointTime - startTime))/(1.e6), distance);
      }

      computationDelay = period - (micros() - pointTime);
      if (computationDelay > period) {
        computationDelay = 0;
      }

      delayMicroseconds(computationDelay);


    }

    blueLED();
    delay(1000);

  } // End of while (will never end)



} // End of setup






void loop() {




} // End of loop

// That's all folks!
