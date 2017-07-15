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
#include <inttypes.h>

#define DBG_PRINT(format, ...) do{\
  printf("[%s]: "format"\n", __func__, ##__VA_ARGS__); \
}while(0);

#define DBG_PRINTF(format) do{\
  printf("[%s]: "format"\n", __func__); \
}while(0);

#define LPS22HD_ADR_R 0xb9
#define LPS22HD_ADR_W 0xb8

char buff[10];
int lps_dataRdy = 0;
int lps_readDone = 0;
lps_state_en lps_state = lps_state_idle;
int lps_stopFlag = 0;

float lps_pressure = 0.0;
int lps_temperature = 0.0;

/**
 * Callback nieblokuj�cej funkcji odczytu rejestr�w. U�ywany po
 * odczycoe rejestr�w z wynikami konwrsji.
 * @param b - okre�la czy odczyt si� powi�d�
 */
static void i2c_readClbk(bool b) {
	if (b) {
		lps_pressure = (float) ((uint32_t) buff[0] + (uint32_t) buff[1]
				<< 8 + (uint32_t) buff[2] << 16) / 4096.0;
		lps_temperature = (int) ((uint32_t) buff[3] + (uint32_t) buff[4] << 8);
		DBG_PRINT("LPS read done. Pressure: %f Temperature: %d \n", lps_pressure, lps_temperature);
//		printf("I2C read done with ret: %s\n", b ? "true" : "false");
		lps_readDone = 1;
	} else {
		lps_readDone = -1;
	}
}


/**
 * Callback nieblokuj�cej funkcji zapisu do rejestr�w
 * @param b - okre�la czy zapis si� powi�d�
 */
static void i2c_writeClbk(bool b) {
	DBG_PRINT("I2C write done with ret: %s\n", b ? "true" : "false");

}

s_i2cInput i2c_1 = { .addr = LPS22HD_ADR_W, .buf = buff, .len = 1, .reg =
LPS_CTRL_REG3 };

/**
 * inicjalizacja modu�u
 * @param lps_gpio - konfiguracja hardware
 */
void lps_init(lps_gpio_t *lps_gpio) {
	gpio_setAlternateI2C(lps_gpio->SCL);
	gpio_setAlternateI2C(lps_gpio->SDA);
	gpio_setOut(lps_gpio->SA0);
	gpio_setL(lps_gpio->SA0);
	gpio_setEXTI(lps_gpio->INT_DRDY);

	i2c_1.reg = LPS_CTRL_REG3;
	buff[0] = 0x04;  // DRDY
	i2c_writeData_blocking(&i2c_1);

	i2c_1.reg = LPS_INT_SOURCE;
	buff[0] = 0x04; //Interrupt active
	i2c_writeData_blocking(&i2c_1);

//	i2c_readData(&i2c_1, i2c_readClbk);
}

/**
 * W��cza cykliczny odczyt z modu�u.
 */
void lps_startRun(void) {
	lps_state = lps_state_shoot;
}

/**
 * W��cza cykliczny odczyt z modu�u.
 */
void lps_stopRun(void) {
	DBG_PRINT("Stop reading LPS");
	lps_stopFlag = 1;

}

/**
 * funkcja wewn�trzna. Zapis do rejestru, rozpoczynaj�cy konwersje.
 */
void lps_oneShotTrigger(void) {
	DBG_PRINT("Trig connversion");
	i2c_1.reg = LPS_CTRL_REG1;
	i2c_1.len = 1;
	i2c_1.addr = LPS22HD_ADR_W;
	buff[0] = 0x01; //DIFF_EN
	i2c_writeData(&i2c_1,i2c_writeClbk);
}

/**
 * Inicjalizacja odczytu z rejestr�w danych.
 */
void lps_readData(void) {
	i2c_1.addr = LPS22HD_ADR_R;
	i2c_1.len = 5;
	i2c_1.reg = LPS_PRESS_OUT_XL;
	i2c_readData(&i2c_1, i2c_readClbk);
}

/**
 * G��wna maszyna stan�w modu�u. Musi by� uruchamiana w g��wnym
 * w�tku aplikacji (g��wnej p�tli programu)
 * @retval 0 - ok
 * @retval -1 - b��d wykonywania. p�tla wraca do stanu pocz�tkowego
 */
int lps_run(void) {

	switch (lps_state) {
	case lps_state_idle:

		break;
	case lps_state_shoot:
		if(lps_stopFlag) {
			lps_state = lps_state_idle;
			break;
		}

		lps_oneShotTrigger();
		lps_state = lps_state_wait;
		break;
	case lps_state_wait:
		if (lps_dataRdy) {
			lps_dataRdy = 0;
			lps_readData();
			lps_state = lps_state_readWait;
		}
		break;
	case lps_state_readWait:
		if (lps_readDone == 1) {
			lps_readDone = 0;
			lps_state = lps_state_shoot;

		} else if (lps_readDone == -1) {
			lps_readDone = 0;
			lps_state = lps_state_idle;
			return -1;
		}

		break;
	default:
		break;
	}

	return 0;
}

/**
 * funkcja obs�ugi przerwania od EXTI (External Trigger).
 * W tym przypadku przerwanie wywo�ywane jest zmin� na stan wysoki:
 * Rejestr CTRL_REG3: INT_H_L=0 -> active high
 */
void EXTI_ISR(void) {
	lps_dataRdy = 1;
	//clear isr flag
}
