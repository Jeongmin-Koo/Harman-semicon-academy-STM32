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
#include "dma.h"
#include "memorymap.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "ili9341.h"
#include "fonts.h"
#include "testimg.h"
#include "pic_240x320.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */
bool SDRAM_initialize(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);

	return ch;
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == SPI1) {
		printf("SPI DMA Complete!\n");
	}
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MPU Configuration--------------------------------------------------------*/
	MPU_Config();

	/* Enable the CPU Cache */

	/* Enable I-Cache---------------------------------------------------------*/
	SCB_EnableICache();

	/* Enable D-Cache---------------------------------------------------------*/
	SCB_EnableDCache();

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
	MX_USART1_UART_Init();
	MX_FMC_Init();
	/* USER CODE BEGIN 2 */
	SDRAM_initialize();

	uint8_t *sdramAddr = (uint8_t *)0xC0000000;

	for (int i =0; i<100; i++) {
		sdramAddr[i] = i;
	}

	for (int i =0; i<100; i++) {
		printf("sdramAddr[%d] = %d\n", i, sdramAddr[i]);
	}

	ILI9341_Init();
	printf("Hello STM32!\n");
	HAL_SPI_Transmit_DMA(&hspi1, hodu3, 100);

	for (uint32_t i=0; i<320*240*2; i++) {
		sdramAddr[i] = hodu3[i];
	}

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		//	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		//
		//	  ILI9341_FillScreen(ILI9341_BLUE);
		//	  HAL_Delay(1000);
		//	  ILI9341_FillScreen(ILI9341_RED);
		//	  HAL_Delay(1000);
		//	  ILI9341_FillScreen(ILI9341_GREEN);
		//	  HAL_Delay(1000);

		//	  ILI9341_DrawImage((ILI9341_WIDTH-240)/2, (ILI9341_HEIGHT-240)/2, 240, 240, (const uint16_t *)test_img_240x240);
		//	  HAL_Delay(2000);
//		ILI9341_DrawImage((ILI9341_WIDTH-240)/2, (ILI9341_HEIGHT-320)/2, 240, 320, (const uint16_t *)hodu3);
		ILI9341_DrawImage8((ILI9341_WIDTH-240)/2, (ILI9341_HEIGHT-320)/2, 240, 320, (const uint8_t *)sdramAddr);
		HAL_Delay(2000);
		//	  ILI9341_WriteString(0, 200, "PARK DOHYEON   SNITCH", Font_16x26, ILI9341_BLUE, ILI9341_BLACK);
		//	  HAL_Delay(2000);
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Supply configuration update enable
	 */
	HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

	while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 5;
	RCC_OscInitStruct.PLL.PLLN = 192;
	RCC_OscInitStruct.PLL.PLLP = 2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLR = 2;
	RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
	RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
	RCC_OscInitStruct.PLL.PLLFRACN = 0;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
			|RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
	RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */
bool SDRAM_initialize(void)
{
	SDRAM_HandleTypeDef *p_sdram  = &hsdram1;

	static FMC_SDRAM_CommandTypeDef Command;

	// Step 1: Configure a clock configuration enable command
	//
	Command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
	Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber      = 1;
	Command.ModeRegisterDefinition = 0;
	if(HAL_SDRAM_SendCommand(p_sdram, &Command, 1000) != HAL_OK)
	{
		return false;
	}

	// Step 2: Insert 100 us minimum delay */
	// Inserted delay is equal to 1 ms due to systick time base unit (ms)
	//
	HAL_Delay(1);

	// Step 3: Configure a PALL (precharge all) command
	//
	Command.CommandMode            = FMC_SDRAM_CMD_PALL;
	Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber      = 1;
	Command.ModeRegisterDefinition = 0;
	if(HAL_SDRAM_SendCommand(p_sdram, &Command, 1000) != HAL_OK)
	{
		return false;
	}

	// Step 4: Configure a Refresh command
	//
	Command.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber      = 8;
	Command.ModeRegisterDefinition = 0;
	if(HAL_SDRAM_SendCommand(p_sdram, &Command, 1000) != HAL_OK)
	{
		return false;
	}

	// Step 5: Program the external memory mode register
	//
	uint32_t mode_reg = 0;

	mode_reg |= (0 << 0); // Burst Length = 1
	mode_reg |= (0 << 3); // Burst Type
	//   0 : Sequential
	//   1 : Interleaved
	mode_reg |= (2 << 4); // CAS Latency Mode
	//   2 :
	//   3 :
	mode_reg |= (0 << 7); // Operation Mode
	mode_reg |= (1 << 9); // Write Burst Mode
	//   0 : Programmed Burst Length
	//   1 : Single Location Access

	Command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
	Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber      = 1;
	Command.ModeRegisterDefinition = mode_reg;
	if(HAL_SDRAM_SendCommand(p_sdram, &Command, 1000) != HAL_OK)
	{
		return false;
	}

	// Step 6: Set the refresh rate counter
	//
	// refresh rate = (COUNT + 1) * SDRAM clock freq (94.4444Mhz)
	//
	// COUNT = (SDRAM refresh period/Number of rows) - 20
	//       = (64ms / 8192) - 20
	//       = 7.81us * 94.444 - 20 = 717
	uint32_t refresh_count = 917;

	if(HAL_SDRAM_ProgramRefreshRate(p_sdram, refresh_count) != HAL_OK)
	{
		return false;
	}

	return true;
}
/* USER CODE END 4 */

/* MPU Configuration */

void MPU_Config(void)
{
	MPU_Region_InitTypeDef MPU_InitStruct = {0};

	/* Disables the MPU */
	HAL_MPU_Disable();

	/** Initializes and configures the Region and the memory to be protected
	 */
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.BaseAddress = 0x0;
	MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
	MPU_InitStruct.SubRegionDisable = 0x87;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);
	/* Enables the MPU */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
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
