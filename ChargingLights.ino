/*
 * Charging Lights
 * 
 * To simulate the charging lights found on Marquee signs and on the
 * GE GEVO Hybrid Demonstrator
 */

#include "ChargingLights.h"

unsigned long prevMillis = 0;
int currLED = 0;
int positionCounter = 0;

void setup() {
  // loop to setup all of the LED output pins
  for (int i = LOW_LED; i < NUM_LEDS; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  pinMode(forwardPin, INPUT_PULLUP);
  pinMode(reversePin, INPUT_PULLUP);
}

void loop() {
  unsigned long currentMillis = millis();
  if ((currentMillis - prevMillis) >= interval) {
    if (digitalRead(reversePin) == LOW) {
      lights(true);
    } else {
      lights(false);
    }
    prevMillis = currentMillis;
  }
}

void lights(bool reversed) {
  if (reversed) {
    positionCounter--;
  } else {
    positionCounter++;
  }
  if (positionCounter >= NUM_LEDS) {
    positionCounter = LOW_LED;
  }
  if (positionCounter < LOW_LED) {
    positionCounter = (NUM_LEDS - 1);
  }
  for (int i = LOW_LED; i < NUM_LEDS; i++) {
    if (i == positionCounter) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
}
