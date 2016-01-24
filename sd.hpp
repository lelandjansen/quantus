// QUANTUS
// sd.hpp

#ifndef __SD_HPP__
#define __SD_HPP__

#include <SPI.h>
#include <SdFat.h>
#include <stdlib.h>
#include <ArduinoJson.h>
#include "globals.hpp"
#include "led.hpp"



extern int DATA_FILE_NUMBER;
extern File dataFile;
extern File logFile;
extern char dataFileName[14];
extern const char settingsFileName[];
extern const char logFileName[];


bool sdInserted();
void sdChange();
void noSD();
bool logSettingsFileError(bool setToDefault, int variableIndex);
bool printUnderscoresToLogFile();
bool printMaximumDataError();
bool errorLogSetup();
bool getSettingsFromFile();
void nextDataFileName();
void previousDataFileName();
void determineDataFileNumber();
void sdSetup();
bool dataFileHeader();
bool logData(measurement data);
bool logData_fp(measurement_fp data_fp);
bool removeCurrentDataFile();

#endif
