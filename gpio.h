/*
 * gpio.h
 *
 *  Created on: 15 lip 2017
 *      Author: GW
 */

#ifndef GPIO_H_
#define GPIO_H_

void gpio_setIn(int pin);
void gpio_setOut(int pin);
void gpio_setH(int pin);
void gpio_setL(int pinh);
void gpio_setAlternateI2C(int pin);
void gpio_setEXTI(int pin);

#endif /* GPIO_H_ */
