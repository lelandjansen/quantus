// QUANTUS
// led.cpp

#include "led.hpp"

volatile uint8_t PULSE_COUNT;



// Turn RGB LED off
void ledOff() {
  analogWrite(LED_RED,   LED_OFF);
  analogWrite(LED_GREEN, LED_OFF);
  analogWrite(LED_BLUE,  LED_OFF);
} // End of ledOff



// Make RGB LED solid white
void ledWhite() {
  analogWrite(LED_RED,   LED_ON);
  analogWrite(LED_GREEN, LED_ON);
  analogWrite(LED_BLUE,  LED_ON);
} // End of ledWhite


// Make RGB LED solid red
void ledRed() {
  analogWrite(LED_RED,   LED_ON);
  analogWrite(LED_GREEN, LED_OFF);
  analogWrite(LED_BLUE,  LED_OFF);
} // End of ledGreen


// Make RGB LED solid yellow
void ledYellow() {
  analogWrite(LED_RED,   LED_ON);
  analogWrite(LED_GREEN, LED_ON);
  analogWrite(LED_BLUE,  LED_OFF);
} // End of ledYellow



// Make RGB LED solid green
void ledGreen() {
  analogWrite(LED_RED,   LED_OFF);
  analogWrite(LED_GREEN, LED_ON);
  analogWrite(LED_BLUE,  LED_OFF);
} // End of ledGreen



// Make RGB LED solid cyan
void ledCyan() {
  analogWrite(LED_RED,   LED_OFF);
  analogWrite(LED_GREEN, LED_ON);
  analogWrite(LED_BLUE,  LED_ON);
} // End of ledCyan


// Make RGB LED solid blue
void ledBlue() {
  analogWrite(LED_RED,   LED_OFF);
  analogWrite(LED_GREEN, LED_OFF);
  analogWrite(LED_BLUE,  LED_ON);
} // End of ledBlue


// Make RGB LED solid magenta
void ledMagenta() {
  analogWrite(LED_RED,   LED_ON);
  analogWrite(LED_GREEN, LED_OFF);
  analogWrite(LED_BLUE,  LED_ON);
} // End of ledMagenta



// Pulse the RGB LED using following the respiration equation pattern
//
// Respiration equation:
// f(x) = (exp(sin(x))-1/e)(255/(e-1/e))
uint8_t pulse() {

  return (exp(sin(PULSE_COUNT*2*M_PI/256))-(1/M_E))*(255/(exp(1)-1/M_E));


  // // f(0) to f(63)
  // if (PULSE_COUNT >= 0 && PULSE_COUNT <= 63) {
  //   return PULSE_A[PULSE_COUNT];
  // }
  // // f(64) to f(127)
  // else if (PULSE_COUNT >= 64 && PULSE_COUNT <= 127) {
  //   // == PULSE_A[64-(PULSE_COUNT-64)-1]
  //   return PULSE_A[127-PULSE_COUNT];
  // }
  // // f(128) to f(191)
  // else if (PULSE_COUNT >= 128 && PULSE_COUNT <= 191) {
  //   return PULSE_B[PULSE_COUNT-128];
  // }
  // // f(192) to f(LED_OFF)
  // else if (PULSE_COUNT >= 192 && PULSE_COUNT <= 255) {
  //   // == PULSE_B[192-(PULSE_COUNT-64)-1]
  //   return PULSE_B[LED_OFF-PULSE_COUNT];
  // }

} // End of pulse





// Blink the LED counting down to data collection
void ledCountdown() {

  // If a countdown is specified (i.e. not zero)
  if (SETTINGS.countdown) {
    uint32_t countdownStart;

    // Make the LED yellow for 250 milliseconds
    countdownStart = millis();

    while (sdInserted() &&
           millis() - countdownStart < 250 &&
           NEXT_STATE != STATE_DATA_CONCLUDE) {

      ledYellow();

    } // End of while

    // Blink the LED green for 150 milliseconds once every second
    countdownStart = millis();
    ledGreen();
    while (sdInserted() &&
           millis() - countdownStart < 1000 * SETTINGS.countdown &&
           NEXT_STATE != STATE_DATA_CONCLUDE) {

      if ((millis() - countdownStart)%1000 > 149) ledYellow();
      else ledGreen();

    } // End of while

  } // End of if

} // End of ledCountdown







// Modify the LED colour depending on the current state and button state
void led() {

  // If button has been pressed and it is possible to advance to the next state
  if (digitalRead(BUTTON) == HIGH &&
      STATE != STATE_NO_SD &&
      STATE != STATE_SD_SETUP &&
      STATE != STATE_DATA_CONCLUDE &&
      STATE != STATE_ERROR) {

    // Solid white
    ledWhite();

  }

  // If button has not been pressed
  else {

    switch (STATE) {

      case STATE_NO_SD:
        // Pulsing red/orange
        analogWrite(LED_RED,   LED_ON);
        analogWrite(LED_GREEN, pulse()/2);
        analogWrite(LED_BLUE,  LED_OFF);
        break;

      case STATE_SD_SETUP:
        // Pulsing blue/magenta
        analogWrite(LED_RED,   pulse()/2);
        analogWrite(LED_GREEN, LED_OFF);
        analogWrite(LED_BLUE,  LED_ON);
        break;

      case STATE_STANDBY:
        // Pulsing blue/cyan
        analogWrite(LED_RED,   LED_OFF);
        analogWrite(LED_GREEN, pulse());
        analogWrite(LED_BLUE,  LED_ON);
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
        analogWrite(LED_GREEN, LED_OFF);
        analogWrite(LED_BLUE,  LED_ON);
        break;

      case STATE_WARNING:
        // Blinking red/yellow
        if ((PULSE_COUNT >= LED_ON && PULSE_COUNT <=  63) ||
            (PULSE_COUNT >= 128 && PULSE_COUNT <= 191)) ledRed();
        else ledYellow();
        break;

      case STATE_ERROR:
      // Blinking red/white
      if ((PULSE_COUNT >= LED_ON && PULSE_COUNT <=  63) ||
          (PULSE_COUNT >= 128 && PULSE_COUNT <= 191)) ledRed();
      else ledWhite();
      break;

    } // End of switch

  } // End of if

  // Increment PULSE_COUNT
  PULSE_COUNT = (PULSE_COUNT + 1)%256;

} // End of led
