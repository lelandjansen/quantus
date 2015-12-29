// QUANTUS
// buttonTest.ino

#include <TimerOne.h>


#define BUTTON 2

#define LED_RED 3
#define LED_GREEN 5
#define LED_BLUE 6



#define STATE_NO_SD         0
#define STATE_SD_SETUP      1
#define STATE_STANDBY       2
#define STATE_DATA_SETUP    3
#define STATE_DATA_COLLECT  4
#define STATE_DATA_CONCLUDE 5
#define STATE_WARNING       6
#define STATE_ERROR         7

uint8_t STATE;

int count = 0;

int i = 0;


uint8_t sineArray[] = { 128, 131, 134, 137, 140, 143, 146, 149, 152, 156, 159,
    162, 165, 168, 171, 174, 176, 179, 182, 185, 188, 191, 193, 196, 199, 201,
    204, 206, 209, 211, 213, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234,
    235, 237, 239, 240, 242, 243, 244, 246, 247, 248, 249, 250, 251, 251, 252,
    253, 253, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253,
    253, 252, 252, 251, 250, 249, 248, 247, 246, 245, 244, 242, 241, 239, 238,
    236, 235, 233, 231, 229, 227, 225, 223, 221, 219, 217, 215, 212, 210, 207,
    205, 202, 200, 197, 195, 192, 189, 186, 184, 181, 178, 175, 172, 169, 166,
    163, 160, 157, 154, 151, 148, 145, 142, 138, 135, 132, 129, 126, 123, 120,
    117, 113, 110, 107, 104, 101,  98,  95,  92,  89,  86,  83,  80,  77,  74,
     71,  69,  66,  63,  60,  58,  55,  53,  50,  48,  45,  43,  40,  38,  36,
     34,  32,  30,  28,  26,  24,  22,  20,  19,  17,  16,  14,  13,  11,  10,
      9,   8,   7,   6,   5,   4,   3,   3,   2,   2,   1,   1,   0,   0,   0,
      0,   0,   0,   0,   1,   1,   1,   2,   2,   3,   4,   4,   5,   6,   7,
      8,   9,  11,  12,  13,  15,  16,  18,  20,  21,  23,  25,  27,  29,  31,
     33,  35,  37,  39,  42,  44,  46 , 49,  51,  54,  56,  59,  62,  64,  67,
     70,  73,  76,  79,  81,  84,  87,  90,  93,  96,  99, 103, 106, 109, 112,
     115, 118, 121, 124, 127 };



void buttonPress() {
  count++;
  Serial.println(count);
  STATE = (STATE + 1) % 8;
}



void setup() {

  Serial.begin(9600);

  Timer1.initialize(5000);
  Timer1.attachInterrupt(pulseLED); // attach the service routine here
  
  
  pinMode(BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPress, FALLING);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  STATE = STATE_NO_SD;
 
  
}

void loop() {
  
}


void pulseLED() {


  
  if (digitalRead(BUTTON) == LOW) {

    // White
    analogWrite(LED_RED,     0);
    analogWrite(LED_GREEN,   0);
    analogWrite(LED_BLUE,    0);

  }
  else {

    switch (STATE) {
      case STATE_NO_SD:
        // Blinking red/white
        if (sineArray[i] > 128) {
          // Red
          analogWrite(LED_RED,     0);
          analogWrite(LED_GREEN, 255);
          analogWrite(LED_BLUE,  255);
        }
        else {
          // White
          analogWrite(LED_RED,     0);
          analogWrite(LED_GREEN,   0);
          analogWrite(LED_BLUE,    0);
        }
        break;
        
      case STATE_SD_SETUP:
        // Pulsing blue/magenta
        analogWrite(LED_RED,   sineArray[i]/2);
        analogWrite(LED_GREEN, 255);
        analogWrite(LED_BLUE,    0);
        break;
        
      case STATE_STANDBY:
        // Pulsing blue/cyan
        analogWrite(LED_RED,   255);
        analogWrite(LED_GREEN, sineArray[i]);
        analogWrite(LED_BLUE,    0);
        break;
        
      case STATE_DATA_SETUP:
        // Blink green on white
        if (sineArray[i] >= 0 && sineArray[i] < 6) {
          // Solid green
          analogWrite(LED_RED,   255);
          analogWrite(LED_GREEN,   0);
          analogWrite(LED_BLUE,  255);
        }
        else {
          // Solid yellow
          analogWrite(LED_RED,     0);
          analogWrite(LED_GREEN,   0);
          analogWrite(LED_BLUE,  255);
        }
        break;
        
      case STATE_DATA_COLLECT:
        // Solid green
        analogWrite(LED_RED,   255);
        analogWrite(LED_GREEN,   0);
        analogWrite(LED_BLUE,  255);
        break;
        
      case STATE_DATA_CONCLUDE:
        // Pulsing blue/magenta
        analogWrite(LED_RED,   sineArray[i]/2);
        analogWrite(LED_GREEN, 255);
        analogWrite(LED_BLUE,    0);
        break;
        
      case STATE_WARNING:
        // Blinking red/yellow
        if (sineArray[i] > 128) {
          // Red
          analogWrite(LED_RED,     0);
          analogWrite(LED_GREEN, 255);
          analogWrite(LED_BLUE,  255);
        }
        else {
          // Yellow
          analogWrite(LED_RED,     0);
          analogWrite(LED_GREEN,   0);
          analogWrite(LED_BLUE,  255);
        }
        break;
        
      case STATE_ERROR:
        // Solid red
        analogWrite(LED_RED,     0);
        analogWrite(LED_GREEN, 255);
        analogWrite(LED_BLUE,  255);
        break;
        
    }
    
    
    
  }
  // delay(1000);
  // Serial.println(count);

  i = (i + 1)%256;

  
}

