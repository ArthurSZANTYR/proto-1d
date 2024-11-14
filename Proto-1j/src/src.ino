#include "./led/led.h"
#include "FastIMU.h"
#include <Wire.h>

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

// Configuration IMU
#define IMU_ADDRESS 0x68
MPU6050 IMU;
calData calib = {0};
AccelData accelData;

#define STEP_THRESHOLD 0.48  // Seuil pour détecter un pas
#define IMU_INTERVAL 50  // Intervalle de lecture IMU (ms)

// Variables pour la détection des pas
int stepCount = 0;
float previousMagnitude = 0;

// Variables pour gérer le temps
unsigned long previousMillisLEDs = 0;
unsigned long previousMillisIMU = 0;


void setup() {
    Serial.begin(115200);

    Wire.begin(1, 2);
    Wire.setClock(400000);

    // Initialisation IMU
    int err = IMU.init(calib, IMU_ADDRESS);
    if (err != 0) {
        Serial.print("Erreur d'initialisation IMU: ");
        Serial.println(err);
        while (true) {}
    }

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

   // Lecture IMU et détection des pas
    if (currentMillis - previousMillisIMU >= IMU_INTERVAL) {
        previousMillisIMU = currentMillis;

        IMU.update();
        IMU.getAccel(&accelData);

        // Calcul du vecteur total d'accélération
        float magnitude = sqrt(sq(accelData.accelX) + sq(accelData.accelY) + sq(accelData.accelZ));

        // Détection de variation significative (pas)
        if (abs(magnitude - previousMagnitude) > STEP_THRESHOLD) {
            stepCount++;
            Serial.print("Pas détecté! Nombre de pas: ");
            Serial.println(stepCount);
        }

        previousMagnitude = magnitude;
    }

}
