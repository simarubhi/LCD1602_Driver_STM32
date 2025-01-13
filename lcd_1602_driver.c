/**
 *  @file lcd_1602_driver.c
 *	@brief LCD 1602 Driver Library
 *  @date Created on: Jan 12, 2025
 *  @author Author: Simar Singh Ubhi
 *  @version 1.0.0
 *
 */

#include "lcd_1602_driver.h"
#include <string.h>

//**********************Private Variables**********************//
static I2C_HandleTypeDef *phi2c1 = NULL;

//**********************Public API Functions**********************//
/**
 *	@brief initalization sequence to lcd and assign I2C handle for driver
 *  @param *hi2c the handle for the I2C lane chosen
 */
void init_lcd(I2C_HandleTypeDef *hi2c)
{
	phi2c1 = hi2c; // Assigning handle

    // Start sequence
	HAL_Delay(25);
	send_lcd_command(0x30);
	HAL_Delay(6);
	send_lcd_command(0x30);
	HAL_Delay(1);
	send_lcd_command(0x30);

	HAL_Delay(5);
	send_lcd_command(0x20); // 4 bit mode

	HAL_Delay(5);
	send_lcd_command(0x2C); // Function set

	HAL_Delay(5);
	send_lcd_command(0x08); // Display, cursor and blink, off

	HAL_Delay(5);
	send_lcd_command(0x01); // Clear display

	HAL_Delay(5);
	send_lcd_command(0x0C); // Display on. Cursor and blink off
}

/**
 *	@brief Send command to LCD, used for performing functions, clearing, setup, etc.
 *  @param cmd command byte to be sent
 */
void send_lcd_command(uint8_t cmd)
{
	uint8_t upper_data, lower_data;

	upper_data = cmd & 0xf0; // 0xf0 -> 1111 0000, this gives first 4 bits
	lower_data = (cmd << 4) & 0xf0; // Gives last four bits

	uint8_t transfer_data[4]; // 4 bytes of data

    // Data must be sent twice with bit 2 (enable) first = 1, then = 2 as described in datasheet
	transfer_data[0] = upper_data | 0x0C;
	transfer_data[1] = upper_data | 0x08;

	transfer_data[2] = lower_data | 0x0C;
	transfer_data[3] = lower_data | 0x08;

	HAL_I2C_Master_Transmit(phi2c1, LCD_ADDRESS, (uint8_t *)transfer_data, 4, HAL_MAX_DELAY); // Send command to LCD via I2C
}

/**
 *	@brief Send data to LCD, used for ASIC characters
 *  @param data data to be sent
 */
void send_lcd_data(uint8_t data)
{
	uint8_t upper_data, lower_data;

    upper_data = data & 0xf0; // 0xf0 -> 1111 0000, this gives first 4 bits
	lower_data = (data << 4) & 0xf0; // Gives last four bits

	uint8_t transfer_data[4]; // 4 bytes of data

    // Data must be sent twice with bit 2 (enable) first = 1, then = 2 as described in datasheet
	transfer_data[0] = upper_data | 0x0D;
	transfer_data[1] = upper_data | 0x09;

	transfer_data[2] = lower_data | 0x0D;
	transfer_data[3] = lower_data | 0x09;

	HAL_I2C_Master_Transmit(phi2c1, LCD_ADDRESS, (uint8_t *)transfer_data, 4, HAL_MAX_DELAY); // Send command to LCD via I2C
}

/**
 *	@brief Send a string to be displayed on LCD
 *  @param *str pointer to string
 */
void send_lcd_string(char *str)
{
    // Keep looping until the null-terminated string character reached indiating end of string
	for (char *p = str; *p != '\0'; p++) {
		send_lcd_data(*p); // Send each character
	}
}

/**
 *	@brief Set position of cursor on LCD
 *  @param row Row index (0 or 1)
 *  @param col Column index (0 to 15)
 */
void set_lcd_cursor(uint8_t row, uint8_t col)
{
    // Base addresses for rows: 0x80 for row 0, 0xC0 for row 1, (0-1) rows and (0-15) columns
	uint8_t base_address = (row == 0) ? 0x80 : 0xC0;
	send_lcd_command(base_address + col);
}

/**
 *	@brief Clears the LCD making it blank
 */
void clear_lcd(void)
{
	send_lcd_command(0x01);
	HAL_Delay(2);
}
