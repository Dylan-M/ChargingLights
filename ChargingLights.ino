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
  Serial.begin(9600);
  Serial.println("Initializing");
  // loop to setup all of the LED output pins
  for (int i = LOW_LED; i < NUM_LEDS; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  pinMode(forwardPin, INPUT_PULLUP);
  pinMode(reversePin, INPUT_PULLUP);
  Serial.println("Initialized");
}

void loop() {
  unsigned long currentMillis = millis();
  Serial.print("Inside of the main loop with millis: ");
  Serial.print(currentMillis);
  Serial.print(" and previous millis of: ");
  Serial.print(prevMillis);
  Serial.println(". Processing...");
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
  Serial.println("Inside the lights function");
  if (reversed) {
    Serial.println("A");
    positionCounter--;
  } else {
    Serial.println("B");
    positionCounter++;
  }
  Serial.println("Checking position counter");
  if (positionCounter >= NUM_LEDS) {
    positionCounter = LOW_LED;
  }
  if (positionCounter < LOW_LED) {
    positionCounter = (NUM_LEDS - 1);
  }
  Serial.println("Before loop");
  for (int i = LOW_LED; i < NUM_LEDS; i++) {
    Serial.println("Inside loop");
    if (i == positionCounter) {
      Serial.print("Lighting pin: ");
      Serial.println(i);
      digitalWrite(i, HIGH);
    } else {
      Serial.print("Turning off pin: ");
      Serial.println(i);
      digitalWrite(i, LOW);
    }
  }
}
