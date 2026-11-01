#include <Arduino.h>
#include "imu.h"
#include "tasks.h"

MPU6050 mpu;  //this is the object that represents our MPU6050 chip, we can use this to call functions to read from the chip and set offsets etc

void setup() {
    Wire.begin();
    Serial.begin(115200);
    while(!Serial);     //this simply waits for the Serial monitor to fully start up
    
    //we then need to initialize our mpu
    mpu.initialize();

    //we'll then simply test if our mpu has connected 
     
    Serial.println(F("Testing MPU6050 connection..."));
    
    if(mpu.testConnection() == false){
        Serial.println("MPU6050 connection failed");
        while(true);
    }
    else {
        Serial.println("MPU6050 connection successful");
    }

    //then we need to set our offsets for our MPU6050 chip, which were calculated reading a bunch of readings and finding the average
    mpu.setXGyroOffset(452);
    mpu.setYGyroOffset(145);
    mpu.setZGyroOffset(1);
    mpu.setXAccelOffset(-1041);
    mpu.setYAccelOffset(-14);
    mpu.setZAccelOffset(5106);



    //we can also create the ImuTask
    xTaskCreate(vImuTask, "ImuTask", 8192, NULL, 1, NULL);
}

void loop() {
    // keep empty
}
