/*
 * gpio.c
 *
 *  Created on: 15 lip 2017
 *      Author: Lukasz Pytlarczyk
 */

#include <stdio.h>
#include "gpio.h"

#define DBG_PRINT(format, ...) do{\
  printf("[%s]: "format"\n", __func__, ##__VA_ARGS__); \
}while(0);

#define DBG_PRINTF(format) do{\
  printf("[%s]: "format"\n", __func__); \
}while(0);

void gpio_setIn(int pin){
	DBG_PRINT("PIN %d set as input",pin);
}

void gpio_setOut(int pin){
	DBG_PRINT("PIN %d set as output",pin);
}

void gpio_setH(int pin){
	DBG_PRINT("PIN %d set HIGH",pin);
}

void gpio_setL(int pin){
	DBG_PRINT("PIN %d set LOW",pin);
}

void gpio_setAlternateI2C(int pin){
	DBG_PRINT("PIN %d set as alternate I2C",pin);
}

void gpio_setEXTI(int pin){
	DBG_PRINT("PIN %d set as EXTI interrupt",pin);
}
