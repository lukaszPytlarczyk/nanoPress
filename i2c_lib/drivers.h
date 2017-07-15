/**
 * @file    drivers.h
 * @Author  Paweł Kaźmierzewski <p.kazmierzewski@inteliclinic.com>
 * @date    May, 2017
 * @brief   Brief description
 *
 * Description
 */

#ifndef DRIVERS_H
#define DRIVERS_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief i2c input type
 */
typedef struct{
  char    addr; /*!< device address */
  char    reg;  /*!< target register */
  char    *buf; /*!< transaction buffer, at least @ref len sized */
  size_t  len;  /*!< size of data to be read */
}s_i2cInput;

/**
 * @enum return value of i2c peripheral driver
 */
typedef enum{
  I2C_SUCCESS = 0x00, /*!< everything went ok */
  I2C_BUSY,           /*!< driver is used in other scope */
  I2C_INPUT_ERROR,    /*!< input argumetns are wrong */
  I2C_ERROR           /*!< driver is unusable */
}e_i2cReturn;

/**
 * @brief finished transaction callback
 *
 */
typedef void(*vf_i2cCallback)(bool);

/**
 * @brief Reading data through i2c interface
 *
 * @param[in] input     @ref s_i2cInput
 * @param[in] callback  function called after finished transaction. False argument value means
 *                      something went wrong
 *
 * @return @ref e_i2cReturn
 */
e_i2cReturn i2c_readData(s_i2cInput *input, vf_i2cCallback callback);

/**
 * @brief Writting data through i2c interface
 *
 * @param[in] input     @ref s_i2cInput
 * @param[in] callback  function called after finished transaction. False argument value means
 *                      something went wrong
 *
 * @return @ref e_i2cReturn
 */
e_i2cReturn i2c_writeData(s_i2cInput *input, vf_i2cCallback callback);

/**
 * @brief Reading data through i2c interface using blocking method
 *
 * function won't end until interface finishes transaction
 *
 * @param[in] input     @ref s_i2cInput
 *
 * @return @ref e_i2cReturn
 */
e_i2cReturn i2c_readData_blocking(s_i2cInput *input);

/**
 * @brief Writting data through i2c interface using blocking method
 *
 * function won't end until interface finishes transaction
 *
 * @param[in] input     @ref s_i2cInput
 *
 * @return @ref e_i2cReturn
 */
e_i2cReturn i2c_writeData_blocking(s_i2cInput *input);

#endif /* !DRIVERS_H */
