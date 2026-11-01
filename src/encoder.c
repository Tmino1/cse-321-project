#include "encoder.h"

static volatile int32_t leftTicks = 0;
static volatile int32_t rightTicks = 0;
static portMUX_TYPE encoderLock = portMUX_INITIALIZER_UNLOCKED;

void setupEncoders(void){
    return;
}
void readEncoders(int32_t *left, int32_t *right){
    portENTER_CRITICAL(&encoderLock);
    *left = leftTicks;
    *right = rightTicks;
    portEXIT_CRITICAL(&encoderLock);
}