#ifndef IMU_H
#define IMU_H

#include "FastIMU.h"

class IMU {
public:
    IMU(uint8_t address);
    void init();
    void readData();
private:
    MPU6050 imu;
    AccelData accelData;
    GyroData gyroData;
    uint8_t imuAddress;
};

#endif