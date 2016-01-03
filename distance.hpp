// QUANTUS
// distance.hpp

#ifndef __DISTANCE_HPP__
#define __DISTANCE_HPP__

#include "globals.hpp"

double   computeDistance(double pingTime, double speedOfSound);
uint32_t computeDistance_fp(uint32_t pingTime, uint32_t speedOfSound);

#endif
