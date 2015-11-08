/*
  Quantus
  quantus.ino
  Copyright (c) Leland Jansen 2015. All rights reserved.
*/


// Measure distance between an ultrasonic sensor and the target at user-specified interval
// Prints the result to the serial monitor


// Global variables

// Hardware pins
int onboardLEDPin  = 13; // Digital
int temperaturePin =  0; // Analog
int triggerPin     = 5; // Digital
int echoPin        = 6; // Digital


double measurementRate = 20; // Measurements per second
double measurementInterval = (1. / measurementRate) * 1.e3; // Convert to millisecond delay

int totalMeasurements = 200; // Total number of measurements taken
int counter = 0; // Number of times measurement has been taken


void setup() {

  // Pin setup
  
  // Set onboardLEDPin as output
  pinMode(onboardLEDPin, OUTPUT);

  // Set temperaturePin as input
  pinMode(temperaturePin, INPUT);

  // Set triggerPin as output
  pinMode(triggerPin, OUTPUT);

  // Set echoPin as input
  pinMode(echoPin, INPUT);



  // Initially set triggerPin to send a low signal
  digitalWrite(triggerPin, LOW);



  // Initialize serial port
  Serial.begin(9600);

  
  // LED countdown
  // Blink five times (five seconds total) before collecting data
  for (int i = 3; i > 0; i--) {
    //Serial.println(i);
    digitalWrite(onboardLEDPin, HIGH);
    delay(200);
    digitalWrite(onboardLEDPin, LOW);
    delay(800);
  }
  digitalWrite(onboardLEDPin, HIGH);
  
}





void loop() {
  

  if (counter < 200) {
  
    double temperature, humidity, pressure, speedOfSound, pingTime, targetDistance;

    uint32_t startTime = micros();
  
    // Take ambient temperature measurement
    temperature = measureTemperature(); // degrees Celsius
  
    // Set relative humidity
    humidity = 0.5; // fraction
    
    // Set ambient pressure
    pressure = 1.01325e5; // Pascales
  
    // Calculate speed of sound in air
    speedOfSound = calculateSpeedOfSound(temperature, humidity, pressure); // metres per second
    
    // Measure ultrasonic ping time
    pingTime = measurePingTime(); // seconds
  
    // Calculate distance to target
    targetDistance = calculateTargetDistance(pingTime, speedOfSound); // centimetres


    uint32_t endTime = micros();

    Serial.println(endTime-startTime );
  
    
    // Print target distance to serial monitor in centimetres
    //Serial.println(targetDistance, 4); // 4 decimal places
    
    counter += 1;
  
    // Delay for the user-specified interval
    delay(measurementInterval);
    //delayMicroseconds(15625);
  
  }

}
