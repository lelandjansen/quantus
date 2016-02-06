// QUANTUS
// pingTime

#include "pingTime.hpp"


// Measure time taken for an ultrasonic signal to travel to target and return
// Hardware: Cytron HC-SRO4 Ultrasonic Sensor
// Timeout in microseconds
double measurePingTime() {

  uint32_t pingTime; // microseconds
  uint32_t timeout = 14000; // microseconds
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // CONFIRM APPROPRIATE TIMEOUT VALUE


  // Produce ultrasonic signal
  digitalWrite(ULTRASONIC_TRIGGER, HIGH);

  // Delay 15 microseconds
  // Ensures a detectable ultrasonic signal is produced
  delayMicroseconds(15);

  // Stop producing ultrasonic signal
  digitalWrite(ULTRASONIC_TRIGGER, LOW);

  // Determine time taken for echoPin to reciece HIGH signal from triggerPin
  // Measured in microseconds
  pingTime = pulseIn(ULTRASONIC_ECHO, HIGH, timeout);

  // Convert from microseconds to seconds
  return (double)pingTime * 1.e-6;

} // End of measurePingTime





// Measure time taken for an ultrasonic signal to travel to target and return
// Hardware: Cytron HC-SRO4 Ultrasonic Sensor
// Timeout in microseconds
// Fixed-point calculation
// Scale factor: 10^6
uint32_t measurePingTime_fp() {

  uint32_t pingTime; // microseconds
  uint32_t timeout = 14000; // microseconds
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // CONFIRM APPROPRIATE TIMEOUT VALUE


  // Produce ultrasonic signal
  digitalWrite(ULTRASONIC_TRIGGER, HIGH);

  // Delay 15 microseconds
  // Ensures a detectable ultrasonic signal is produced
  delayMicroseconds(15);

  // Stop producing ultrasonic signal
  digitalWrite(ULTRASONIC_TRIGGER, LOW);

  // Determine time taken for echoPin to reciece HIGH signal from triggerPin
  // Measured in microseconds
  pingTime = pulseIn(ULTRASONIC_ECHO, HIGH, timeout);

  return pingTime;

} // End of measurePingTime
