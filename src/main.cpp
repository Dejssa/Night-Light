#include <Arduino.h>
#include <FastLED.h>
#include <const.h>
#include <led.h>

int _current_brightness = -1;
bool raised = false;

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
  if (raised) {
    setBrightness(_current_brightness);
  } else if (_current_brightness > -1) {
    delay(DELAY_DETECTED);
    for(; _current_brightness >= 0; _current_brightness-=1) {
      if (raised) {
        _current_brightness = BRIGHTNESS;
        break;
      }
      setBrightness(_current_brightness);
      delay(DELAY_DOWN_BRIGHT);
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
  raised = digitalRead(PIN_MOTION) == HIGH;
  _current_brightness = BRIGHTNESS;
}
