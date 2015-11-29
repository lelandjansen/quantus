// QUANTUS
// pingTime.cpp

#include "pingTime.h"

// Measure time taken for an ultrasonic signal to travel to target and return
// Hardware: Cytron HC-SRO4 Ultrasonic Sensor
// Returns ping time (time for ultrasonic signal to travel to target and return) in seconds
// Timeout in microseconds
uint32_t measurePingTime(uint32_t timeout) {

  // Global variables: triggerPin and echoPin
  // These are the digital pins to which the ultrasonic sensor is connected

  uint32_t pingTime;

  // Set triggerPin to HIGH
  // Produce ultrasonic signal
  digitalWrite(ULTRASONIC_TRIGGER, HIGH);

  // Delay 15 microseconds
  // This ensures a detectable ultrasonic signal is produced
  delayMicroseconds(15);

  // Set triggerPin to LOW
  // Stop producing ultrasonic signal
  digitalWrite(ULTRASONIC_TRIGGER, LOW);

  // Determine time taken for echoPin to reciece HIGH signal from triggerPin
  // Measured in microseconds
  // Divide by 1 million to convert microseconds to seconds
  pingTime = pulseIn(ULTRASONIC_ECHO, HIGH, timeout);

  return pingTime;

}
