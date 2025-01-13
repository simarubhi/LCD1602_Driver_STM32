/**
 *  @file lcd_1602_driver.h
 *	@brief LCD 1602 Driver Library
 *  @date Created on: Jan 12, 2025
 *  @version 1.0.0
 *  @author Simar Singh Ubhi
 */

#ifndef INC_LCD_1602_DRIVER_H_
#define INC_LCD_1602_DRIVER_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"  // Include the HAL I2C header to define I2C_HandleTypeDef

#define LCD_ADDRESS (0x27 << 1) // I2C address for LCD module (changes depending on specific model, check data sheet or store)

/**
 * @brief Initializes the LCD in 4-bit mode.
 */
void init_lcd(I2C_HandleTypeDef *hi2c);

/**
 * @brief Sends a command to the LCD.
 * @param cmd Command to send
 */
void send_command(uint8_t cmd);

/**
 * @brief Sends a data byte (character) to the LCD.
 * @param data Data byte to send
 */
void send_data(uint8_t data);

/**
 * @brief Sends a string to the LCD.
 * @param str Pointer to the null-terminated string (\0)
 */
void send_string(char *str);

/**
 * @brief Sets the cursor to a specific position on the LCD.
 * @param row Row index (0 or 1)
 * @param col Column index (0 to 15)
 */
void set_cursor(uint8_t row, uint8_t col);

/**
 * @brief Clears the LCD display.
 */
void clear_display(void);

#endif /* INC_LCD_1602_DRIVER_H_ */
