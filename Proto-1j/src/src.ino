#include "./led/led.h"

// Définir les constantes
#define NUM_LEDS 9
#define LED_PIN 0

int mode = 1;
//1 - fraction
//2 - longrun
//3 - finisher

// Intervalles de temps pour chaque tâche (en millisecondes)
long intervalLEDs;     // Intervalle pour l'animation des LEDs

// Objets
LEDController ledController(LED_PIN, NUM_LEDS);

// Variables pour gérer le temps
unsigned long previousMillisLEDs = 0;

void setup() {
    Serial.begin(115200);

    if (mode == 1) {
        intervalLEDs = 100;
    }
    if (mode == 2) {
        intervalLEDs = 15;
    }

    ledController.init(); // Initialisation des LEDs
}

void loop() {
    unsigned long currentMillis = millis();

    // Mettre à jour les LEDs à intervalle régulier
    if (currentMillis - previousMillisLEDs >= intervalLEDs) {
        previousMillisLEDs = currentMillis;
        
      if (mode == 1) {
          ledController.update_fraction();
      }
      if (mode == 2) {
          ledController.update_longrun();
      }
    }

}
