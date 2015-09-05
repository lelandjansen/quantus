/*
  Quantus
  measurePingTime.ino
  Copyright (c) Leland Jansen 2015. All rights reserved.
*/


// Measure time taken for an ultrasonic signal to travel to target and return
// Hardware: Cytron HC-SRO4 Ultrasonic Sensor
// Returns ping time (time for ultrasonic signal to travel to target and return) in seconds
double measurePingTime() {

  // Global variables: triggerPin and echoPin
  // These are the digital pins to which the ultrasonic sensor is connected

  double pingTime;

  // Set triggerPin to HIGH
  // Produce ultrasonic signal
  digitalWrite(triggerPin, HIGH);

  // Delay 15 microseconds
  // This ensures a detectable ultrasonic signal is produced
  delayMicroseconds(15);

  // Set triggerPin to LOW
  // Stop producing ultrasonic signal
  digitalWrite(triggerPin, LOW);

  // Determine time taken for echoPin to reciece HIGH signal from triggerPin
  // Measured in microseconds
  // Divide by 1 million to convert microseconds to seconds
  pingTime = pulseIn(echoPin, HIGH) / 1.e6;
  
  return pingTime;

}
