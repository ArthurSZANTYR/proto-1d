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
GyroData gyroData;
MagData magData;

// Variables pour gérer le temps
unsigned long previousMillisLEDs = 0;

unsigned long previousMillisIMU = 0;
const long imuInterval = 50; // Fréquence de lecture IMU

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

    // Lecture IMU sans delay
    if (currentMillis - previousMillisIMU >= imuInterval) {
        previousMillisIMU = currentMillis;

        IMU.update();
        IMU.getAccel(&accelData);
        Serial.print(accelData.accelX); Serial.print("\t");
        Serial.print(accelData.accelY); Serial.print("\t");
        Serial.println(accelData.accelZ);

        IMU.getGyro(&gyroData);
        Serial.print(gyroData.gyroX); Serial.print("\t");
        Serial.print(gyroData.gyroY); Serial.print("\t");
        Serial.println(gyroData.gyroZ);

        if (IMU.hasMagnetometer()) {
            IMU.getMag(&magData);
            Serial.print(magData.magX); Serial.print("\t");
            Serial.print(magData.magY); Serial.print("\t");
            Serial.println(magData.magZ);
        }
    }

}
