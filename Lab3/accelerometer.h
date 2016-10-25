#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "lis3dsh.h"
#include "math.h"

typedef struct {
	float x; 
	float y; 
	float z;
} accelerometerValues;

void accelerometerInit(void);
void updateAccelerometerValues(float newX, float newY, float newZ);

#endif