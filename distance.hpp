// QUANTUS
// distance.hpp

#ifndef __DISTANCE_HPP__
#define __DISTANCE_HPP__


#include "globals.hpp"


double   computeDistance_float(double pingTime, double speedOfSound);
uint32_t computeDistance_fixed(uint32_t pingTime, uint32_t speedOfSound);


#endif
