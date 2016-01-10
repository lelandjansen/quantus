// QUANTUS
// sd.hpp

#ifndef __SD_HPP__
#define __SD_HPP__

#include <SPI.h>
#include <SdFat.h>
#include <stdlib.h>
#include "globals.hpp"
#include "led.hpp"

extern int  dataFileNumber;
extern File dataFile;
extern File errorFile;
extern char dataFileName[13];


bool sdInserted();
void sdChange();
void noSD();
// bool openDataFile();
// void closeDataFile();
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
