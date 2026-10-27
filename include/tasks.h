/*
 * tasks.h 	- All tasks present in the project defined here with their parameters.
 * owner	- Both
 */


#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/idf_additions.h"



/*---- Tasks ----*/

/* owner: 	TODO
 * file:  	empty
 * does: 	Reads the IMU and filters the data to remove bad data points.
 */ 
void vImuTask(void *pvParameters);

/* owner: 	TODO
 * file:  	TODO 
 * does: 	Implements a PID controller to calculate the effort to stay "upright" from the latest filtered IMU readings.
 */
void vPidTask(void *pvParameters);

/* owner: 	TODO
 * file:  	TODO 
 * does: 	Tracks several statuses of the robot as it runs, such as battery voltage and Imu status etc
 */
void vSupervisorTask(void *pvParameters);

/* owner: 	TODO
 * file:  	TODO 
 * does: 	Logs the current state of the robot to printf
 */
void vLogTask(void *pvParameters);
 
