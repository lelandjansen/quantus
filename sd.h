// QUANTUS
// sd.h

#ifndef ___SD_H_
#define ___SD_H_

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <stdlib.h>
#include "globals.h"
#include "led.h"

void   sdSetup();
double getConstantsFromSD(char constantName);
void   dataFileSetup(int frequency, double humidity, double pressure);
void   writeDataToFile(double pointTime, double distance);

#endif
