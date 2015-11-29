// QUANTUS
// led.cpp

#include "led.h"


// Common anode RGB LED
// Supply 5V to anode
// Set red, green, and blue pins to LOW to turn on that color
// Set pins to HIGH to turn off that color

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


void whiteLED() {
  digitalWrite(LED_RED,   LOW);
  digitalWrite(LED_BLUE,  LOW);
  digitalWrite(LED_GREEN, LOW);
}

void offLED() {
  digitalWrite(LED_RED,   HIGH);
  digitalWrite(LED_BLUE,  HIGH);
  digitalWrite(LED_GREEN, HIGH);
}
