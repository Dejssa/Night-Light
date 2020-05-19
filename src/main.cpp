#include <Arduino.h>
#include <FastLED.h>
#include <const.h>
#include <led.h>

int _current_brightness = 0;
bool isRaised = false;
unsigned long fading = 0;
unsigned long raising = 0;


void IRAM_ATTR movementDetected();
void turnOnNotification();

void setup() {
  Serial.begin(9600); 
  pinMode(PIN_MOTION, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_MOTION), movementDetected, CHANGE);

  initLed();

  turnOnNotification();
  zeroBrightness();
}

void loop() {
  if (isRaised) {
    if (_current_brightness != BRIGHTNESS) {
      _current_brightness = BRIGHTNESS;
      setBrightness(_current_brightness);
      raising = millis();
    }

    if (raising + RAISE_STATUS_UPDATE < millis()) {
      raising = millis();
    }
  } else {
    if (raising + DELAY_DETECTED < millis()) {
      if (fading + DELAY_DOWN_BRIGHT < millis() && _current_brightness > 0) {
        _current_brightness -= 1;
        setBrightness(_current_brightness);
        fading = millis();
      } 
    } 
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

void movementDetected() {
  isRaised = digitalRead(PIN_MOTION) == HIGH;
}
