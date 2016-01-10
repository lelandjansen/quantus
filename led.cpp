// QUANTUS
// led.cpp

#include "led.hpp"

volatile uint8_t PULSE_COUNT;



// Turn RGB LED off
void ledOff() {
  analogWrite(LED_RED,   255);
  analogWrite(LED_GREEN, 255);
  analogWrite(LED_BLUE,  255);
} // End of ledOff



// Make RGB LED solid white
void ledWhite() {
  analogWrite(LED_RED,     0);
  analogWrite(LED_GREEN,   0);
  analogWrite(LED_BLUE,    0);
} // End of ledWhite


// Make RGB LED solid red
void ledRed() {
  analogWrite(LED_RED,     0);
  analogWrite(LED_GREEN, 255);
  analogWrite(LED_BLUE,  255);
} // End of ledGreen


// Make RGB LED solid yellow
void ledYellow() {
  analogWrite(LED_RED,     0);
  analogWrite(LED_GREEN,   0);
  analogWrite(LED_BLUE,  255);
} // End of ledYellow



// Make RGB LED solid green
void ledGreen() {
  analogWrite(LED_RED,   255);
  analogWrite(LED_GREEN,   0);
  analogWrite(LED_BLUE,  255);
} // End of ledGreen



// Make RGB LED solid cyan
void ledCyan() {
  analogWrite(LED_RED,   255);
  analogWrite(LED_GREEN,   0);
  analogWrite(LED_BLUE,    0);
} // End of ledCyan


// Make RGB LED solid blue
void ledBlue() {
  analogWrite(LED_RED,   255);
  analogWrite(LED_GREEN, 255);
  analogWrite(LED_BLUE,    0);
} // End of ledBlue


// Make RGB LED solid magenta
void ledMagenta() {
  analogWrite(LED_RED,     0);
  analogWrite(LED_GREEN, 255);
  analogWrite(LED_BLUE,    0);
} // End of ledMagenta




uint8_t pulse() {

  // Formula: f(x) = (exp(sin(x))-1/e)(255/(e-1/e))

  // f(0) to f(63)
  if (PULSE_COUNT >= 0 && PULSE_COUNT <= 63) {
    return PULSE_A[PULSE_COUNT];
  }
  // f(64) to f(127)
  else if (PULSE_COUNT >= 64 && PULSE_COUNT <= 127) {
    return PULSE_A[64-(PULSE_COUNT-64)-1];
  }
  // f(128) to f(191)
  else if (PULSE_COUNT >= 128 && PULSE_COUNT <= 191) {
    return PULSE_B[PULSE_COUNT-128];
  }
  // f(192) to f(255)
  else if (PULSE_COUNT >= 192 && PULSE_COUNT <= 255) {
    return PULSE_B[192-(PULSE_COUNT-64)-1];
  }

} // End of pulse





// ledCountdown blinks the LED counting down to data collection
void ledCountdown() {

  // If a countdown is specified
  if (SETTINGS.countdown) {
    uint32_t countdownStart;

    // Make the LED yellow for 250 milliseconds
    countdownStart = millis();
    while (sdInserted()
     && millis() - countdownStart < 250
     && NEXT_STATE != STATE_DATA_CONCLUDE) {
      ledYellow();
    }

    // Blink the LED green for 150 milliseconds once every second
    countdownStart = millis();
    ledGreen();
    while (sdInserted()
     && millis() - countdownStart < 1000 * SETTINGS.countdown
     && NEXT_STATE != STATE_DATA_CONCLUDE) {
      if ((millis() - countdownStart)%1000 > 149) {
        ledYellow();
      }
      else { //if ((millis() - countdownStart)%150 == 0) {
        ledGreen();
      }
    }
  }

} // End of ledCountdown







// led modifies the LED colour depending on the current state and button state
void led() {

  // If button has been pressed
  if (digitalRead(HIGH) == LOW
        && STATE != STATE_NO_SD
        && STATE != STATE_SD_SETUP
        && STATE != STATE_DATA_CONCLUDE
        && STATE != STATE_ERROR) {

    // White
    ledWhite();

  }

  // If button has not been pressed
  else {

    switch (STATE) {
      case STATE_NO_SD:
        // Pulsing red/orange
        analogWrite(LED_RED,   0);
        analogWrite(LED_GREEN, 255-pulse()/4);
        analogWrite(LED_BLUE,  255);
        break;

      case STATE_SD_SETUP:
        // Pulsing blue/magenta
        analogWrite(LED_RED,   pulse()/2);
        analogWrite(LED_GREEN, 255);
        analogWrite(LED_BLUE,    0);
        break;

      case STATE_STANDBY:
        // Pulsing blue/cyan
        analogWrite(LED_RED,   255);
        analogWrite(LED_GREEN, pulse());
        analogWrite(LED_BLUE,    0);
        break;

      case STATE_DATA_SETUP:
        // Colour controlled within setup function
        break;

      case STATE_DATA_COLLECT:
        // Solid green
        ledGreen();
        break;

      case STATE_DATA_CONCLUDE:
        // Pulsing blue/magenta
        analogWrite(LED_RED,   pulse()/2);
        analogWrite(LED_GREEN, 255);
        analogWrite(LED_BLUE,    0);
        break;

      case STATE_WARNING:
        // Blinking red/yellow
        if ((PULSE_COUNT >=   0 && PULSE_COUNT <=  63)
         || (PULSE_COUNT >= 128 && PULSE_COUNT <= 191)) ledRed();
        else ledYellow();
        break;

      case STATE_ERROR:
      // Blinking red/white
      if ((PULSE_COUNT >=   0 && PULSE_COUNT <=  63)
       || (PULSE_COUNT >= 128 && PULSE_COUNT <= 191)) ledRed();
      else ledWhite();
      break;

    } // End of switch

  } // End of if

  PULSE_COUNT = (PULSE_COUNT + 1)%256;

} // End of led
