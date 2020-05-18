#include <led.h>

CRGB leds[LEDS_COUNT];

void initLed() {
    FastLED.addLeds<WS2812B, PIN_LED, RGB>(leds, LEDS_COUNT);
}

void zeroBrightness() {
    FastLED.setBrightness(0);
    for (int i = 0; i < LEDS_COUNT; i++) {
        leds[i] = CRGB (0,255,255);
    }

    FastLED.show();
}

void fillWithColor(int r, int g, int b) {
  FastLED.setBrightness(BRIGHTNESS);
  for (int i = 0; i < LEDS_COUNT; i++) {
    leds[i] = CRGB (r,g,b);
  }
  FastLED.show();
}

void setBrightness(int val) {
    FastLED.setBrightness(val);
    FastLED.show();
}