// QUANTUS
// data.hpp

#ifndef __DATA_HPP__
#define __DATA_HPP__

#include "globals.hpp"
#include "sd.hpp"
#include "led.hpp"
#include "pingTime.hpp"
#include "temperature.hpp"
#include "speedOfSound.hpp"
#include "distance.hpp"


extern int    DATA_COUNT;
extern double START_TIME;


measurement_float takeMeasurement_float();
measurement_fixed takeMeasurement_fixed();
void dataSetup();
void dataCollect_float();
void dataCollect_fixed();
void dataConclude();


#endif
