// QUANTUS
// distance.cpp

#include "distance.hpp"

// Compute distance to target
double computeDistance(double pingTime, double speedOfSound) {

  //       speed = distance / time
  // => distance = speed * time

  // Calculate target in metres distance given speed of sound and ping time
  // Divide by 2 to get distance to target (not ditance to target and return)
  return speedOfSound * pingTime / 2.;

} // End of computeDistance




// Compute distance to target
// Fixed-point calculation
// Scale factor: 10^9
uint32_t computeDistance_fp(uint32_t pingTime, uint32_t speedOfSound) {

  //       speed = distance / time
  // => distance = speed * time

  // Calculate target in metres distance given speed of sound and ping time
  // Divide by 2000 to get distance to target (not ditance to target and return)
  uint32_t distance;
  distance  = speedOfSound / 2000;
  distance *= pingTime;

  return distance;

} // End of computeDistance_fp
