// QUANTUS
// data.cpp

#include "data.hpp"

int      DATA_COUNT;
uint32_t START_TIME_INT;
double   START_TIME_DOUBLE;
uint32_t LAST_DATA_COLLECT;
uint32_t PERIOD;

// Take measurements
measurement takeMeasurement() {

  measurement data;

  data.time         = (double)micros() * 1.e-6 - START_TIME_DOUBLE;
  data.pingTime     = measurePingTime();
  data.temperature  = measureTemperature();
  data.speedOfSound = computeSpeedOfSound(data.temperature);
  data.distance     = computeDistance(data.pingTime, data.speedOfSound);

  return data;

} // End of takeMeasurement



void dataSetup() {

  // Detach old timer interrupt
  Timer1.detachInterrupt();

  ledYellow();

  // SET DATA_COUNT to zero
  DATA_COUNT = 0;

  // if(!openDataFile()) {
  //   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //   // ERROR: Could not open data file
  //   NEXT_STATE = STATE_ERROR;
  //   return;
  // }

  // Create data file
  if (dataFileHeader()) {
    NEXT_STATE = STATE_DATA_COLLECT;
  }
  else {
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // ERROR: Could not create data file
    NEXT_STATE = STATE_ERROR;
    return;
  }

  PERIOD = 1e6 / (uint32_t)settings.frequency;

  // Blink countdown
  for (int i = 0; i <= settings.countDown; i++) {
    ledYellow();
    if (i == 0) delay(300);
    else delay (850);
    ledGreen();
    if (i != settings.countDown) delay(150);
  }

  // Set START_TIME to current time
  LAST_DATA_COLLECT = 0;
  START_TIME_INT    = micros();
  START_TIME_DOUBLE = (double)START_TIME_INT * 1.e-6;

} // End of dataSetup





void dataCollect() {

  if (micros() - LAST_DATA_COLLECT >= PERIOD) {


    ledWhite();


    LAST_DATA_COLLECT = micros();



    // Take measurement
    measurement data = takeMeasurement();

    // Log measurement to sd card
    if (!logData(data)) {
      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      // ERROR: Cannot write file to SD card
      NEXT_STATE = STATE_ERROR;
      return;
    }

    DATA_COUNT++;
    if (DATA_COUNT >= 1000) {
      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      // WARNING: Cannot collect more than 1000 data points
      NEXT_STATE = STATE_WARNING;
      return;
    }

    ledGreen();

  }

} // End of dataCollect





void dataConclude() {

  // closeDataFile();

  // Attach new timer interrupt (change led colour)
  Timer1.attachInterrupt(led, 10000);

  // Increment file name
  nextDataFileName();

  NEXT_STATE = STATE_STANDBY;


} // End of dataConclude
