// QUANTUS
// sd.cpp

#include "sd.hpp"
SdFat SD;


int DATA_FILE_NUMBER;
File dataFile;
File settingsFile;
File errorFile;
char dataFileName[13];
bool errorEncountered = false;



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
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  delay(100);
} // End of SDInserted



// State while no SD card is inserted
void noSD() {
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // NO SD CODE
} // End of noSD



// DELETE
// ALSO REMOVE FROM sd.hpp
// bool openDataFile() {
//
//   dataFile = SD.open(dataFileName, FILE_WRITE);
//     if (dataFile) {
//       return true;
//     }
//     else {
//       return false;
//     }
// } // End of openDataFile
//
//
// void closeDataFile() {
//   dataFile.close();
// }





bool errorLogSetup() {

  // Check if the file "ERRORLOG.txt" exists
  // If not, create it
  // Append new error log header

  if (!SD.exists("ERRORLOG.txt")) {
    errorFile = SD.open("ERRORLOG.txt", FILE_WRITE);
    if (errorFile) {
      errorFile.println(F("QUANTUS ERROR LOG"));
      errorFile.close();
    }
    else {
      return false;
    }
  }
  errorFile = SD.open("ERRORLOG.txt", FILE_WRITE);
  if (errorFile) {
    if (errorEncountered) {
      errorFile.println();
      errorFile.println(F("__________________________________________________"));
      errorFile.close();
    }
  }
  else {
    return false;
  }

  return true;

} // End of errorLogSetup





bool getSettingsFromFile() {

  if (!SD.exists("SETTINGS")) {
    SD.mkdir("SETTINGS");
  }

  // DELETE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  SETTINGS = defaultSettings;

  int bufferSize = 20 + 1;
  char stringBuffer[bufferSize];

  // rawData
  if (SD.exists("SETTINGS/rawData.txt")) {

    settingsFile = SD.open("SETTINGS/rawData.txt", FILE_READ);
    if (settingsFile) {
      // Read file contents to buffer
      int i = 0;
      while (settingsFile.available()) {
        if (i == bufferSize) break;
        stringBuffer[i] = settingsFile.read();
        i++;
      }
    }

    // Check if string
    if (strncmp(stringBuffer, "true", 4) == 0) {
      Serial.println(F("rawData = true"));
      SETTINGS.rawData = true;
    }
    else if (strncmp(stringBuffer, "false", 5) == 0) {
      Serial.println(F("rawData = false"));
      SETTINGS.rawData = false;
    }
    else {
      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      Serial.println(F("Warning: rawData.txt file does not contain correct value. Setting to default value (false). Original file not modified."));
      SETTINGS.rawData = false;
    }
  }
  // If the file does not exist
  else {
    settingsFile = SD.open("SETTINGS/rawData.txt", FILE_WRITE);
    if (settingsFile) {
      settingsFile.print(F("false"));
      Serial.println(F("Did not find rawData.txt. Created file and set value to false."));
      settingsFile.close();
      SETTINGS.rawData = false;
    }
    else {
      return false;
    }
  }

  Serial.print("Raw data: ");
  Serial.println(SETTINGS.rawData);

  return true;

} // End of getSettingsFromFile





void nextDataFileName() {
  DATA_FILE_NUMBER++;
  sprintf(dataFileName, "QNTS_%03i.csv", DATA_FILE_NUMBER);
} // End of nextDataFileName

void previousDataFileName() {
  DATA_FILE_NUMBER--;
  sprintf(dataFileName, "QNTS_%03i.csv", DATA_FILE_NUMBER);
} // End of nextDataFileName




void determineDataFileNumber() {

  // Determine the number of the next data file
  for (DATA_FILE_NUMBER = 999; DATA_FILE_NUMBER >= 0; DATA_FILE_NUMBER--) {
    if (NEXT_STATE == STATE_NO_SD) break;
    sprintf(dataFileName, "QNTS_%03i.csv", DATA_FILE_NUMBER);
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
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // ERROR CODE
    Serial.println(F("Error: Could not create error log."));
    NEXT_STATE = STATE_NO_SD;
    return;
  }


  // Get settings from file
  if (!getSettingsFromFile()) {
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // ERROR CODE
    Serial.println(F("Error: Could not get settings from file."));
    NEXT_STATE = STATE_NO_SD;
    return;
  }


  // Determine data file number
  determineDataFileNumber();

  // If data file number is between 990 and 999
  // Warn that 10 or less data files can be created
  if (DATA_FILE_NUMBER > 989 && DATA_FILE_NUMBER < 1000) {
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // WARNING: 10 or less data files can be created
    Serial.println(F("Warning: 10 or less data files remain"));
    NEXT_STATE = STATE_WARNING;
  }
  // If data file number is 1000
  // No more data files can be created
  else if (DATA_FILE_NUMBER >= 1000) {
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // ERROR: No more data files can be created
    Serial.println(F("Error: No more data files can be created."));
    NEXT_STATE = STATE_ERROR;
    return;
  }

  if (NEXT_STATE != STATE_WARNING && NEXT_STATE != STATE_NO_SD) {
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


    if (SETTINGS.rawData) dataFile.println(F(",,,,"));
    else dataFile.println(F(","));

    if (SETTINGS.rawData) dataFile.println(F("time (s),ping time (s),temperature (C),computed speed of sound (m/s),computed distance (m)"));
    else dataFile.println(F("time (s),distance (m)"));

    dataFile.close();

  }
  else {
    return false;
  }

  return true;
}





bool logData(measurement data) {

  dataFile = SD.open(dataFileName, FILE_WRITE);
  if (dataFile) {
    if (SETTINGS.rawData) {
      dataFile.print(data.time,         6);
      dataFile.print(F(","));
      dataFile.print(data.pingTime,     6);
      dataFile.print(F(","));
      dataFile.print(data.temperature,  2);
      dataFile.print(F(","));
      dataFile.print(data.speedOfSound, 3);
      dataFile.print(F(","));
      dataFile.print(data.distance,     6);
      dataFile.println();
      dataFile.close();
    }
    else {
      dataFile.print(data.time,         9);
      dataFile.print(F(","));
      dataFile.print(data.distance,     6);
      dataFile.println();
      dataFile.close();
    }

    return true;

  }
  else {
    return false;
  }


} // End of logData





bool logData_fp(measurement_fp data_fp) {

  dataFile = SD.open(dataFileName, FILE_WRITE);
  if (dataFile) {
    if (SETTINGS.rawData) {
      dataFile.print(data_fp.time);
      dataFile.print(F("e-6,"));
      dataFile.print(data_fp.pingTime);
      dataFile.print(F("e-6,"));
      dataFile.print(data_fp.temperature);
      dataFile.print(F("e-6,"));
      dataFile.print(data_fp.speedOfSound);
      dataFile.print(F("e-6,"));
      dataFile.print(data_fp.distance);
      dataFile.println(F("e-9"));
      dataFile.close();
    }
    else {
      dataFile.print(data_fp.time);
      dataFile.print(F("e-6,"));
      dataFile.print(data_fp.distance);
      dataFile.println(F("e-9"));
      dataFile.close();
    }

    return true;

  }
  else {
    return false;
  }


} // End of logData




// Remove current data file
bool removeCurrentDataFile() {
  if (SD.remove(dataFileName)) {
    previousDataFileName();
    return true;
  }
  else {
    return false;
  }
}
