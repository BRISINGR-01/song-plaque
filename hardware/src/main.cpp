#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN 3
#define NUM_LEDS 3
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_COLORS 7

CRGB leds[NUM_LEDS];

const CRGB colors[NUM_COLORS]{
    CRGB(228, 128, 46), // rgba(228, 128, 46, 1)
    CRGB(184, 61, 61),  // rgba(184, 61, 61, 1)

    CRGB(227, 41, 94),  // rgba(227, 41, 94, 1)
    CRGB(230, 56, 123), // rgba(230, 56, 123, 1)
    CRGB(239, 104, 63), // rgba(239, 104, 63, 1)

    CRGB(206, 43, 111),  // rgba(206, 43, 111, 1)
    CRGB(250, 116, 154), // rgba(250, 116, 154, 1)
};

uint8_t breathe_brightness()
{
  return beatsin8(8, 40, 255);
}

void cycle_colors()
{
  static uint8_t index = 0;
  static uint8_t blendAmount = 0;

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = blend(colors[index], colors[(index + 1) % NUM_COLORS], blendAmount);
  }

  blendAmount++;

  if (blendAmount == 255)
  {
    blendAmount = 0;
    index = (index + 1) % NUM_COLORS;
  }
}

void setup()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
}

void loop()
{
  cycle_colors();
  FastLED.setBrightness(breathe_brightness());
  FastLED.show();
  delay(20);
}
