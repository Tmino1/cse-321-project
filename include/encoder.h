/*
* File: encoder.h
* Setup and reading of the encoders
* owner - Travis
*/

#include <stdint.h>
#include "driver/gpio.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"

// Function to setup the encoder driver and configure the GPIO pins for the encoders
void setupEncoderDriver();

// Interrupt handlers for reading the encoder pulses
static void leftEncoderPulse(void *unused);
static void rightEncoderPulse(void *unused);