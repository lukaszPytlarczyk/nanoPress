/*
 * gpio.c
 *
 *  Created on: 15 lip 2017
 *      Author: Lukasz Pytlarczyk
 */

#include <stdio.h>
#include "gpio.h"

void gpio_setIn(int pin){
	printf("PIN %d set as input\n",pin);
}

void gpio_setOut(int pin){
	printf("PIN %d set as output\n",pin);
}

void gpio_setH(int pin){
	printf("PIN %d set HIGH\n",pin);
}

void gpio_setL(int pin){
	printf("PIN %d set LOW\n",pin);
}

void gpio_setAlternateI2C(int pin){
	printf("PIN %d set as alternate I2C\n",pin);
}

void gpio_setEXTI(int pin){
	printf("PIN %d set as EXTI interrupt\n",pin);
}
