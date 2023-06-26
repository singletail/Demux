#ifdef _LED
#include "main.h"
#include <FastLED.h>

#define DATA_PIN 6
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 300
#define BRIGHTNESS 255

CRGB leds[NUM_LEDS];

namespace led
{

    void init()
    {
        FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
            .setCorrection(TypicalLEDStrip)
            .setDither(BRIGHTNESS < 255);
        FastLED.setBrightness(BRIGHTNESS);
    }

    void on()
    {
        static uint8_t hue = 0;
        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i] = CHSV(hue++, 255, 255);
            FastLED.show();
        }
    }

    void off()
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i].nscale8(250);
        }
    }

    void pride()
    {
        static uint16_t sPseudotime = 0;
        static uint16_t sLastMillis = 0;
        static uint16_t sHue16 = 0;

        uint8_t sat8 = beatsin88(87, 220, 250);
        uint8_t brightdepth = beatsin88(341, 96, 224);
        uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
        uint8_t msmultiplier = beatsin88(147, 23, 60);

        uint16_t hue16 = sHue16; // gHue * 256;
        uint16_t hueinc16 = beatsin88(113, 1, 3000);

        uint16_t ms = millis();
        uint16_t deltams = ms - sLastMillis;
        sLastMillis = ms;
        sPseudotime += deltams * msmultiplier;
        sHue16 += deltams * beatsin88(400, 5, 9);
        uint16_t brightnesstheta16 = sPseudotime;

        for (uint16_t i = 0; i < NUM_LEDS; i++)
        {
            hue16 += hueinc16;
            uint8_t hue8 = hue16 / 256;

            brightnesstheta16 += brightnessthetainc16;
            uint16_t b16 = sin16(brightnesstheta16) + 32768;

            uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
            uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
            bri8 += (255 - brightdepth);

            CRGB newcolor = CHSV(hue8, sat8, bri8);

            uint16_t pixelnumber = i;
            pixelnumber = (NUM_LEDS - 1) - pixelnumber;

            nblend(leds[pixelnumber], newcolor, 64);
        }
        FastLED.show();
    }
}
#endif