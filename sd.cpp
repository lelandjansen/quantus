// QUANTUS
// sd.cpp

#include "sd.hpp"
SdFat SD;


int DATA_FILE_NUMBER;
File dataFile;
File settingsFile;
File logFile;
char dataFileName[14];
const char settingsFileName[] = "qSettings.json";
const char logFileName[] = "qLog.txt";



bool sdInserted() {
  if (digitalRead(CARD_DETECT) == HIGH) {
    return true;
  }
  else if (digitalRead(CARD_DETECT) == LOW) {
    return false;
  }
}


void sdChange() {
  if (sdInserted()) {
    // SD Card is inserted
    Serial.println(F("Inserted"));
    NEXT_STATE = STATE_SD_SETUP;
  }
  else {
    // SD Card is removed

    // Attach new timer interrupt (change led colour)
    Timer1.attachInterrupt(led, 10000);

    NEXT_STATE = STATE_NO_SD;
    Serial.println(F("Removed"));
  }
} // End of SDInserted



// State while no SD card is inserted
void noSD() {

  // No SD card is inserted

} // End of noSD





// Log errors in settings FILE_WRITE
bool logSettingsFileError(bool setToDefault, int variableIndex) {

  // Print logFile underscores if an error has not already been encountered
  if (!ERROR_ENCOUNTERED && !printUnderscoresToLogFile()) return false;

  // Set next state to warning
  NEXT_STATE = STATE_WARNING;

  char* variableName[] = {
    "rawData",
    "countdown",
    "frequency",
    "pressure",
    "humidity",
    "CO2MoleFraction",
    "autoTemperature",
    "temperature",
    "maximumData"
  };

  logFile = SD.open(logFileName, FILE_WRITE);
  if (logFile) {
    logFile.print(F("Warning: Cannot not parse \""));
    logFile.print(variableName[variableIndex]);
    logFile.print(F("\" or value out of range in \""));
    logFile.print(settingsFileName);
    logFile.print(F("\" file."));
    if (setToDefault) {
      logFile.println(F(" Assigning default value."));
    }
    else {
      logFile.println(F(" Errors might occur."));
    }
  }
  else return false;

  logFile.close();

  return true;

} // End of logSettingsFileError





bool printUnderscoresToLogFile() {
  logFile = SD.open(logFileName, FILE_WRITE);
  if (logFile) {
    // Print line of underscores
    logFile.println();
    for (int i = 0; i < 7; i++) {
      logFile.print(F("_"));
    }
    logFile.println();
    logFile.close();
  }
  else return false;
  return true;
} // End of printUnderscoresToLogFile





bool printMaximumDataError() {

  // Print logFile underscores if an error has not already been encountered
  if (!ERROR_ENCOUNTERED && !printUnderscoresToLogFile()) return false;

  logFile = SD.open(logFileName);
  if (logFile) {
    logFile.print(F("Warning: Cannot collect more than "));
    logFile.print(SETTINGS.maximumData);
    logFile.println(F(" data measurements."));
    logFile.close();
  }
  else return false;

} // End of printMaximumDataError






bool errorLogSetup() {

  // If log file does not exist, create it
  if (!SD.exists(logFileName)) {
    logFile = SD.open(logFileName, FILE_WRITE);
    if (logFile) {
      logFile.println(F("Quantus: Error/warning log"));
      logFile.close();
    }
    else return false;
  }
  return true;

} // End of errorLogSetup





bool getSettingsFromFile() {

  const int bufferSize = 200;
  char dataStringBuffer[bufferSize];

  // If the settings file exists
  if (SD.exists(settingsFileName)) {
    settingsFile = SD.open(settingsFileName, FILE_READ);
    if (settingsFile) {
      // Read file contents to buffer
      int i = 0;
      while (settingsFile.available()) {
        if (i == bufferSize) break;
        dataStringBuffer[i] = settingsFile.read();
        i++;
      }
    }


    // Parse JSON data
    // Note to self: Update buffer size in <> when updating string buffer size
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(dataStringBuffer);

    SETTINGS.rawData         = root["rawData"];
    SETTINGS.countdown       = root["countdown"];
    SETTINGS.frequency       = root["frequency"];
    SETTINGS.pressure        = root["pressure"];
    SETTINGS.humidity        = root["humidity"];
    SETTINGS.CO2MoleFraction = root["CO2MoleFraction"];
    SETTINGS.autoTemperature = root["autoTemperature"];
    SETTINGS.temperature     = root["temperature"];
    SETTINGS.maximumData     = root["maximumData"];


    // Verify data is within constraints

    // rawData (0)
    if (SETTINGS.rawData != true && SETTINGS.rawData != false) {
      // Set rawData to default value
      SETTINGS.rawData = SETTINGS_DEFAULT.rawData;
      // Log warning (cannot parse or out of range)
      if (!logSettingsFileError(1, 0)) return false;
    }

    // countdown (1)
    if (SETTINGS.countdown == NULL) {
      // Set countdown to default value
      SETTINGS.countdown = SETTINGS_DEFAULT.countdown;
      // Log warning (cannot parse or out of range)
      if (!logSettingsFileError(1, 1)) return false;
    }
    else if (SETTINGS.countdown < SETTINGS_MINIMUM.countdown || SETTINGS.countdown > SETTINGS_MAXIMUM.countdown) {
      // Log warning (out of range)
      if (!logSettingsFileError(0, 1)) return false;
    }

    // frequency (2)
    if (SETTINGS.frequency == NULL || SETTINGS.frequency < SETTINGS_MINIMUM.frequency || SETTINGS.frequency > SETTINGS_MAXIMUM.frequency) {
      // Set frequency to default value
      SETTINGS.frequency = SETTINGS_DEFAULT.frequency;
      // Log warning (cannot parse or out of range)
      if (!logSettingsFileError(1, 2)) return false;
    }

    // pressure (3)
    if (SETTINGS.pressure == NULL) {
      // Set pressure to default value
      SETTINGS.pressure = SETTINGS_DEFAULT.pressure;
      // Log warning (cannot parse or out of range)
      if (!logSettingsFileError(1, 3)) return false;
    }
    else if (SETTINGS.pressure < SETTINGS_MINIMUM.pressure || SETTINGS.pressure > SETTINGS_MAXIMUM.pressure) {
      // Log warning (out of range)
      if (!logSettingsFileError(0, 3)) return false;
    }

    // humidity (4)
    if (SETTINGS.humidity == NULL) {
      // Set humidity to default value
      SETTINGS.humidity = SETTINGS_DEFAULT.humidity;
      // Log warning (cannot parse or out of range)
      if (!logSettingsFileError(1, 4)) return false;
    }
    else if (SETTINGS.humidity < SETTINGS_MINIMUM.humidity || SETTINGS.humidity > SETTINGS_MAXIMUM.humidity) {
      // Log warning (out of range)
      if (!logSettingsFileError(0, 4)) return false;
    }

    // CO2MoleFraction (5)
    if (SETTINGS.CO2MoleFraction == NULL) {
      // Set CO2MoleFraction to default value
      SETTINGS.CO2MoleFraction = SETTINGS_DEFAULT.CO2MoleFraction;
      // Log warning (cannot parse or out of range)
      if (!logSettingsFileError(1, 5)) return false;
    }
    else if (SETTINGS.CO2MoleFraction < SETTINGS_MINIMUM.CO2MoleFraction || SETTINGS.CO2MoleFraction > SETTINGS_MAXIMUM.CO2MoleFraction) {
      // Log warning (out of range)
      if (!logSettingsFileError(0, 5)) return false;
    }

    // autoTemperature (6)
    if (SETTINGS.autoTemperature == NULL || (SETTINGS.autoTemperature != false && SETTINGS.autoTemperature != true)) {
      // Set autoTemperature to default value
      SETTINGS.autoTemperature = SETTINGS_DEFAULT.autoTemperature;
      // Log warning (cannot parse or out of range)
      if (!logSettingsFileError(1, 6)) return false;
    }

    // temperature (7)
    if (!SETTINGS.autoTemperature) {
      if (SETTINGS.temperature == NULL) {
        // Set CO2MoleFraction to default value
        SETTINGS.temperature = SETTINGS_DEFAULT.temperature;
        // Log warning (cannot parse or out of range)
        if (!logSettingsFileError(1, 7)) return false;
      }
      else if (SETTINGS.temperature < SETTINGS_MINIMUM.temperature || SETTINGS.temperature > SETTINGS_MAXIMUM.temperature) {
        // Log warning (out of range)
        if (!logSettingsFileError(0, 7)) return false;
      }
    }

    // maximumData (8)
    if (SETTINGS.maximumData == NULL || SETTINGS.maximumData < SETTINGS_MINIMUM.maximumData || SETTINGS.maximumData > SETTINGS_MAXIMUM.maximumData) {
      // Set maximumData to default value
      SETTINGS.maximumData = SETTINGS_DEFAULT.maximumData;
      // Log warning (cannot parse or out of range)
      if (!logSettingsFileError(1, 8)) return false;
    }

  }
  // If the settings file does not exist
  else {

    // Print logFile underscores if an error has not already been encountered
    if (!ERROR_ENCOUNTERED && !printUnderscoresToLogFile()) return false;

    logFile = SD.open(logFileName, FILE_WRITE);
    if (logFile) {
      NEXT_STATE = STATE_WARNING;
      logFile.print(F("Warning: Cannot find file \""));
      logFile.print(settingsFileName);
      logFile.println(F("\". New settings file created containing default values."));
      logFile.close();
    }
    else return false;



    settingsFile = SD.open(settingsFileName, FILE_WRITE);
    if (settingsFile) {

      // Set SETTINGS to default
      SETTINGS = SETTINGS_DEFAULT;

      // Print JSON file with default values to settings file
      settingsFile.print(F("{"));
        settingsFile.print(F("\"rawData\":"));
          if (SETTINGS_DEFAULT.rawData) settingsFile.print(F("true"));
          else settingsFile.print(F("false"));
          settingsFile.print(F(","));
        settingsFile.print(F("\"countdown\":"));
          settingsFile.print(SETTINGS_DEFAULT.countdown);
          settingsFile.print(F(","));
        settingsFile.print(F("\"frequency\":"));
          settingsFile.print(SETTINGS_DEFAULT.frequency);
          settingsFile.print(F(","));
        settingsFile.print(F("\"pressure\":"));
          settingsFile.print(SETTINGS_DEFAULT.pressure, 4);
          settingsFile.print(F(","));
        settingsFile.print(F("\"humidity\":"));
          settingsFile.print(SETTINGS_DEFAULT.humidity, 4);
          settingsFile.print(F(","));
        settingsFile.print(F("\"CO2MoleFraction\":"));
          settingsFile.print(SETTINGS_DEFAULT.CO2MoleFraction*1e4, 4);
          settingsFile.print(F("E-4"));
          settingsFile.print(F(","));
        settingsFile.print(F("\"autoTemperature\":"));
          if (SETTINGS_DEFAULT.autoTemperature) settingsFile.print(F("true"));
          else settingsFile.print(F("false"));
          settingsFile.print(F(","));
        settingsFile.print(F("\"temperature\":"));
          settingsFile.print(SETTINGS_DEFAULT.temperature, 4);
          settingsFile.print(F(","));
        settingsFile.print(F("\"maximumData\":"));
          settingsFile.print(SETTINGS_DEFAULT.maximumData);
      settingsFile.print(F("}"));

      settingsFile.close();

    }
    else return false;
  }

  return true;

} // End of getSettingsFromFile





void nextDataFileName() {
  DATA_FILE_NUMBER++;
  sprintf(dataFileName, "qData_%03i.csv", DATA_FILE_NUMBER);
} // End of nextDataFileName

void previousDataFileName() {
  DATA_FILE_NUMBER--;
  sprintf(dataFileName, "qData_%03i.csv", DATA_FILE_NUMBER);
} // End of nextDataFileName




void determineDataFileNumber() {

  // Determine the number of the next data file
  for (DATA_FILE_NUMBER = 999; DATA_FILE_NUMBER >= 0; DATA_FILE_NUMBER--) {
    if (NEXT_STATE == STATE_NO_SD) break;
    sprintf(dataFileName, "qData_%03i.csv", DATA_FILE_NUMBER);
    if (SD.exists(dataFileName) || DATA_FILE_NUMBER == 0) {
      nextDataFileName();
      break;
    }
  }

} // End of determineDataFileNumber





void sdSetup() {

  // Try to initialize SD card
  // If the SD card cannot be initialized, go to no SD state
  if (!SD.begin(CHIP_SELECT)) {
    NEXT_STATE = STATE_NO_SD;
    return;
  }


  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // Check available space on SD card
    // If SD card is almost full
      // Warning: SD card almost full
    // If SD card is full
      // Error: SD card is full



  // Set up error log file
  if (!errorLogSetup()) {
    // Cannot create error log file
    NEXT_STATE = STATE_ERROR;
    return;
  }


  // Get settings from file
  if (!getSettingsFromFile()) {
    // Cannot get settings from file
    NEXT_STATE = STATE_ERROR;
    return;
  }


  // Determine data file number
  determineDataFileNumber();

  // If data file number is between 990 and 998
  // Warn that 10 or less data files can be created
  if (DATA_FILE_NUMBER > 989) {

    // Print logFile underscores if an error has not already been encountered
    if (!ERROR_ENCOUNTERED && !printUnderscoresToLogFile()) {
      NEXT_STATE = STATE_NO_SD;
      return;
    }

    logFile = SD.open(logFileName, FILE_WRITE);
    if (logFile) {

      if (DATA_FILE_NUMBER <= 998) {
        NEXT_STATE = STATE_WARNING;
        logFile.print(F("Warning: Only "));
        logFile.print(1000-DATA_FILE_NUMBER);
        logFile.print(F(" more data files can be created."));
      }
      else if (DATA_FILE_NUMBER == 999) {
        NEXT_STATE = STATE_WARNING;
        logFile.print(F("Warning: Only 1 more data file can be created."));
      }
      else if (DATA_FILE_NUMBER >= 1000) {
        NEXT_STATE = STATE_ERROR;
        logFile.print(F("Error: No more data files can be created."));
      }
      logFile.println(F(" Please remove data files from the SD card."));

    }
    else {
      NEXT_STATE = STATE_ERROR;
      return;
    }

    logFile.close();

  }

  if (NEXT_STATE != STATE_WARNING && NEXT_STATE != STATE_ERROR) {
    // Go to standby state
    NEXT_STATE = STATE_STANDBY;
  }


} // End of sdSetup




bool dataFileHeader() {

  dataFile = SD.open(dataFileName, FILE_WRITE);

  if (dataFile) {

    dataFile.print(F("QUANTUS,Distance-time measurements"));
    if (SETTINGS.rawData) dataFile.println(F(",,,"));
    else dataFile.println();

    dataFile.print(F("Raw data export,"));
    if (SETTINGS.rawData) dataFile.print(F("true"));
    else dataFile.print(F("false"));
    if (SETTINGS.rawData) dataFile.println(F(",,,"));
    else dataFile.println();

    dataFile.print(F("Count down (seconds),"));
    dataFile.print(SETTINGS.countdown);
    if (SETTINGS.rawData) dataFile.println(F(",,,"));
    else dataFile.println();

    dataFile.print(F("Frequency (Hz),"));
    dataFile.print(SETTINGS.frequency);
    if (SETTINGS.rawData) dataFile.println(F(",,,"));
    else dataFile.println();

    dataFile.print(F("Pressure (Pa),"));
    dataFile.print(SETTINGS.pressure, 2);
    if (SETTINGS.rawData) dataFile.println(F(",,,"));
    else dataFile.println();

    dataFile.print(F("Relative humidity (fraction),"));
    dataFile.print(SETTINGS.humidity, 4);
    if (SETTINGS.rawData) dataFile.println(F(",,,"));
    else dataFile.println();

    dataFile.print(F("Carbon dioxide mole fraction (fraction),"));
    dataFile.print(SETTINGS.CO2MoleFraction, 6);
    if (SETTINGS.rawData) dataFile.println(F(",,,"));
    else dataFile.println();

    dataFile.print(F("Temperature (C),"));
    if (SETTINGS.autoTemperature) dataFile.print(F("auto"));
    else dataFile.print(SETTINGS.temperature, 2);
    if (SETTINGS.rawData) dataFile.println(F(",,,"));
    else dataFile.println();

    dataFile.print(F("Maximum amount of data,"));
    dataFile.print(SETTINGS.maximumData);
    if (SETTINGS.rawData) dataFile.println(F(",,,"));
    else dataFile.println();


    if (SETTINGS.rawData) dataFile.println(F(",,,,"));
    else dataFile.println(F(","));

    if (SETTINGS.rawData) dataFile.println(F("time (s),ping time (s),temperature (C),computed speed of sound (m/s),computed distance (m)"));
    else dataFile.println(F("time (s),distance (m)"));

    dataFile.close();

  }
  else return false;

  return true;
}





bool logData(measurement data) {

  dataFile = SD.open(dataFileName, FILE_WRITE);
  if (dataFile) {
    if (SETTINGS.rawData) {
      dataFile.print(data.time,         6);
      dataFile.print(",");
      dataFile.print(data.pingTime,     6);
      dataFile.print(",");
      dataFile.print(data.temperature,  2);
      dataFile.print(",");
      dataFile.print(data.speedOfSound, 3);
      dataFile.print(",");
      dataFile.print(data.distance,     6);
      dataFile.println();
    }
    else {
      dataFile.print(data.time,         9);
      dataFile.print(",");
      dataFile.print(data.distance,     6);
      dataFile.println();
    }
    dataFile.close();
    return true;

  }
  else return false;


} // End of logData





bool logData_fp(measurement_fp data_fp) {

  dataFile = SD.open(dataFileName, FILE_WRITE);
  if (dataFile) {
    if (SETTINGS.rawData) {
      dataFile.print(data_fp.time);
      dataFile.print("E-6,");
      dataFile.print(data_fp.pingTime);
      dataFile.print("E-6,");
      dataFile.print(data_fp.temperature);
      dataFile.print("E-6,");
      dataFile.print(data_fp.speedOfSound);
      dataFile.print("E-6,");
      dataFile.print(data_fp.distance);
      dataFile.println("E-9");
    }
    else {
      dataFile.print(data_fp.time);
      dataFile.print("E-6,");
      dataFile.print(data_fp.distance);
      dataFile.println("E-9");
    }
    dataFile.close();
    return true;

  }
  else return false;


} // End of logData




// Remove current data file
bool removeCurrentDataFile() {
  if (SD.remove(dataFileName)) {
    previousDataFileName();
    return true;
  }
  else return false;
}
