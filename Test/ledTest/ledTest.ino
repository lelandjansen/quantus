// QUANTUS
// ledTest.ino

// Test to ensure that LED is connected correctly


#define LED_RED               3
#define LED_GREEN             5
#define LED_BLUE              6



void whiteLED() {
  digitalWrite(LED_RED,   LOW);
  digitalWrite(LED_BLUE,  LOW);
  digitalWrite(LED_GREEN, LOW);
}

void redLED() {
  digitalWrite(LED_RED,   LOW);
  digitalWrite(LED_BLUE,  HIGH);
  digitalWrite(LED_GREEN, HIGH);
}

void magentaLED() {
  digitalWrite(LED_RED,   LOW);
  digitalWrite(LED_BLUE,  LOW);
  digitalWrite(LED_GREEN, HIGH);
}

void blueLED() {
  digitalWrite(LED_RED,   HIGH);
  digitalWrite(LED_BLUE,  LOW);
  digitalWrite(LED_GREEN, HIGH);
}

void cyanLED() {
  digitalWrite(LED_RED,   HIGH);
  digitalWrite(LED_BLUE,  LOW);
  digitalWrite(LED_GREEN, LOW);
}

void greenLED() {
  digitalWrite(LED_RED,   HIGH);
  digitalWrite(LED_BLUE,  HIGH);
  digitalWrite(LED_GREEN, LOW);
}

void yellowLED() {
  digitalWrite(LED_RED,   LOW);
  digitalWrite(LED_BLUE,  HIGH);
  digitalWrite(LED_GREEN, LOW);
}

void offLED() {
  digitalWrite(LED_RED,   HIGH);
  digitalWrite(LED_BLUE,  HIGH);
  digitalWrite(LED_GREEN, HIGH);
}









void setup() {

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  Serial.begin(9600);

}

void loop() {

  whiteLED();
  Serial.println("white");
  delay(500);

  redLED();
  delay(500);
  Serial.println("red");

  magentaLED();
  Serial.println("magenta");
  delay(500);

  blueLED();
  Serial.println("blue");
  delay(500);

  cyanLED();
  Serial.println("cyan");
  delay(500);

  greenLED();
  Serial.println("green");
  delay(500);

  yellowLED();
  Serial.println("yellow");
  delay(500);

  offLED();
  Serial.println("off");
  delay(500);

}
