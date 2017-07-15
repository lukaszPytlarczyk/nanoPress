/*
 * LPS22HD.h
 *
 *  Created on: 15 lip 2017
 *      Author: Lukasz Pytlarczyk
 */

#ifndef LPS22HD_LPS22HD_H_
#define LPS22HD_LPS22HD_H_

typedef struct {
	int SCL; /*!< SCL pin number */
	int SDA;      /*!< SDA pin number */
	int SA0;      /*!< SA0 pin number */
	int INT_DRDY; /*!< INT_DDRY pin number */
}lps_gpio_t;

void lps_init(lps_gpio_t *lps_gpio);
int lps_run(void);


#endif /* LPS22HD_LPS22HD_H_ */
