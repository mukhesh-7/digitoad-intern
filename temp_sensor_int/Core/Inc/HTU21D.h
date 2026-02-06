#ifndef HTU21D_H
#define HTU21D_H

#include "stm32l4xx_hal.h" // Include your specific HAL header file

// Define I2C address and commands
#define HTU21D_ADDRESS 0x40 << 1 // 7-bit address shifted for HAL
#define TRIGGER_TEMP_MEASURE_HOLD  0xE3
#define TRIGGER_HUMD_MEASURE_HOLD  0xE5
#define TRIGGER_TEMP_MEASURE_NOHOLD  0xF3
#define TRIGGER_HUMD_MEASURE_NOHOLD  0xF5
#define WRITE_USER_REG  0xE6
#define READ_USER_REG  0xE7
#define SOFT_RESET  0xFE

// User register resolution
#define USER_REGISTER_RESOLUTION_MASK 0x81
#define USER_REGISTER_RESOLUTION_RH12_TEMP14 0x00
#define USER_REGISTER_RESOLUTION_RH8_TEMP12 0x01
#define USER_REGISTER_RESOLUTION_RH10_TEMP13 0x80
#define USER_REGISTER_RESOLUTION_RH11_TEMP11 0x81

// Errors
#define ERROR_I2C_TIMEOUT 998
#define ERROR_BAD_CRC 999

typedef struct {
    I2C_HandleTypeDef *i2c_handle; // I2C handle
} HTU21D_HandleTypeDef;

// Public functions
void HTU21D_Init(HTU21D_HandleTypeDef *htu21d, I2C_HandleTypeDef *i2c_handle);
float HTU21D_ReadTemperature(HTU21D_HandleTypeDef *htu21d);
float HTU21D_ReadHumidity(HTU21D_HandleTypeDef *htu21d);
void HTU21D_Reset(HTU21D_HandleTypeDef *htu21d);

#endif // HTU21D_H
