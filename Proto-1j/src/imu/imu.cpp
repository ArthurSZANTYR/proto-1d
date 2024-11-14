#include "imu.h"
#include <Wire.h>

IMU::IMU(uint8_t address) : imuAddress(address) {}

void IMU::init() {
    Serial.println("Initialisation IMU...");
    calData calib = {0};
    int err = imu.init(calib, imuAddress);
    
    if (err != 0) {
        Serial.print("Erreur d'initialisation IMU: ");
        Serial.println(err);
        delay(1000);  // Donne un peu de temps pour voir l'erreur
        while (true) {}  // Boucle infinie si l'initialisation échoue
    }
    
    Serial.println("IMU initialisé avec succès.");
}

void IMU::readData() {
    imu.update();
    imu.getAccel(&accelData);
    imu.getGyro(&gyroData);

    Serial.print("Accélération: ");
    Serial.print(accelData.accelX); Serial.print("\t");
    Serial.print(accelData.accelY); Serial.print("\t");
    Serial.println(accelData.accelZ);

    Serial.print("Gyroscope: ");
    Serial.print(gyroData.gyroX); Serial.print("\t");
    Serial.print(gyroData.gyroY); Serial.print("\t");
    Serial.println(gyroData.gyroZ);
}