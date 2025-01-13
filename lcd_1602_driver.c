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
void init_lcd(I2C_HandleTypeDef *hi2c)
{
	phi2c1 = hi2c;

	HAL_Delay(25);
	send_command(0x30);
	HAL_Delay(6);
	send_command(0x30);
	HAL_Delay(1);
	send_command(0x30);

	HAL_Delay(5);
	send_command(0x20); // 4 Bit

	HAL_Delay(5);
	send_command(0x2C); // Function set

	HAL_Delay(5);
	send_command(0x08); // Display, cursor, blink, off

	HAL_Delay(5);
	send_command(0x01); // Clear

	HAL_Delay(5);
	send_command(0x0C); // Display On, cursor & blink off
}


void send_command(uint8_t cmd)
{
	uint8_t upper_data, lower_data;

	upper_data = cmd & 0xf0; // 0xf0 -> 1111 0000, this gives first 4 bits
	lower_data = (cmd << 4) & 0xf0; // gives last four bits

	uint8_t transfer_data[4]; // 4
	transfer_data[0] = upper_data | 0x0C;
	transfer_data[1] = upper_data | 0x08;

	transfer_data[2] = lower_data | 0x0C;
	transfer_data[3] = lower_data | 0x08;

	HAL_I2C_Master_Transmit(phi2c1, LCD_ADDRESS, (uint8_t *)transfer_data, 4, HAL_MAX_DELAY);
}

void send_data(uint8_t data)
{
	uint8_t upper_data, lower_data;

	upper_data = data & 0xf0; // 0xf0 -> 1111 0000, this gives first 4 bits
	lower_data = (data << 4) & 0xf0; // gives last four bits

	uint8_t transfer_data[4]; // 4

	transfer_data[0] = upper_data | 0x0D;
	transfer_data[1] = upper_data | 0x09;

	transfer_data[2] = lower_data | 0x0D;
	transfer_data[3] = lower_data | 0x09;

	HAL_I2C_Master_Transmit(phi2c1, LCD_ADDRESS, (uint8_t *)transfer_data, 4, HAL_MAX_DELAY);
}

void send_string(char *str)
{
	for (char *p = str; *p != '\0'; p++) {
		send_data(*p);
	}
}

void set_cursor(uint8_t row, uint8_t col)
{
    // Base addresses for rows: 0x80 for row 0, 0xC0 for row 1, (0-1) rows and (0-15) columns
	uint8_t base_address = (row == 0) ? 0x80 : 0xC0;
    send_command(base_address + col);
}

void clear_display(void)
{
    send_command(0x01);
	HAL_Delay(2);
}





