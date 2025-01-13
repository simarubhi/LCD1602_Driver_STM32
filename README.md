# LCD 1602 Driver library for the  module for STM32

![DHT11](https://img.shields.io/badge/Module-DHT11-blue)
![STM32](https://img.shields.io/badge/Microcontroller-STM32-white)
![Project Status](https://img.shields.io/badge/Project-Finished-brightgreen)

Driver library for the LCD 1602 module for STM32 microcontrollers

## Usage

### STM32 CubeIDE & Code Setup
1. Enable I2C connectivity ([Wiki Tutorial](https://wiki.st.com/stm32mcu/wiki/Getting_started_with_I2C#I-settings))
2. Save/Generate Code
3. Connect 5V, GND, SCL, and SDA to LCD
4. In lcd_1602_driver.h set LCD_ADDRESS to the correct address for your specific LCD 1602 module (Be mindful of bit shift)
5. In lcd_1602_driver.h set "stm32f4xx_hal.h" to the correct STM32 board you are using
6. Implement Code
7. (Optional) Consult datasheet to change init_lcd_function to change things like column count. Note different modals will have different features and functions.

### Code Implementation
```c
#include "lcd_1602_driver.h"

...

I2C_HandleTypeDef hi2c1; // Usually auto-generated

...

int main(void)
{
  ...

  // Initalization
  init_lcd(&hi2c1);
  set_lcd_cursor(0, 0);
  send_lcd_string("Initializing..."); 
  HAL_Delay(2000);
  clear_lcd();

  ...

  while (1)
  {
    ...

    // Example test usage
    set_lcd_cursor(0, 0);
    send_lcd_string("Hello World");
    HAL_Delay(5000);
    clear_lcd();

    set_lcd_cursor(0, 0);
    send_lcd_string("Top Row Here");
    set_lcd_cursor(1, 0);
    send_lcd_string("Bottom Row");
    HAL_Delay(5000);
    clear_lcd();
    
    ...
  }

}
```

## Documentation
![Wiring Diagram](https://github.com/simarubhi/LCD1602_Driver_STM32/blob/main/docs/lcd_1602.jpg)

Datasheets for the LCD 1602:
* https://www.waveshare.com/datasheet/LCD_en_PDF/LCD1602.pdf
* https://www.openhacks.com/uploadsproductos/eone-1602a1.pdf
