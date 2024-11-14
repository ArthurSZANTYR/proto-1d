#ifndef LEDS_H
#define LEDS_H

#include <FastLED.h>

class LEDController {
public:
    LEDController(uint8_t pin, uint8_t numLeds);
    void init();
    void update_good();
    void update_up();
    void update_down();
    void update_fraction();
    void update_longrun();
    void update_finisher();
private:
    CRGB* leds;
    uint8_t numLeds;
    uint8_t ledPin;
    int ledIndex = 0;
};

#endif