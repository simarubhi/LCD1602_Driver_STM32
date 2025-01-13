# LCD 1602 Driver library for the  module for STM32

![DHT11](https://img.shields.io/badge/Module-DHT11-blue)
![STM32](https://img.shields.io/badge/Microcontroller-STM32-white)
![Project Status](https://img.shields.io/badge/Project-Finished-brightgreen)

Driver library for the LCD 1602 module for STM32 microcontrollers

_Instructions In Progress..._

## Usage

### STM32 CubeIDE & Code Setup
1. Enable I2C connectivity ([Wiki Tutorial](https://wiki.st.com/stm32mcu/wiki/Getting_started_with_I2C#I-settings))
2. Save/Generate Code
3. Connect 5V, GND, SCL, and SDA to LCD
4. In lcd_1602_driver.h set LCD_ADDRESS to the correct address for your specific LCD 1602 module (Be mindful of bit shift)
5. In lcd_1602_driver.h set "stm32f4xx_hal.h" to the correct STM32 board you are using
6. Implement Code

### Code Implementation
```c
#include "lcd_1602_driver.h"

...

I2C_HandleTypeDef hi2c1; // Usually autog-generated

...

int main(void)
{
  ...

  init_lcd(&hi2c1);
  HAL_Delay(10); // Recommended to allow display to stabalize

  ...

  while (1)
  {
    ...
    
    send_data
    
    ...

    HAL_Delay(3000); // Recommended to have at least 3 second delay between reads
  }

}
```
