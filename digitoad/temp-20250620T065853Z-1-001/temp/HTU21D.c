#include "HTU21D.h"

// Initialize the HTU21D
void HTU21D_Init(HTU21D_HandleTypeDef *htu21d, I2C_HandleTypeDef *i2c_handle) {
    htu21d->i2c_handle = i2c_handle;
    HTU21D_Reset(htu21d); // Perform a reset during initialization
}

// Reset the sensor
void HTU21D_Reset(HTU21D_HandleTypeDef *htu21d) {
    uint8_t command = SOFT_RESET;
    HAL_I2C_Master_Transmit(htu21d->i2c_handle, HTU21D_ADDRESS, &command, 1, HAL_MAX_DELAY);
    HAL_Delay(15); // Wait for the reset to complete
}

// Read temperature
float HTU21D_ReadTemperature(HTU21D_HandleTypeDef *htu21d) {
    uint8_t command = TRIGGER_TEMP_MEASURE_NOHOLD;
    uint8_t data[3]; // Two data bytes + CRC
    HAL_I2C_Master_Transmit(htu21d->i2c_handle, HTU21D_ADDRESS, &command, 1, HAL_MAX_DELAY);
    HAL_Delay(50); // Measurement time
    HAL_I2C_Master_Receive(htu21d->i2c_handle, HTU21D_ADDRESS, data, 3, HAL_MAX_DELAY);

    // Combine bytes
    uint16_t raw_temp = (data[0] << 8) | data[1];
    raw_temp &= 0xFFFC; // Clear the status bits

    // Convert to temperature
    return -46.85 + (175.72 * raw_temp) / 65536.0;
}

// Read humidity
float HTU21D_ReadHumidity(HTU21D_HandleTypeDef *htu21d) {
    uint8_t command = TRIGGER_HUMD_MEASURE_NOHOLD;
    uint8_t data[3]; // Two data bytes + CRC
    HAL_I2C_Master_Transmit(htu21d->i2c_handle, HTU21D_ADDRESS, &command, 1, HAL_MAX_DELAY);
    HAL_Delay(50); // Measurement time
    HAL_I2C_Master_Receive(htu21d->i2c_handle, HTU21D_ADDRESS, data, 3, HAL_MAX_DELAY);

    // Combine bytes
    uint16_t raw_humidity = (data[0] << 8) | data[1];
    raw_humidity &= 0xFFFC; // Clear the status bits

    // Convert to humidity
    return -6.0 + (125.0 * raw_humidity) / 65536.0;
}
