/*
 * ili9846_lvgl.c
 *
 *  Created on: May 7, 2025
 *      Author: kiet
 */


#include "ili9486_lvgl.h"
#include "lvgl.h"

extern SPI_HandleTypeDef hspi1;
extern DMA_HandleTypeDef hdma_spi1_tx; // If using DMA

// Forward declaration for lv_disp_flush_ready, if needed by ILI9486_EndOfDrawBitmap_Adapter
#if LV_USE_DMA_TRANSFER_FOR_ILI9486 // Custom define
extern lv_disp_drv_t disp_drv; // Assuming 'disp_drv' is globally accessible
#endif

static void ConvHL(uint8_t *s, int32_t l)
{
	uint8_t v;
	while (l > 0) {
		v = *(s+1);
		*(s+1) = *s;
		*s = v;
		s += 2;
		l -= 2;
	}
}

void ILI9486_Init_Adapter(void)
{
    LCD_Init(SCAN_DIR_DFT, 255); // Default scan direction, max backlight
    LCD_Clear(BLACK); // Clear screen
}

void ILI9486_SetWindow_Adapter(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y)
{
    LCD_SetWindow(start_x, start_y, end_x + 1, end_y + 1); // +1 because Waveshare might do (Xend-1)

    // After setting window, prepare for GRAM write
    LCD_WriteReg(0x2C); // Write to GRAM command for ILI9486 (same as ILI9341)
}

void ILI9486_WritePixel_Adapter(uint16_t x, uint16_t y, uint16_t color)
{
    ILI9486_SetWindow_Adapter(x, y, x, y); // Set 1x1 window

    LCD_SetPointlColor(x, y, color);

}

void ILI9486_DrawBitmap_Adapter(uint16_t w, uint16_t h, uint8_t *s)
{

    // Prepare for data write
    LCD_DC_1; // Data mode
    LCD_CS_0;   // Chip select active

    HAL_SPI_Transmit(&hspi1, s, (uint32_t)w * h * 2, HAL_MAX_DELAY);

    LCD_CS_1;   // Chip select inactive
}

void ILI9486_DrawBitmapDMA_Adapter(uint16_t w, uint16_t h, uint8_t *s)
{
    // Prepare for data write
    LCD_DC_1; // Data mode
    LCD_CS_0;   // Chip select active

    HAL_SPI_Transmit_DMA(&hspi1, s, (uint32_t)w * h * 2);
}

void ILI9486_EndOfDrawBitmap_Adapter(void)
{
}

