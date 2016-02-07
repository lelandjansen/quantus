// QUANTUS
// sdTest.ino


// EDIT ME!!!!!!!!!!!!!!!!!!
// Code to test button interrupt functionality
// Sets up hardware interrupt
// Counts the number of times the button has been pressed
// Prints the button press count to the serial monitor on each press


# define SD 3


void sdChange() {
  delay(100);
  digitalRead(SD) == HIGH? Serial.println("IN") : Serial.println("OUT");

}



void setup() {

  Serial.begin(9600);

  pinMode(SD, INPUT);

  attachInterrupt(digitalPinToInterrupt(SD), sdChange, CHANGE);

}


void loop() {



}
