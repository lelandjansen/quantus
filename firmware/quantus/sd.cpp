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
const char logFileName[]      = "qLog.txt";





// Check if SD card is inserted
bool sdInserted() {
  return digitalRead(CARD_DETECT) == HIGH;
} // End of sdInserted





// Determine next state when SD card is inserted or removed
void sdChange() {
  delay(100);
  if (sdInserted()) NEXT_STATE = STATE_SD_SETUP;
  else {
    Timer1.attachInterrupt(led, 10000);
    NEXT_STATE = STATE_NO_SD;
  }
} // End of sdChange





// State while no SD card is inserted
void noSD() {
  return; // No SD card is inserted
} // End of noSD





// Log errors encountered in settings JSON file
// Returns true if successful, false if unsuccessful
bool logSettingsFileError(bool setToDefault, int variableIndex) {

  // Print logFile underscores if an error has not already been encountered
  if (!ERROR_ENCOUNTERED && !printUnderscoresToLogFile()) return false;

  NEXT_STATE = STATE_WARNING;

  // Array of variable names in JSON file
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

  // Open log file on SD card
  logFile = SD.open(logFileName, FILE_WRITE);

  // Write warning to log file
  //
  // If variable is not to be set to default, write to log file:
  // "Warning: Cannot parse <variableName> or value out of range in
  //  <settingsFile> file. Assigning default value."
  //
  // If variable is to be set to default, write to log file:
  // "Warning: Cannot parse <variableName> or value out of range in
  //  <settingsFile> file. Errors might occur.."
  if (logFile) {
    logFile.print(F("Warning: Cannot not parse \""));
    logFile.print(variableName[variableIndex]);
    logFile.print(F("\" or value out of range in \""));
    logFile.print(settingsFileName);
    logFile.print(F("\" file."));

    if (setToDefault) logFile.println(F(" Assigning default value."));
    else logFile.println(F(" Errors might occur."));
  }
  else return false;

  logFile.close();

  return true;

} // End of logSettingsFileError





// Write unserscores in log file to symbolize the start of a new series of
//  warnings/erros
// Returns true if successful, false if unsuccessful
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





// Error to print if the maximum amount of data allowed to be collected has been
//  reached
// Returns true if successful, false if unsuccessful
bool printMaximumDataError() {

  // Print logFile underscores if an error has not already been encountered
  if (!ERROR_ENCOUNTERED && !printUnderscoresToLogFile()) return false;

  // Write warning to log file
  // "Warning: Cannot collect more than <maximumData> data measurements."
  logFile = SD.open(logFileName);
  if (logFile) {
    logFile.print(F("Warning: Cannot collect more than "));
    logFile.print(SETTINGS.maximumData);
    logFile.println(F(" data measurements."));
    // Close the file
    logFile.close();
  }
  else return false;

  return true;

} // End of printMaximumDataError





// Set up the error log file
bool errorLogSetup() {

  // If log file does not exist, write header to log file
  // "Quantus: Error/warning log"
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




// Parse settings JSON file and extract configuration settings
bool getSettingsFromFile() {

  const int bufferSize = 200;
  char dataStringBuffer[bufferSize];

  // If the settings file exists
  if (SD.exists(settingsFileName)) {

    settingsFile = SD.open(settingsFileName, FILE_READ);
    if (settingsFile) {
      // Read the JSON file contents to the string buffer
      int i = 0;
      while (settingsFile.available() && i < bufferSize) {
        dataStringBuffer[i] = settingsFile.read();
        i++;
      }
    }

    // Parse JSON data (ArduinoJson library)
    StaticJsonBuffer<bufferSize> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(dataStringBuffer);

    // Set system settings to parsed JSON file values
    SETTINGS.rawData         = root["rawData"];
    SETTINGS.countdown       = root["countdown"];
    SETTINGS.frequency       = root["frequency"];
    SETTINGS.pressure        = root["pressure"];
    SETTINGS.humidity        = root["humidity"];
    SETTINGS.CO2MoleFraction = root["CO2MoleFraction"];
    SETTINGS.autoTemperature = root["autoTemperature"];
    SETTINGS.temperature     = root["temperature"];
    SETTINGS.maximumData     = root["maximumData"];


    // Verify that user-specified settings are within constraints
    // Log warning if settings cannot be parsed or are out of range
    // Return false if a warning cannot be written to the error log file

    // rawData (0)
    if (SETTINGS.rawData != false &&
        SETTINGS.rawData != true) {
      SETTINGS.rawData = SETTINGS_DEFAULT.rawData;
      if (!logSettingsFileError(true, 0)) return false;
    }

    // countdown (1)
    if (SETTINGS.countdown == NULL) {
      SETTINGS.countdown = SETTINGS_DEFAULT.countdown;
      if (!logSettingsFileError(true, 1)) return false;
    }
    else if (SETTINGS.countdown < SETTINGS_MINIMUM.countdown ||
             SETTINGS.countdown > SETTINGS_MAXIMUM.countdown) {
      if (!logSettingsFileError(false, 1)) return false;
    }

    // frequency (2)
    if (SETTINGS.frequency == NULL ||
        SETTINGS.frequency < SETTINGS_MINIMUM.frequency ||
        SETTINGS.frequency > SETTINGS_MAXIMUM.frequency) {
      SETTINGS.frequency = SETTINGS_DEFAULT.frequency;
      if (!logSettingsFileError(true, 2)) return false;
    }

    // pressure (3)
    if (SETTINGS.pressure == NULL) {
      SETTINGS.pressure = SETTINGS_DEFAULT.pressure;
      if (!logSettingsFileError(true, 3)) return false;
    }
    else if (SETTINGS.pressure < SETTINGS_MINIMUM.pressure ||
             SETTINGS.pressure > SETTINGS_MAXIMUM.pressure) {
      if (!logSettingsFileError(false, 3)) return false;
    }

    // humidity (4)
    if (SETTINGS.humidity == NULL) {
      SETTINGS.humidity = SETTINGS_DEFAULT.humidity;
      if (!logSettingsFileError(true, 4)) return false;
    }
    else if (SETTINGS.humidity < SETTINGS_MINIMUM.humidity ||
             SETTINGS.humidity > SETTINGS_MAXIMUM.humidity) {
      if (!logSettingsFileError(false, 4)) return false;
    }

    // CO2MoleFraction (5)
    if (SETTINGS.CO2MoleFraction == NULL) {
      SETTINGS.CO2MoleFraction = SETTINGS_DEFAULT.CO2MoleFraction;
      if (!logSettingsFileError(true, 5)) return false;
    }
    else if (SETTINGS.CO2MoleFraction < SETTINGS_MINIMUM.CO2MoleFraction ||
             SETTINGS.CO2MoleFraction > SETTINGS_MAXIMUM.CO2MoleFraction) {
      if (!logSettingsFileError(true, 5)) return false;
    }

    // autoTemperature (6)
    if (SETTINGS.autoTemperature != false &&
        SETTINGS.autoTemperature != true) {
      SETTINGS.autoTemperature = SETTINGS_DEFAULT.autoTemperature;
      if (!logSettingsFileError(true, 6)) return false;
    }

    // temperature (7)
    if (!SETTINGS.autoTemperature) {
      if (SETTINGS.temperature == NULL) {
        SETTINGS.temperature = SETTINGS_DEFAULT.temperature;
        if (!logSettingsFileError(true, 7)) return false;
      }
      else if (SETTINGS.temperature < SETTINGS_MINIMUM.temperature ||
               SETTINGS.temperature > SETTINGS_MAXIMUM.temperature) {
        if (!logSettingsFileError(false, 7)) return false;
      }
    }

    // maximumData (8)
    if (SETTINGS.maximumData == NULL ||
        SETTINGS.maximumData < SETTINGS_MINIMUM.maximumData ||
        SETTINGS.maximumData > SETTINGS_MAXIMUM.maximumData) {
      SETTINGS.maximumData = SETTINGS_DEFAULT.maximumData;
      if (!logSettingsFileError(true, 8)) return false;
    }

  } // End of if (i.e. settings file exists)


  // If the settings file does not exist, create one containing default settings
  else {

    // Print logFile underscores if an error has not already been encountered
    if (!ERROR_ENCOUNTERED && !printUnderscoresToLogFile()) return false;

    // Write warning to log file
    // "Warning: Cannot find file "<settingsFileName>". New settings file
    //  created containing default values."
    logFile = SD.open(logFileName, FILE_WRITE);
    if (logFile) {
      NEXT_STATE = STATE_WARNING;
      logFile.print(F("Warning: Cannot find file \""));
      logFile.print(settingsFileName);
      logFile.println(F("\". New settings file created containing default values."));
      logFile.close();
    }
    else return false;


    // Create JSON settings file containing default settings
    settingsFile = SD.open(settingsFileName, FILE_WRITE);
    if (settingsFile) {

      SETTINGS = SETTINGS_DEFAULT;

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





// Increment data file number and data file name by one
void nextDataFileName() {
  DATA_FILE_NUMBER++;
  sprintf(dataFileName, "qData_%03i.csv", DATA_FILE_NUMBER);
} // End of nextDataFileName

// Decrement data file number and data file name by one
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
  // FEATURE TO IMPLEMENT
  // Check available space on SD card
    // If SD card is almost full
      // Warning: SD card almost full
    // If SD card is full
      // Error: SD card is full


  // Set up error log file
  if (!errorLogSetup()) {
    NEXT_STATE = STATE_ERROR;
    return;
  }


  // Get settings from file
  if (!getSettingsFromFile()) {
    NEXT_STATE = STATE_ERROR;
    return;
  }


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

  if (NEXT_STATE != STATE_WARNING && NEXT_STATE != STATE_ERROR) NEXT_STATE = STATE_STANDBY;


} // End of sdSetup





// Write header to data file enumerating settings and data columns
// Returns true if successful, false if unsuccessful
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

} // End of dataFileHeader





// Log measured data to data file (floating point)
// Returns true if successful, false if unsuccessful
bool logData_float(measurement_float data) {

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


} // End of logData_float





// Log measured data to data file (fixed point)
// Returns true if successful, false if unsuccessful
bool logData_fixed(measurement_fixed data) {

  dataFile = SD.open(dataFileName, FILE_WRITE);
  if (dataFile) {

    if (SETTINGS.rawData) {
      dataFile.print(data.time);
      dataFile.print("E-6,");
      dataFile.print(data.pingTime);
      dataFile.print("E-6,");
      dataFile.print(data.temperature);
      dataFile.print("E-6,");
      dataFile.print(data.speedOfSound);
      dataFile.print("E-6,");
      dataFile.print(data.distance);
      dataFile.println("E-9");
    }
    else {
      dataFile.print(data.time);
      dataFile.print("E-6,");
      dataFile.print(data.distance);
      dataFile.println("E-9");
    }
    dataFile.close();
    return true;

  }
  else return false;

} // End of logData_fixed





// Remove current data file
// Returns true if successful, false if unsuccessful
bool removeCurrentDataFile() {
  if (SD.remove(dataFileName)) {
    previousDataFileName();
    return true;
  }
  else return false;
}
