/*
 * ili9486_lvgl.h
 *
 *  Created on: May 7, 2025
 *      Author: kiet
 */

// File: ILI9486_lvgl.h
#ifndef INC_ILI9486_LVGL_H_
#define INC_ILI9486_LVGL_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"      // For STM32 HAL, GPIO defs
#include "ILI9486.h"   // Include the Waveshare ILI9486 base driver header

#define GUI_WIDTH       LCD_WIDTH  // Should be 480
#define GUI_HEIGHT      LCD_HEIGHT // Should be 320

// Functions to be called
void ILI9486_Init_Adapter(void);
void ILI9486_SetWindow_Adapter(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y);
void ILI9486_DrawBitmap_Adapter(uint16_t w, uint16_t h, uint8_t *s);
void ILI9486_DrawBitmapDMA_Adapter(uint16_t w, uint16_t h, uint8_t *s);
void ILI9486_WritePixel_Adapter(uint16_t x, uint16_t y, uint16_t color);

void ILI9486_EndOfDrawBitmap_Adapter(void);

// This is a helper, might not be needed externally if Waveshare driver handles it well enough
// void ILI9486_LCD_WR_REG_Adapter(uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* INC_ILI9486_LVGL_H_ */
