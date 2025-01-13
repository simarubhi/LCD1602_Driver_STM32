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
 *	@brief initalization sequence to lcd and assign I2C handle for driver
 *  @param *hi2c the handle for the I2C lane chosen
 */
void init_lcd(I2C_HandleTypeDef *hi2c);

/**
 *	@brief Send command to LCD, used for performing functions, clearing, setup, etc.
 *  @param cmd command byte to be sent
 */
void send_lcd_command(uint8_t cmd);

/**
 *	@brief Send data to LCD, used for ASIC characters
 *  @param data data to be sent
 */
void send_lcd_data(uint8_t data);

/**
 *	@brief Send a string to be displayed on LCD
 *  @param *str pointer to string
 */
void send_lcd_string(char *str);

/**
 *	@brief Set position of cursor on LCD
 *  @param row Row index (0 or 1)
 *  @param col Column index (0 to 15)
 */
void set_lcd_cursor(uint8_t row, uint8_t col);

/**
 *	@brief Clears the LCD making it blank
 */
void clear_lcd(void);

#endif /* INC_LCD_1602_DRIVER_H_ */
