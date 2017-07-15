/*
 * main.c
 *
 *  Created on: 15 lip 2017
 *      Author: Lukasz Pytlarczyk
 */
#include <stdio.h>
#include <inttypes.h>
#include "drivers.h"
#include "LPS22HD.h"



lps_gpio_t lps_gpio = {	.SCL=11 , .SDA=12 ,.SA0=13 ,.INT_DRDY=14};


/**
 * Modu³ testuj¹cy.
 * @return
 */
int main(){

	printf("TEST START\n");

	int i, loopCnt = 70;
	lps_init(&lps_gpio);
	lps_startRun();

	for(i=1;i<loopCnt;i++) {
		printf("time: %d\n",i);
		if(lps_run()==-1) {
			printf("LPS read error. ABORT\n");
		}
		if(i%10==0) {
			EXTI_ISR(); // symulacja przerwania
			printf("ISR simulation\n");
		}
		if(i%47==0) {
			lps_stopRun();
			break;
		}
	}

	printf("TEST END\n");
	return 0;
}
