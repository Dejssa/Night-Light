#include <Arduino.h>
#include <FastLED.h>

#define LEDS_COUNT 95
#define DELAY_DOWN_BRIGHT 10
#define DELAY_TURN_ON 200
#define DELAY_DETECTED 1000
#define BRIGHTNESS 100

#define PIN_LED 13
#define PIN_MOTION 15

void detectsMovement();
void turnOn();

CRGB leds[LEDS_COUNT];

void setup() {
  Serial.begin(9600); 

  

  FastLED.addLeds<WS2812B, PIN_LED, RGB>(leds, LEDS_COUNT);
  pinMode(PIN_MOTION, INPUT);
  // attachInterrupt(digitalPinToInterrupt(PIN_MOTION), detectsMovement, RISING);

  turnOn();


  FastLED.setBrightness(0);
  for (int i = 0; i < LEDS_COUNT; i++) {
    leds[i] = CRGB (0,255,255);
  }
  FastLED.show();
}

void loop() {

  if(digitalRead(PIN_MOTION) == HIGH) {
    detectsMovement();
  }

}

void turnOn() {
  FastLED.setBrightness(BRIGHTNESS);
  for (int i = 0; i < LEDS_COUNT; i++) {
    leds[i] = CRGB (0,0,255);
  }
  FastLED.show();
  delay(DELAY_TURN_ON);

  for (int i = 0; i < LEDS_COUNT; i++) {
    leds[i] = CRGB (0,255,0);
  }
  FastLED.show();
  delay(DELAY_TURN_ON);

    for (int i = 0; i < LEDS_COUNT; i++) {
    leds[i] = CRGB (255,0,0);
  }
  FastLED.show();
  delay(DELAY_TURN_ON);
}

// Checks if motion was detected, sets LED HIGH and starts a timer
void detectsMovement() {
  Serial.println("MOTION DETECTED!!!");

  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();

  for(int i = BRIGHTNESS; i > 0; i--) {
   FastLED.setBrightness(i);
    FastLED.show();
    delay(DELAY_DOWN_BRIGHT);
  }
}