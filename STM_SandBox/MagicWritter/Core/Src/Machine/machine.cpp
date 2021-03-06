/*
 * machine.cpp
 *
 *  Created on: Apr 8, 2022
 *      Author: szerpadiaz
 */

#include <Machine/machine.h>
#include <Machine/processor_header.h>

void Machine::init()
{
	HAL_Init();
	Machine::configure_clock();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	CRC_HandleTypeDef hcrc;
	hcrc.Instance = CRC;
	if (HAL_CRC_Init(&hcrc) != HAL_OK)
	{
		Machine::error_handler();
	}
}

void Machine::configure_clock(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
	  Machine::error_handler();
  }


  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Machine::error_handler();
  }
}

void Machine::error_handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

/**
  * Initializes the Global MSP.
  * This function is called by HAL_Init() which is called above in Machine::init()
  */
void HAL_MspInit(void)
{

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);
}

void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc)
{
  if(hcrc->Instance==CRC)
  {
    __HAL_RCC_CRC_CLK_ENABLE();

  }
}

void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc)
{
  if(hcrc->Instance==CRC)
  {
    __HAL_RCC_CRC_CLK_DISABLE();
  }
}
