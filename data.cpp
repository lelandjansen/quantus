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





// Take measurements
// Fixed-point calculation
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

  PERIOD = 1000000 / (uint32_t)SETTINGS.frequency;


  // Compute initial temperature and speed of sound, and derivate values
  // Convert to fixed-point

  // Measure temperature once but do not use reading
  measureTemperature();
  delay(100);

  temperatureInitial       = measureTemperature();
  TEMPERATURE_INITIAL      = (uint32_t)(temperatureInitial * 1e6);

  speedOfSoundInitial      = computeSpeedOfSound(temperatureInitial);
  SPEED_OF_SOUND_INITIAL   = (uint32_t)(speedOfSoundInitial * 1e6);

  d_speedOfSoundInitial    = computeSpeedOfSoundDerivative(temperatureInitial);
  D_SPEED_OF_SOUND_INITIAL = (uint32_t)(d_speedOfSoundInitial * 1e4);

  // Serial.print(F("temperatureInitial       "));
  // Serial.println(temperatureInitial, 6);
  // Serial.print(F("TEMPERATURE_INITIAL      "));
  // Serial.println(TEMPERATURE_INITIAL);
  // Serial.print(F("speedOfSoundInitial      "));
  // Serial.println(speedOfSoundInitial, 6);
  // Serial.print(F("SPEED_OF_SOUND_INITIAL   "));
  // Serial.println(SPEED_OF_SOUND_INITIAL);
  // Serial.print(F("d_speedOfSoundInitial    "));
  // Serial.println(d_speedOfSoundInitial, 6);
  // Serial.print(F("D_SPEED_OF_SOUND_INITIAL "));
  // Serial.println(D_SPEED_OF_SOUND_INITIAL);
  // Serial.println();


  // Blink countdown
  uint32_t countDownStart;
  countDownStart = millis();
  while (sdInserted() && millis() - countDownStart < 250) {
    ledYellow();
  }
  countDownStart = millis();
  ledGreen();
  while (sdInserted() && millis() - countDownStart < 1000 * SETTINGS.countDown) {
    if ((millis() - countDownStart)%1000 > 149) {
      ledYellow();
    }
    else { //if ((millis() - countDownStart)%150 == 0) {
      ledGreen();
    }
  }

  while(1) {
    ledBlue();
  }

  // Blink countdown
  for (int i = 0; i <= SETTINGS.countDown; i++) {
    if (!sdInserted()) break;
    ledYellow();
    if (i == 0) delay(250);
    else delay (850);
    ledGreen();
    if (i != SETTINGS.countDown) delay(150);
  }

  // Set START_TIME to current time
  LAST_DATA_COLLECT = 0;
  START_TIME_INT    = micros();
  START_TIME_DOUBLE = (double)START_TIME_INT * 1.e-6;

} // End of dataSetup





// Collect data
void dataCollect() {

  if (micros() - LAST_DATA_COLLECT - 44e-6 >= PERIOD) {


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




// Collect data
// Fixed-point calculations
void dataCollect_fp() {

  Serial.println(F("0"));

  // Measurement tends to take an extra 44 microseconds (hence -44)
  if (micros() - LAST_DATA_COLLECT >= PERIOD - 44) {

    Serial.println(F("1"));

    ledWhite();

    Serial.println(F("2"));


    LAST_DATA_COLLECT = micros();

    Serial.println(F("3"));


    // Take measurement
    measurement_fp data_fp = takeMeasurement_fp();

    Serial.println(F("4"));

    // Log measurement to sd card
    if (!logData_fp(data_fp)) {
      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      // ERROR: Cannot write file to SD card
      Serial.println(F("Error logging data"));
      NEXT_STATE = STATE_ERROR;
      return;
    }


    Serial.println(F("5"));

    DATA_COUNT++;
    if (DATA_COUNT >= 1000) {
      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      // WARNING: Cannot collect more than 1000 data points
      NEXT_STATE = STATE_WARNING;
      return;
    }


    Serial.println(F("6"));

    ledGreen();


    Serial.println(F("7"));

  }

} // End of dataCollect_fp





// Finish data collection
void dataConclude() {

  // closeDataFile();

  // Attach new timer interrupt (change led colour)
  Timer1.attachInterrupt(led, 10000);

  // Increment file name
  nextDataFileName();

  NEXT_STATE = STATE_STANDBY;

} // End of dataConclude
