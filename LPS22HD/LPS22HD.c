/*
 * LPS22HD.c
 *
 *  Created on: 15 lip 2017
 *      Author: Lukasz Pytlarczyk
 */

#include "LPS22HD.h"
#include "drivers.h"
#include "gpio.h"
#include <stdio.h>


#define NANO_ADR 0xaa
char buff[10];

static void i2c_readClbk(bool b){
  printf("I2C read done with ret: %s\n", b?"true":"false");
}


void lps_init(lps_gpio_t *lps_gpio){
	gpio_setAlternateI2C(lps_gpio->SCL);
	gpio_setAlternateI2C(lps_gpio->SDA);
	gpio_setOut(lps_gpio->SA0);
	gpio_setL(lps_gpio->SA0);
	gpio_setEXTI(lps_gpio->INT_DRDY);

	s_i2cInput i2c_1 = {.addr = 0xaa, .buf = buff, .len=sizeof(buff), .reg= 15};
	i2c_readData(&i2c_1, i2c_readClbk);
}

int lps_run(void){


	return 0;
}
