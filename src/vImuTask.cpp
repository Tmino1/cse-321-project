/**
 * This is the ImuTask, its only purpose is to read from the Imu and filter out any noise
 */
#include "tasks.h"
#include "imu.h"

int16_t ax, ay, az;     // these variables represent the accelerometer's RAW axis measurments, which is the force and acceleration along that axis, and sort of resembles its rotational position 
int16_t gx, gy, gz;     // these variables represent the gyroscope's RAW axis measurements, which is the rotational velocity around that axis

//these variables represent the IMU measurements after being filtered
int16_t filtered_ax, filtered_ay, filtered_az;
int16_t filtered_gx, filtered_gy, filtered_gz;


// we can also initialize our dataQueue which is used for sharing values with other tasks
QueueHandle_t dataQueue = xQueueCreate(7, sizeof(int16_t));




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
        
        /* now all we need to do is filter out the values the imu measured by basically "accepting" only a fraction of the newly measured data. This means for example, our filtered
        * value x = (75% of the old value) + (25% of the new value)
        *
        * 
        * This approach creates what's called a software low pass filter, where low frequency waves are let through but higher frequency waves are blocked off
        * 
        * In our scenario with our IMU, the high frequency waves come from the unstable and erratic behavior in the IMU's RAW readings
        */

        
        filtered_ax = 0.75*filtered_ax + 0.25*ax;
        filtered_ay = 0.75*filtered_ay + 0.25*ay;
        filtered_az = 0.75*filtered_az + 0.25*az;

        filtered_gx = 0.75*filtered_gx + 0.25*gx;
        filtered_gy = 0.75*filtered_gy + 0.25*gy;
        filtered_gz = 0.75*filtered_gz + 0.25*gz;


        // for testing purposes
        Serial.println();
        Serial.printf("ax: %6d  ay: %6d  az: %6d\n", filtered_ax, filtered_ay, filtered_az);
        Serial.println();
        Serial.printf("gx: %6d  gy: %6d  gz: %6d", filtered_gx, filtered_gy, filtered_gz);
        Serial.println();
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}