#include <arduino.h>

static const int ULTRASONIC_TRIGGER = 2;
static const int ULTRASONIC_ECHO = 4;

void Ping(int trials, unsigned long time_between_pings) {
  unsigned long ping_time; // microseconds
  unsigned long timeout = 14000; // microseconds
  unsigned long results[trials];

  for (int i = 0; i < trials; ++i) {
    digitalWrite(ULTRASONIC_TRIGGER, HIGH);
    delayMicroseconds(15);
    digitalWrite(ULTRASONIC_TRIGGER, LOW);
    ping_time = pulseIn(ULTRASONIC_ECHO, HIGH, timeout);
    results[i] = ping_time;
    delay((time_between_pings - ping_time)/1000);
  }

  for (int i = 0; i < trials; ++i) Serial.println(results[i]);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Begin ultrasonic sensor test");

  pinMode(ULTRASONIC_TRIGGER, OUTPUT);
  pinMode(ULTRASONIC_ECHO,    INPUT);

  int trials = 100;
  unsigned long time_between_pings = 50000; // microseconds

  int test_frequencies[] = {5, 10, 20, 32};

  for (int i = 0; i < sizeof(test_frequencies)/sizeof(test_frequencies[0]); ++i)
    Ping(300, 1000000/test_frequencies[i]);

  Serial.println("End ultrasonic sensor test");
}

void loop() {
  //
}
