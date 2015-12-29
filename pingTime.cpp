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

  // Convert from microseconds to seconds
  return (double)pingTime * 1.e-6;

} // End of measurePingTime
