#include <Arduino.h>
#include <FastLED.h>
#include <const.h>
#include <led.h>


void detectsMovement();
void turnOnNotification();


void setup() {
  Serial.begin(9600); 
  pinMode(PIN_MOTION, INPUT);

  initLed();

  turnOnNotification();
  zeroBrightness();
}

void loop() {

  if(digitalRead(PIN_MOTION) == HIGH) {
    detectsMovement();
  }

}

void turnOnNotification() {
  fillWithColor(0,0,255);
  delay(DELAY_TURN_ON);
  
  fillWithColor(0,255,0);
  delay(DELAY_TURN_ON);

  fillWithColor(255,0,0);
  delay(DELAY_TURN_ON);
}


// Checks if motion was detected, sets LED HIGH and starts a timer
void detectsMovement() {
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();

  delay(DELAY_DETECTED);
  fadeBrightness(DELAY_DOWN_BRIGHT);
}