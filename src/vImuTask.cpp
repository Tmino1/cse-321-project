/**
 * This is the ImuTask, its only purpose is to read from the Imu and filter out any noise
 */
#include "tasks.h"
#include "imu.h"

int16_t ax, ay, az;     // these variables represent the accelerometer's axis measurments, which is the force and acceleration along that axis
int16_t gx, gy, gz;     // these variables represent the gyroscope's axis measurements, which is the rotational velocity around that axis

//these variables represent the IMU measurements anfter being filtered
int16_t filtered_ax, filtered_ay, filtered_az;
int16_t filtered_gx, filtered_gy, filtered_gz;


/*Based on the measurements az and gz are likely the variables that'll mainly be focused on when keeping our robot balanced*/


void vImuTask(void *pvParameters){

    //this section basically gets the initial readings and sets the filtered variables to them
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    filtered_ax = ax;
    filtered_ay = ay;
    filtered_az = az;

    filtered_gx = gx;
    filtered_gy = gy;
    filtered_gz = gz;

    while(1){
        mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);   //this line basically reads the imu's raw measurement values and puts them in their repsective variables
        
        //now all we need to do is filter out the values the imu measured by basically ...
        
        filtered_ax = 0.75*filtered_ax + 0.25*ax;
        filtered_ay = ay;
        filtered_az = az;

        filtered_gx = gx;
        filtered_gy = gy;
        filtered_gz = gz;


        // for testing purposes
        Serial.println();
        Serial.printf("ax: %6d  ay: %6d  az: %6d\n", ax, ay, az);
        Serial.println();
        Serial.printf("gx: %6d  gy: %6d  gz: %6d", gx, gy, gz);
        Serial.println();
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}