/*
  Quantus
  main.ino
  Copyright (c) Leland Jansen 2015. All rights reserved.
*/


// Measure distance between an ultrasonic sensor and the target at user-specified interval
// Prints the result to the serial monitor


// Global variables
// Hardware pins
int onboardLEDPin  = 13; // Digital
int temperaturePin =  0; // Analog
int triggerPin     = 10; // Digital
int echoPin        = 11; // Digital


double measurementRate = 5; // Measurements per second
double measurementInterval = (1. / measurementRate) * 1.e3; // Convert to milliseconds

int counter = 0;


void setup() {

  // Pin setup

  // !!!!! NOT IN ORIGINAL FUNCTION
  // Set onboardLEDPin as output
  pinMode(onboardLEDPin, OUTPUT);

  // Set temperaturePin as input
  pinMode(temperaturePin, INPUT);

  // !!!!! NOT IN ORIGINAL FUNCTION
  // Set triggerPin as output
  pinMode(triggerPin, OUTPUT);

  // Set echoPin as input
  pinMode(echoPin, INPUT);



  // Initially set triggerPin to send a low signal
  digitalWrite(triggerPin, LOW);



  // Initialize serial port
  Serial.begin(9600);

  /*
  // Indicate program has started by printing to console
  Serial.print("Begin taking measurements at interval of ");
  Serial.print(measurementInterval);
  Serial.println(" milliseconds");
  */
  
  // Turn on LED
  for (int i = 0; i < 5; i++) {
    digitalWrite(onboardLEDPin, HIGH);
    delay(200);
    digitalWrite(onboardLEDPin, LOW);
    delay(800);
  }
  digitalWrite(onboardLEDPin, HIGH);
  
}





void loop() {
  

  if (counter < 50) {
  
    double temperature, humidity, pressure, speedOfSound, pingTime, targetDistance;
  
    // Take ambient temperature measurement
    temperature = measureTemperature(); // degrees Celsius
  
    // Set relative humidity
    humidity = 0.5; // fraction
    
    // Set ambient pressure
    pressure = 1.01325e5; // Pascales
  
    // Calculate speed of sound in air
    speedOfSound = calculateSpeedOfSound(temperature, humidity, pressure); // metres per second
    // speedOfSound = 343.2;
    
    // Measure ultrasonic ping time
    pingTime = measurePingTime(); // seconds
  
    // Calculate distance to target
    targetDistance = calculateTargetDistance(pingTime, speedOfSound); // centimetres
  
    
    // Print target distance to serial monitor
    Serial.println(targetDistance, 4); // 4 decimal places
    //Serial.println(" cm");
    

    counter += 1;
  
    // Delay for the user-specified interval
    delay(50/*measurementInterval*/);

  }

}
