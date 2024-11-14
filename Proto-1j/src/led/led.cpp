#include "led.h"

LEDController::LEDController(uint8_t pin, uint8_t numLeds) : ledPin(pin), numLeds(numLeds) {
    leds = new CRGB[numLeds];
}

void LEDController::init() {
    FastLED.addLeds<WS2812B, 0, GRB>(leds, numLeds);  // Use the overload that doesn't require a constant pin
    FastLED.setBrightness(50);  // You can set brightness or other configurations here
}


void LEDController::update_fraction() {
    // Éteindre toutes les LEDs
    for (int i = 0; i < numLeds; i++) {
        leds[i] = CRGB::Black;
    }
    // Allumer une LED
    leds[ledIndex] = CRGB::Red;
    FastLED.show();
    // Passer à la LED suivante
    ledIndex++;
    if (ledIndex >= numLeds) {
        ledIndex = 0; // Revenir à la première LED
    }
}



void LEDController::update_up() {
    // Variable de luminosité (de 0 à 255)
    static uint8_t brightness = 0;
    static bool increasing = true; // Indique si la luminosité augmente ou diminue

    // Mettre à jour la luminosité progressivement
    if (increasing) {
        brightness += 5; // Augmente la luminosité (ajustez la valeur pour la vitesse)
        if (brightness >= 255) {
            brightness = 255;
            increasing = false; // Commencer à diminuer
        }
    } else {
        brightness -= 5; // Diminue la luminosité
        if (brightness <= 0) {
            brightness = 0;
            increasing = true; // Recommencer à augmenter
        }
    }

    // Appliquer la luminosité à toutes les LEDs
    for (int i = 0; i < numLeds; i++) {
        leds[i] = CRGB::Red;
        leds[i].fadeToBlackBy(255 - brightness); // Ajuste la luminosité
    }

    FastLED.show();
}

void LEDController::update_down() {
    // Variable de luminosité (de 0 à 255)
    static uint8_t brightness = 0;
    static bool increasing = true; // Indique si la luminosité augmente ou diminue

    // Mettre à jour la luminosité progressivement
    if (increasing) {
        brightness += 5; // Augmente la luminosité (ajustez la valeur pour la vitesse)
        if (brightness >= 255) {
            brightness = 255;
            increasing = false; // Commencer à diminuer
        }
    } else {
        brightness -= 5; // Diminue la luminosité
        if (brightness <= 0) {
            brightness = 0;
            increasing = true; // Recommencer à augmenter
        }
    }

    // Appliquer la luminosité à toutes les LEDs
    for (int i = 0; i < numLeds; i++) {
        leds[i] = CRGB::Blue;
        leds[i].fadeToBlackBy(255 - brightness); // Ajuste la luminosité
    }

    FastLED.show();
}

void LEDController::update_good() {
    // Variable de luminosité (de 0 à 255)
    static uint8_t brightness = 0;
    static bool increasing = true; // Indique si la luminosité augmente ou diminue

    // Mettre à jour la luminosité progressivement
    if (increasing) {
        brightness += 5; // Augmente la luminosité (ajustez la valeur pour la vitesse)
        if (brightness >= 255) {
            brightness = 255;
            increasing = false; // Commencer à diminuer
        }
    } else {
        brightness -= 5; // Diminue la luminosité
        if (brightness <= 0) {
            brightness = 0;
            increasing = true; // Recommencer à augmenter
        }
    }

    // Appliquer la luminosité à toutes les LEDs
    for (int i = 0; i < numLeds; i++) {
        leds[i] = CRGB::Green;
        leds[i].fadeToBlackBy(255 - brightness); // Ajuste la luminosité
    }

    FastLED.show();
}




