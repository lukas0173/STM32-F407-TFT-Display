/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lvgl.h"
#include "LCDController.h" #include "demos/benchmark/lv_demo_benchmark.h"
#include "ili9486_lvgl.h"
#include "ui.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;

/* USER CODE BEGIN PV */
uint8_t speedValue = 0;
uint8_t delayCounter = 0; // To slow down the change in while loop without affecting the renderer

static lv_anim_t speedIndicatorArrowAnimation; // speed indicator arrow animation
int32_t rotationValue;
int32_t previousAngleValue = -1700;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// Display speed value
void update_speed_display(int new_speed) {
	char speed_str[10];
	sprintf(speed_str, "%d", new_speed); // Format the speed as a string

	if (ui_speed_value != NULL) { // Check if the label exists
		lv_label_set_text(ui_speed_value, speed_str);
	}
}

void update_speed_indicator_arrow(lv_obj_t *arrowObj, int32_t targetAngle, int32_t previousAngle, uint32_t duration) {
    if (!arrowObj) {
        return;
    }

    // Stop and delete any previous animation that might be using the _ui_anim_callback_set_image_angle on this object.
	lv_anim_del(arrowObj, (lv_anim_exec_xcb_t)_ui_anim_callback_set_image_angle);

    // This user_data holds the target object for the callback.
    ui_anim_user_data_t *user_data = (ui_anim_user_data_t *)lv_mem_alloc(sizeof(ui_anim_user_data_t));
    if (!user_data) {
        return; // Allocation failed
    }
    user_data->target = arrowObj;
    user_data->val = 0; // Or an appropriate default/indicator

    lv_anim_init(&speedIndicatorArrowAnimation);

    // Get the current visual angle of the needle as the starting point.
    // LVGL stores rotation in 0.1 degree units.
    int32_t current_angle_tenths = previousAngle;

    lv_anim_set_user_data(&speedIndicatorArrowAnimation, user_data);
    lv_anim_set_custom_exec_cb(&speedIndicatorArrowAnimation, _ui_anim_callback_set_image_angle);
    lv_anim_set_values(&speedIndicatorArrowAnimation, current_angle_tenths, targetAngle);
    lv_anim_set_time(&speedIndicatorArrowAnimation, duration);
    lv_anim_set_path_cb(&speedIndicatorArrowAnimation, lv_anim_path_ease_out); // Or lv_anim_path_linear, etc.
    lv_anim_set_deleted_cb(&speedIndicatorArrowAnimation, _ui_anim_callback_free_user_data); // Crucial for freeing user_data

    // Set other parameters to default values (no repeat, no playback for this use case)
    lv_anim_set_playback_time(&speedIndicatorArrowAnimation, 0);
    lv_anim_set_playback_delay(&speedIndicatorArrowAnimation, 0);
    lv_anim_set_repeat_count(&speedIndicatorArrowAnimation, 0); // LV_ANIM_REPEAT_INFINITE for looping
    lv_anim_set_repeat_delay(&speedIndicatorArrowAnimation, 0);
    lv_anim_set_early_apply(&speedIndicatorArrowAnimation, false);
    lv_anim_set_delay(&speedIndicatorArrowAnimation, 0); // No initial delay for direct speed updates

    lv_anim_start(&speedIndicatorArrowAnimation);
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_SPI1_Init();
	MX_RTC_Init();
	/* USER CODE BEGIN 2 */
	lv_init();
	lv_port_disp_init();
	ui_init();
////
//	/* Change Active Screen's background color */
//	lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57),
//			LV_PART_MAIN);
//	lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff),
//			LV_PART_MAIN);
//
//	/* Create a spinner */
//	lv_obj_t *spinner = lv_spinner_create(lv_scr_act(), 1000, 60);
//	lv_obj_set_size(spinner, 64, 64);
//	lv_obj_align(spinner, LV_ALIGN_BOTTOM_MID, 0, 0);

//	lv_demo_benchmark();

//	LCD_SCAN_DIR Lcd_ScanDir = SCAN_DIR_DFT;
//	LCD_Init(Lcd_ScanDir, 200);
//	LCD_Clear(YELLOW);
//	LCD_Clear(LCD_BACKGROUND);
//	GUI_Show();

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		lv_timer_handler();
		HAL_Delay(5);
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		delayCounter++;
		if (delayCounter == 5) {
			delayCounter = 0;
			if (speedValue == 50) {
				speedValue = 0;
			}
			speedValue++;
			update_speed_display(speedValue);
			rotationValue = -1700 + speedValue * 60;
			update_speed_indicator_arrow(ui_speed_indicator_arrow, rotationValue, previousAngleValue, 300);
			previousAngleValue = -1700 + speedValue * 60;
		}
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI
			| RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief RTC Initialization Function
 * @param None
 * @retval None
 */
static void MX_RTC_Init(void) {

	/* USER CODE BEGIN RTC_Init 0 */

	/* USER CODE END RTC_Init 0 */

	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };

	/* USER CODE BEGIN RTC_Init 1 */

	/* USER CODE END RTC_Init 1 */

	/** Initialize RTC Only
	 */
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if (HAL_RTC_Init(&hrtc) != HAL_OK) {
		Error_Handler();
	}

	/* USER CODE BEGIN Check_RTC_BKUP */

	/* USER CODE END Check_RTC_BKUP */

	/** Initialize RTC and set the Time and Date
	 */
	sTime.Hours = 0x0;
	sTime.Minutes = 0x0;
	sTime.Seconds = 0x0;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK) {
		Error_Handler();
	}
	sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	sDate.Month = RTC_MONTH_JANUARY;
	sDate.Date = 0x1;
	sDate.Year = 0x0;

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN RTC_Init 2 */

	/* USER CODE END RTC_Init 2 */

}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void) {

	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}

/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void) {

	/* DMA controller clock enable */
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA2_Stream3_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */

	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE, CS_Pin | DC_Pin | RESET_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : CS_Pin DC_Pin RESET_Pin */
	GPIO_InitStruct.Pin = CS_Pin | DC_Pin | RESET_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
