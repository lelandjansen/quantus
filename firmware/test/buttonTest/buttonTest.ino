// QUANTUS
// buttonTest.ino

// Code to test button interrupt functionality
// Sets up hardware interrupt
// Counts the number of times the button has been pressed
// Prints the button press count to the serial monitor on each press


# define BUTTON 2

int PRESSCOUNT;



void buttonPress() {
  PRESSCOUNT++;
  Serial.println(PRESSCOUNT);
}



void setup() {

  PRESSCOUNT = 0;

  Serial.begin(9600);

  pinMode(BUTTON, INPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPress, RISING);

}


void loop() {



}
