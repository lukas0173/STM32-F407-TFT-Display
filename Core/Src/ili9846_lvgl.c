/*
 * ili9846_lvgl.c
 *
 *  Created on: May 7, 2025
 *      Author: kiet
 */


// File: ILI9486_lvgl.c
#include "ili9486_lvgl.h"
#include "lvgl.h" // For lv_disp_flush_ready if used in EndOfDrawBitmap

extern SPI_HandleTypeDef hspi1; // Assuming SPI1 is used, as in both drivers
extern DMA_HandleTypeDef hdma_spi1_tx; // If using DMA

// Forward declaration for lv_disp_flush_ready, if needed by ILI9486_EndOfDrawBitmap_Adapter
// Better to get it from lv_disp.h or similar, but for now:
#if LV_USE_DMA_TRANSFER_FOR_ILI9486 // Custom define you might add
extern lv_disp_drv_t disp_drv; // Assuming 'disp_drv' is globally accessible or passed
#endif

// Byte swap function - copied from your ili9341.c
// This might be needed if LVGL outputs colors in one byte order
// and the ILI9486 (or the way Waveshare driver sends data) expects another.
// LVGL usually outputs RGB565 Big Endian. Most displays expect Big Endian.
// If colors are swapped (red/blue), this function (or lack thereof) is a suspect.
// The ILI9341 driver used it, so we keep it for mimicry.
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
    // Initialize using the Waveshare ILI9486 driver
    // SCAN_DIR_DFT (D2U_L2R) from Waveshare might give 480x320.
    // You might need to experiment with other LCD_SCAN_DIR values
    // if the orientation is not correct for LVGL's 480x320.
    // L2R_U2D (0) or R2L_D2U (3) are common for landscape.
    // U2D_R2L (5) would be portrait 320x480 then rotated.
    // The ili9341 used ROTATE_270. For ILI9486, to get landscape 480x320,
    // if native is 320x480, you'd use something like U2D_R2L or D2U_L2R based on connector.
    // The Waveshare driver's LCD_WIDTH/HEIGHT are 480/320, so SCAN_DIR_DFT should be fine.
    LCD_Init(SCAN_DIR_DFT, 255); // Default scan direction, max backlight
    LCD_Clear(BLACK); // Clear screen
}

void ILI9486_SetWindow_Adapter(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y)
{
    // Use Waveshare function to set window
    // Note: Waveshare's LCD_SetWindow expects Xend and Yend to be the actual last pixel,
    // so it internally subtracts 1 if needed, or expects it directly.
    // The ili9341 driver sent end_x, end_y directly.
    // The Waveshare function is: LCD_SetWindow(Xstart, Ystart, Xend, Yend)
    // And it writes (Xend-1), (Yend-1). So, if LVGL provides inclusive end coordinates, this is fine.
    LCD_SetWindow(start_x, start_y, end_x + 1, end_y + 1); // +1 because Waveshare might do (Xend-1)

    // After setting window, prepare for GRAM write
    LCD_WriteReg(0x2C); // Write to GRAM command for ILI9486 (same as ILI9341)
}

void ILI9486_WritePixel_Adapter(uint16_t x, uint16_t y, uint16_t color)
{
    ILI9486_SetWindow_Adapter(x, y, x, y); // Set 1x1 window

    // Waveshare LCD_SetPointlColor does this:
    // LCD_SetCursor(Xpoint, Ypoint); // which is LCD_SetWindow(Xpoint, Ypoint, Xpoint, Ypoint);
    // LCD_SetColor(Color, 1, 1);     // which is LCD_Write_AllData(Color, 1*1);
    // LCD_Write_AllData then does: DC_1, CS_0, HAL_SPI_Transmit(byte0), HAL_SPI_Transmit(byte1), CS_1
    // So we can use it directly.
    LCD_SetPointlColor(x, y, color);

    // Or, more manually to ensure byte order if ConvHL was vital:
    /*
    uint8_t data[2];
    data[0] = color >> 8;
    data[1] = color & 0xFF;
    // ConvHL(data, 2); // If byte swap is needed for single pixel and Waveshare doesn't do it.
                       // LCD_SetPointlColor uses LCD_Write_AllData which sends MSB then LSB.
                       // If LVGL color is already MSB-LSB, ConvHL is not needed here.

    LCD_DC_1();
    LCD_CS_0; // Macro from Waveshare ILI9486.h
    HAL_SPI_Transmit(&hspi1, data, 2, HAL_MAX_DELAY);
    LCD_CS_1; // Macro from Waveshare ILI9486.h
    */
}

void ILI9486_DrawBitmap_Adapter(uint16_t w, uint16_t h, uint8_t *s)
{
    // ILI9486_SetWindow_Adapter should have been called by LVGL's flush_cb before this.
    // It would have called LCD_WriteReg(0x2C);

    // Prepare for data write
    LCD_DC_1; // Data mode
    LCD_CS_0;   // Chip select active

    // The ili9341 driver did ConvHL. If LVGL color data (in *s) needs byte swapping
    // for the ILI9486, do it here.
    // Assuming s points to an array of uint16_t colors (so uint8_t *s means byte pointer)
    // uint32_t len_bytes = (uint32_t)w * h * 2;
    // ConvHL(s, len_bytes); // Apply if colors are Red/Blue swapped or image is garbled

    HAL_SPI_Transmit(&hspi1, s, (uint32_t)w * h * 2, HAL_MAX_DELAY);

    LCD_CS_1;   // Chip select inactive
}

void ILI9486_DrawBitmapDMA_Adapter(uint16_t w, uint16_t h, uint8_t *s)
{
    // ILI9486_SetWindow_Adapter should have been called by LVGL's flush_cb.
    // It would have called LCD_WriteReg(0x2C);

    // Prepare for data write
    LCD_DC_1; // Data mode
    LCD_CS_0;   // Chip select active

    // Byte swapping if needed (see DrawBitmap_Adapter notes)
    // uint32_t len_bytes = (uint32_t)w * h * 2;
    // ConvHL(s, len_bytes);

    // Start DMA transfer
    // HAL_SPI_Transmit_DMA will return HAL_OK immediately.
    // LCD_CS_1 MUST be called in HAL_SPI_TxCpltCallback when DMA is complete.
    HAL_SPI_Transmit_DMA(&hspi1, s, (uint32_t)w * h * 2);
}

// This function's purpose in the context of the tutorial's LVGL port needs clarification.
// If non-DMA: lv_disp_flush_ready is called in flush_cb after DrawBitmap.
// If DMA: lv_disp_flush_ready is called in HAL_SPI_TxCpltCallback.
// So this function might not be strictly needed by the LVGL port if it follows the tutorial.
// If it *is* called by the LVGL porting layer, it should signal LVGL.
void ILI9486_EndOfDrawBitmap_Adapter(void)
{
    // This function is a bit ambiguous from the ILI9341 example.
    // If this is called from a non-DMA flush_cb, it means drawing is done.
    // If from a DMA context, it's usually handled by the DMA complete callback.
    // The tutorial calls lv_disp_flush_ready() at the end of the disp_flush (for non-DMA)
    // or in HAL_SPI_TxCpltCallback (for DMA).
    // So, this function might be redundant for the tutorial's structure.
    // If, for some reason, your porting code calls this and expects it to signal LVGL:
    // lv_disp_flush_ready(&disp_drv); // You'd need access to your disp_drv variable
}

// This is the SPI DMA Transfer Complete Callback.
// It MUST be implemented in your stm32f4xx_it.c or a relevant HAL callback file.
// Add this to your project, typically in stm32f4xx_it.c or where HAL_SPI_TxCpltCallback is defined.
/*
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi == &hspi1) { // Check if it's the SPI peripheral used for the LCD
        LCD_CS_1; // De-select LCD, IMPORTANT for DMA
        // Signal LVGL that the flush is complete
        // You need to have access to your 'lv_disp_drv_t disp_drv' variable here.
        // This might be global or passed through a context pointer if you have one.
        // For simplicity, if it's global:
        // extern lv_disp_drv_t disp_drv; // Declare if not in this scope
        lv_disp_flush_ready(&disp_drv);
    }
}
*/
// Make sure you have `extern lv_disp_drv_t disp_drv;` in the file where HAL_SPI_TxCpltCallback is,
// and `lv_disp_drv_t disp_drv;` is defined globally in your LVGL porting file (e.g., LCDController.c).
