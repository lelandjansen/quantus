// QUANTUS
// sd.hpp

#ifndef __SD_HPP__
#define __SD_HPP__

#include <SPI.h>
#include <SD.h>
#include <stdlib.h>
#include "globals.hpp"

extern int dataFileNumber;
extern File dataFile;
extern File errorFile;
extern char dataFileName[13];


void noSD();
// bool openDataFile();
// void closeDataFile();
bool errorLogSetup();
bool getSettingsFromFile();
void nextDataFileName();
void determineDataFileNumber();
void sdSetup();
bool dataFileHeader();
bool logData(measurement data);

#endif
