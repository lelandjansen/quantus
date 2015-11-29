// QUANTUS
// distance.cpp

#include "distance.h"

// Calculate the distance between the ultrasonic sensor and the target
// Accepts two parameters: pingTime and speedOfSound
// pingTime is the time taken for an ultrasonic signal to travel to target and return (measured in seconds)
// speedOfSound is the calculated speed of sound in air (measured in metres per second)
// Returns distance to tagret in metres per second
double calculateTargetDistance(double pingTime, double speedOfSound) {


  // convert pintTime from microseconds to seconds
  pingTime /= 1.e6;

  //       speed = distance / time
  // => distance = speed * time

  // Calculate target in metres distance given speed of sound and ping time
  // Divide by 2 to get distance to target (not ditance to target and return)
  double targetDistance = speedOfSound * pingTime / 2.;

  return targetDistance;

}
