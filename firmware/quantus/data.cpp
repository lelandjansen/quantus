// QUANTUS
// data.cpp

#include "data.hpp"

int      DATA_COUNT;
uint32_t START_TIME_INT;
double   START_TIME_DOUBLE;
uint32_t LAST_DATA_COLLECT;
uint32_t PERIOD;


// Take measurements (floating point)
measurement_float takeMeasurement_float() {

  measurement_float data;

  data.time         = (double)micros() * 1.e-6 - START_TIME_DOUBLE;
  data.pingTime     = measurePingTime_float();
  data.temperature  = measureTemperature_float();
  data.speedOfSound = computeSpeedOfSound(data.temperature);
  data.distance     = computeDistance_float(data.pingTime, data.speedOfSound);

  return data;

} // End of takeMeasurement_float





// Take measurements (fixed point)
measurement_fixed takeMeasurement_fixed() {

  measurement_fixed data;

  data.time         = micros() - START_TIME_INT;
  data.pingTime     = measurePingTime_fixed();
  data.temperature  = measureTemperature_fixed();
  data.speedOfSound = computeSpeedOfSoundLinearApproximation(data.temperature);
  data.distance     = computeDistance_fixed(data.pingTime, data.speedOfSound);

  return data;

} // End of takeMeasurement_fixed




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

  // // Measure temperature once but do not use reading
  // measureTemperature_float();
  // delay(100);

  // Take floating point measurements and convert to fixed point

  temperatureInitial       = measureTemperature_float();
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
void dataCollect_float() {



  if (micros() - LAST_DATA_COLLECT - 44e-6 >= PERIOD) {
  // Note: Measurement tends to take an extra 44 microseconds (hence -44e-6)

    ledWhite();

    LAST_DATA_COLLECT = micros();

    // Take measurements (floating point)
    measurement_float data = takeMeasurement_float();

    // Write measurement to data file on the SD card
    if (!logData_float(data)) {
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

} // End of dataCollect_float




// Collect data (fixed point)
void dataCollect_fixed() {



  if (micros() - LAST_DATA_COLLECT >= PERIOD - 44) {
  // Note: Measurement tends to take an extra 44 microseconds (hence -44)

    ledWhite();

    LAST_DATA_COLLECT = micros();

    // Take measurements (fixed point)
    measurement_fixed data = takeMeasurement_fixed();

    // Write measurement to data file on the SD card
    if (!logData_fixed(data)) {
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

} // End of dataCollect_fixed





// Finish data collection
void dataConclude() {

  // Attach new timer interrupt (pulse led colour)
  Timer1.attachInterrupt(led, 10000);

  nextDataFileName();

  NEXT_STATE = STATE_STANDBY;

} // End of dataConclude
