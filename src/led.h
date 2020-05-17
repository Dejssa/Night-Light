#include <Arduino.h>
#include <FastLED.h>
#include <const.h>

void initLed();

void zeroBrightness();
void fillWithColor(int r, int g, int b);
void lightUp();
void fadeBrightness(int delayTime);