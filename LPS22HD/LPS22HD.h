/*
 * LPS22HD.h
 *
 *  Created on: 15 lip 2017
 *      Author: Lukasz Pytlarczyk
 */

#ifndef LPS22HD_LPS22HD_H_
#define LPS22HD_LPS22HD_H_

#define LPS_INTERRUPT_CFG 0x0B
#define LPS_INT_SOURCE 0x25
#define LPS_CTRL_REG1 0x10
#define LPS_CTRL_REG2 0x11
#define LPS_CTRL_REG3 0x12

#define LPS_PRESS_OUT_XL 0x28
#define LPS_PRESS_OUT_L 0x29
#define LPS_PRESS_OUT_H 0x2A

#define LPS_TEMP_OUT_L 0x2B
#define LPS_TEMP_OUT_H 0x2C



typedef struct {
	int SCL; /*!< SCL pin number */
	int SDA;      /*!< SDA pin number */
	int SA0;      /*!< SA0 pin number */
	int INT_DRDY; /*!< INT_DDRY pin number */
}lps_gpio_t;

typedef enum {
	lps_state_idle = 0,
	lps_state_shoot = 1 ,
	lps_state_wait = 2,
	lps_state_readWait = 3
} lps_state_en ;

void lps_init(lps_gpio_t *lps_gpio);
int lps_run(void);
void lps_startRun(void);
void lps_stopRun(void);


#endif /* LPS22HD_LPS22HD_H_ */
