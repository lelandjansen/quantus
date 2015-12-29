// QUANTUS
// distance.cpp

#include "distance.hpp"

double computeDistance(double pingTime, double speedOfSound) {

  //       speed = distance / time
  // => distance = speed * time

  // Calculate target in metres distance given speed of sound and ping time
  // Divide by 2 to get distance to target (not ditance to target and return)
  return speedOfSound * pingTime / 2.;

} // End of computeDistance
