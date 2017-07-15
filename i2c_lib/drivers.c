/**
 * @file    drivers.c
 * @Author  Paweł Kaźmierzewski <p.kazmierzewski@inteliclinic.com>
 * @date    May, 2017
 * @brief   Brief description
 *
 * Description
 */

#include <stdint.h>
#include <stdio.h>

#include "drivers.h"

#define DBG_PRINT(format, ...) do{\
  printf("[%s]: "format"\n", __func__, ##__VA_ARGS__); \
}while(0);

#define DBG_PRINTF(format) do{\
  printf("[%s]: "format"\n", __func__); \
}while(0);

//__attribute__((weak)) e_i2cReturn i2c_readData(s_i2cInput *input, vf_i2cCallback callback){
e_i2cReturn i2c_readData(s_i2cInput *input, vf_i2cCallback callback){
  char _string_buffer[1000];
  int _string_buffer_ptr = 0;
  if(input == NULL || callback == NULL){
    DBG_PRINTF("Input Error!");
    return I2C_INPUT_ERROR;
  }
  DBG_PRINT("I2C device address: 0x%02X", input->addr);
  DBG_PRINT("I2C device register: 0x%02X", input->reg);
  DBG_PRINT("I2C device len: %d", input->len);
  for (size_t i=0; i<input->len; i++){
	input->buf[i] = 0xFF&i;
    int _string_buffer_ptr_delta = snprintf(&_string_buffer[_string_buffer_ptr], sizeof(_string_buffer) - _string_buffer_ptr,"0x%02X ", 0xFF&input->buf[i]);
    _string_buffer_ptr += _string_buffer_ptr_delta;
  }
  DBG_PRINT("I2C device buffer: %s", _string_buffer);

  callback(true);
  return I2C_SUCCESS;
}

e_i2cReturn i2c_writeData(s_i2cInput *input, vf_i2cCallback callback){
  char _string_buffer[1000];
  int _string_buffer_ptr = 0;
  if(input == NULL || callback == NULL){
    DBG_PRINTF("Input Error!");
    return I2C_INPUT_ERROR;
  }
  DBG_PRINT("I2C device address: 0x%02X", input->addr);
  DBG_PRINT("I2C device register: 0x%02X", input->reg);
  DBG_PRINT("I2C device len: %d", input->len);
  for (size_t i=0; i<input->len; i++){
//    input->buf[i] = 0xFF&i;
    int _string_buffer_ptr_delta = snprintf(&_string_buffer[_string_buffer_ptr], sizeof(_string_buffer) - _string_buffer_ptr,"0x%02X ", 0xFF&input->buf[i]);
    _string_buffer_ptr += _string_buffer_ptr_delta;
  }
  DBG_PRINT("I2C device buffer: %s", _string_buffer);

  callback(true);
  return I2C_SUCCESS;
}

__attribute__((weak)) e_i2cReturn i2c_readData_blocking(s_i2cInput *input){
  char _string_buffer[1000];
  int _string_buffer_ptr = 0;
  if(input == NULL){
    DBG_PRINTF("Input Error!");
    return I2C_INPUT_ERROR;
  }
  DBG_PRINT("I2C device address: 0x%02X", input->addr);
  DBG_PRINT("I2C device register: 0x%02X", input->reg);
  DBG_PRINT("I2C device len: %d", input->len);
  for (size_t i=0; i<input->len; i++){
	input->buf[i] = 0xFF&i;
    int _string_buffer_ptr_delta = snprintf(&_string_buffer[_string_buffer_ptr], sizeof(_string_buffer) - _string_buffer_ptr,"0x%02X ", 0xFF&input->buf[i]);
    _string_buffer_ptr += _string_buffer_ptr_delta;
  }
  DBG_PRINT("I2C device buffer: %s", _string_buffer);

  return I2C_SUCCESS;
}

 e_i2cReturn i2c_writeData_blocking(s_i2cInput *input){
  char _string_buffer[1000];
  int _string_buffer_ptr = 0;
  if(input == NULL){
    DBG_PRINTF("Input Error!");
    return I2C_INPUT_ERROR;
  }
  DBG_PRINT("I2C device address: 0x%02X", input->addr);
  DBG_PRINT("I2C device register: 0x%02X", input->reg);
  DBG_PRINT("I2C device len: %d", input->len);
  for (size_t i=0; i<input->len; i++){
    input->buf[i] = 0xFF&(char)(-i);
    int _string_buffer_ptr_delta = snprintf(&_string_buffer[_string_buffer_ptr], sizeof(_string_buffer) - _string_buffer_ptr,"0x%02X ", 0xFF&input->buf[i]);
    _string_buffer_ptr += _string_buffer_ptr_delta;
  }
  DBG_PRINT("I2C device buffer: %s", _string_buffer);

  return I2C_SUCCESS;
}

