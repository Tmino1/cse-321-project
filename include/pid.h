/*
* PID controller header file
* 
* This file contains the declarations for the PID controller functions and variables.
* It is used to control the speed and position of a motor using feedback from sensors.
*
* Owner: Travis
*/

// PID controller parameters
extern float clamp_min; // Minimum output value
extern float clamp_max; // Maximum output value

extern int64_t pid_task_period_ms; // Period of the PID task in milliseconds

// Helper functions for the PID controller task
float get_effort(float error, float dt); // Calculate the PID effort based on the error and time delta

float get_dt(void); // Get the time delta since the last call in seconds

float get_error(void); // Get the current error value (to be defined elsewhere)