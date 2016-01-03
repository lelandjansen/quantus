// QUANTUS
// sd.cpp

#include "sd.hpp"


// DELETE
#include <Arduino.h>


int dataFileNumber;
File dataFile;
File settingsFile;
File errorFile;
char dataFileName[13];




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
    errorFile.println();
    errorFile.println(F("__________________________________________________"));
    errorFile.close();
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

  /*

  // Temperature
  if (SD.exists("SETTINGS/TEMP.txt")) {
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    settingsFile = SD.open("SETTINGS/TEMP.txt", FILE_READ);
    if (settingsFile) {
      // read file to array
      // convert
      // DELETE
      SETTINGS.autoTemperature = true;
      SETTINGS.temperature     = 20;
      if (SETTINGS.temperature < minimumSettings.temperature
       || SETTINGS.temperature > maximumSettings.temperature) {
          // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
          // Warning: temperature values out of range
          NEXT_STATE = STATE_WARNING;
      }
      settingsFile.close();
    }
    else {
      return false;
    }
  }
  else {
    settingsFile = SD.open("SETTINGS/TEMP.txt", FILE_WRITE);
    if (settingsFile) {
      settingsFile.print("auto");
      settingsFile.close();
    }
    else {
      return false;
    }
  }

  */

  // DELETE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  SETTINGS = defaultSettings;

  return true;

} // End of getSettingsFromFile





void nextDataFileName() {
  dataFileNumber++;
  sprintf(dataFileName, "QNTS_%03i.csv", dataFileNumber);
} // End of nextDataFileName





void determineDataFileNumber() {
  // Determine the number of the next data file
  for (dataFileNumber = 999; dataFileNumber >= 0; dataFileNumber--) {
    sprintf(dataFileName, "QNTS_%03i.csv", dataFileNumber);
    if (SD.exists(dataFileName) || dataFileNumber == 0) {
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
    NEXT_STATE = STATE_NO_SD;
    return;
  }


  // Get settings from file
  if (!getSettingsFromFile()) {
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // ERROR CODE
    NEXT_STATE = STATE_NO_SD;
    return;
  }


  // Determine data file number
  determineDataFileNumber();

  // If data file number is between 990 and 999
  // Warn that 10 or less data files can be created
  if (dataFileNumber > 989 && dataFileNumber < 1000) {
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // WARNING: 10 or less data files can be created
    NEXT_STATE = STATE_WARNING;
  }
  // If data file number is 1000
  // No more data files can be created
  else if (dataFileNumber == 1000) {
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // ERROR: No more data files can be created
    NEXT_STATE = STATE_ERROR;
    return;
  }


  if (NEXT_STATE != STATE_WARNING) {
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
    dataFile.print(SETTINGS.countDown);
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
