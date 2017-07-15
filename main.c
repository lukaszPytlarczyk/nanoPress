/*
 * main.c
 *
 *  Created on: 15 lip 2017
 *      Author: GW
 */
#include <stdio.h>
#include <inttypes.h>
#include "drivers.h"
#include "LPS22HD.h"


uint8_t buffer[3];

lps_gpio_t lps_gpio = {	.SCL=11 , .SDA=12 ,.SA0=13 ,.INT_DRDY=14};

int main(){

	printf("TEST START\n");

	lps_init(&lps_gpio);

	printf("TEST END\n");
	return 0;
}
