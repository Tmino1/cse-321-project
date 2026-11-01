#include <pid.h>
#include <Arduino.h>
#include <config.h>
#include <task.h>
#include <FreeRTOS.h>

float previous_error = 0.0; // Store the previous error for derivative calculation

float get_effort(float error, float dt) {
    // Implementation for calculating PID efforts
    float effort = 0.0;

    float integral = error * dt; // Integral term
    float derivative = (error - previous_error) / dt; // Derivative term
    
    float ep = error * KP; // Proportional term
    float ei = integral * KI; // Integral term
    float ed = derivative * KD; // Derivative term  

    effort = ep + ei + ed; // Total effort

    previous_error = error; // Update the previous error for the next iteration

    // Clamp the effort to the specified range
    if (effort < clamp_min) {
        effort = clamp_min;
    } else if (effort > clamp_max) {
        effort = clamp_max;
    }

    return effort;
}

float get_dt(void) {
    static int64_t previous_time = 0;
    int64_t nowtime = esp_timer_get_time();

    if (previous_time == 0) {
        previous_time = nowtime;
        return 0.0f;  // No previous call yet.
    }

    float dt = (nowtime - previous_time) / 1000000.0f;
    previous_time = nowtime;

    return dt;  // Seconds.
}

float get_error(void) {
    // Placeholder for getting the current error value
    // This function should be defined elsewhere to provide the actual error value
    return 0.0f; // Replace with actual error calculation
}

void vPidTask(void *pvParameters) {
    float dt = 0.0f;
    float error = 0.0f;
    float effort = 0.0f;
    for (;;) {
        vtaskDelay(pdMS_TO_TICKS(pid_task_period_ms));
        dt = get_dt();
        error = get_error(); // This function should be defined elsewhere to get the current error
        effort = get_effort(error, dt);
    }
}
