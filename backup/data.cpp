// QUANTUS
// data.cpp

#include "data.hpp"

int      DATA_COUNT;
uint32_t START_TIME_INT;
double   START_TIME_DOUBLE;
uint32_t LAST_DATA_COLLECT;
uint32_t PERIOD;


// Take measurements (floating point)
measurement takeMeasurement() {

  measurement data;

  data.time         = (double)micros() * 1.e-6 - START_TIME_DOUBLE;
  data.pingTime     = measurePingTime();
  data.temperature  = measureTemperature();
  data.speedOfSound = computeSpeedOfSound(data.temperature);
  data.distance     = computeDistance(data.pingTime, data.speedOfSound);

  return data;

} // End of takeMeasurement





// Take measurements (fixed point)
measurement_fp takeMeasurement_fp() {

  measurement_fp data_fp;

  data_fp.time         = micros() - START_TIME_INT;
  data_fp.pingTime     = measurePingTime_fp();
  data_fp.temperature  = measureTemperature_fp();
  data_fp.speedOfSound = computeSpeedOfSoundLinearApproximation_fp(data_fp.temperature);
  data_fp.distance     = computeDistance_fp(data_fp.pingTime, data_fp.speedOfSound);

  return data_fp;

} // End of takeMeasurement




// Setup code for data collection
void dataSetup() {

  double temperatureInitial, speedOfSoundInitial, d_speedOfSoundInitial;

  // Detach old timer interrupt
  Timer1.detachInterrupt();

  ledYellow();

  DATA_COUNT = 0;

  // Create data file
  if (!dataFileHeader()) {
    NEXT_STATE = STATE_ERROR;
    return;
  }

  // Compute the data collection period
  PERIOD = 1000000 / (uint32_t)SETTINGS.frequency;


  // Compute initial temperature and speed of sound, and derivate values
  // Convert to fixed-point

  // Measure temperature once but do not use reading
  measureTemperature();
  delay(100);

  // Take floating point measurements and convert to fixed point

  temperatureInitial       = measureTemperature();
  TEMPERATURE_INITIAL      = (uint32_t)(temperatureInitial * 1e6);

  speedOfSoundInitial      = computeSpeedOfSound(temperatureInitial);
  SPEED_OF_SOUND_INITIAL   = (uint32_t)(speedOfSoundInitial * 1e6);

  d_speedOfSoundInitial    = computeSpeedOfSoundDerivative(temperatureInitial);
  D_SPEED_OF_SOUND_INITIAL = (uint32_t)(d_speedOfSoundInitial * 1e4);


  // Countdown to data collection
  ledCountdown();


  if (NEXT_STATE == STATE_NO_SD) return;
  else if (NEXT_STATE == STATE_DATA_CONCLUDE) {
    if (!removeCurrentDataFile()) NEXT_STATE = STATE_ERROR;
    return;
  }


  NEXT_STATE = STATE_DATA_COLLECT;


  LAST_DATA_COLLECT = 0;
  START_TIME_INT    = micros();
  START_TIME_DOUBLE = (double)START_TIME_INT * 1.e-6;

} // End of dataSetup





// Collect data (floating point)
void dataCollect() {



  if (micros() - LAST_DATA_COLLECT - 44e-6 >= PERIOD) {
  // Note: Measurement tends to take an extra 44 microseconds (hence -44e-6)

    ledWhite();

    LAST_DATA_COLLECT = micros();

    // Take measurements (floating point)
    measurement data = takeMeasurement();

    // Write measurement to data file on the SD card
    if (!logData(data)) {
      NEXT_STATE = STATE_ERROR;
      return;
    }

    DATA_COUNT++;


    if (DATA_COUNT >= SETTINGS.maximumData) {
      NEXT_STATE = STATE_WARNING;
      // Write the warning to the log file
      if (!printMaximumDataError()) NEXT_STATE = STATE_ERROR;
      return;
    }

    // Turn the LED green to symbolize that we are in the data collection state
    //  however data is not being collected
    ledGreen();

  } // End of if

} // End of dataCollect




// Collect data (fixed point)
void dataCollect_fp() {



  if (micros() - LAST_DATA_COLLECT >= PERIOD - 44) {
  // Note: Measurement tends to take an extra 44 microseconds (hence -44)

    ledWhite();

    LAST_DATA_COLLECT = micros();

    // Take measurements (fixed point)
    measurement_fp data_fp = takeMeasurement_fp();

    // Write measurement to data file on the SD card
    if (!logData_fp(data_fp)) {
      NEXT_STATE = STATE_ERROR;
      return;
    }

    DATA_COUNT++;

    if (DATA_COUNT >= SETTINGS.maximumData) {
      NEXT_STATE = STATE_WARNING;
      // Write the warning to the log file
      if (!printMaximumDataError()) NEXT_STATE = STATE_NO_SD;
      return;
    }

    // Turn the LED green to symbolize that we are in the data collection state
    //  however data is not being collected
    ledGreen();

  } // End of if

} // End of dataCollect_fp





// Finish data collection
void dataConclude() {

  // Attach new timer interrupt (pulse led colour)
  Timer1.attachInterrupt(led, 10000);

  nextDataFileName();

  NEXT_STATE = STATE_STANDBY;

} // End of dataConclude
