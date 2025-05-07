# STM32-F407-TFT-Display
The project will utilize the 3.5-inch TFT LCD (Wireshark clone), ILI9486 chip, with the STM32F407VGT6 dev kit. An additional adapter layer is needed over the original Wireshark driver for LVGL compatibility (`Core/Inc/ili9846_lvgl.h`, and `Core/Src/ili9846_lvgl.c`). This adapter layer is inspired by the ILI9341 driver, following this tutorial: https://controllerstech.com/lvgl-on-stm32-part-1/
## Notes
### Dependencies
- ili9486 driver headers and sources are located inside `Core/Inc` and `Core/Src`
- Make sure to copy all of the font files, `LCDController`, `ILI9486`, and `ili9486_lvgl`.
- This project is using LVGL v8.3 for compatibility, located in `Drivers` folder, make sure to copy the `lv_config.h` as well.

After copying the `lvgl` folder to `Drivers` directory, include the path by right-clicking on the project and opening Properties. Then head to `c/c++ Build` -> `Settings` -> `MCU GCC Compiler` -> `Include Paths`, then add the `lvgl` folder.
### Configurations
Besides copying all the necessary files into your projects, you will need to make the following change to the timer interrupt. In my case is the file `stm32f4xx_it.c`.
```c
void SysTick_Handler(void) {
	/* USER CODE BEGIN SysTick_IRQn 0 */
	lv_tick_inc(1);

	/* USER CODE END SysTick_IRQn 0 */
	HAL_IncTick();
	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}
```
