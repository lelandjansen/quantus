// QUANTUS
// data.hpp

#ifndef __DATA_HPP__
#define __DATA_HPP__

#include <TimerOne.h>
#include "globals.hpp"
#include "sd.hpp"
#include "led.hpp"
#include "pingTime.hpp"
#include "temperature.hpp"
#include "speedOfSound.hpp"
#include "distance.hpp"


extern int    DATA_COUNT;
extern double START_TIME;


measurement takeMeasurement();
measurement_fp takeMeasurement_fp();
void dataSetup();
void dataCollect();
void dataCollect_fp();
void dataConclude();



#endif