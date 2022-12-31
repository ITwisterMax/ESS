/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
	#define LEDS_COUNT 4
	#define SPEEDS_COUNT 3
	#define BUTTON_PRESS_PERIOD 100
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
	PIN_TYPE leds_pins[LEDS_COUNT] = { {GPIOA, GPIO_PIN_5}, {GPIOA, GPIO_PIN_6}, {GPIOA, GPIO_PIN_7}, {GPIOB, GPIO_PIN_6} };

	uint32_t speeds[SPEEDS_COUNT] = {50000, 150000, 200000};
	_Bool leds_state[LEDS_COUNT + 1] = {0, 0, 0, 0, 1};

	_Bool is_active = 0;

	uint8_t curr_step = 0;
	int8_t prev_step = 0;

	uint8_t speed = 1;

	_Bool flag_down_press = 1;
	uint32_t time_down_press = 0;

	_Bool flag_up_press = 1;
	uint32_t time_up_press = 0;

	_Bool flag_action_press = 1;
	uint32_t time_action_press = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */
	if(! flag_up_press && (HAL_GetTick() - time_up_press) > BUTTON_PRESS_PERIOD)
	{
		flag_up_press = 1;
	}

	if (flag_up_press) {
		flag_up_press = 0;
		
		// speed increment
		if (speed < SPEEDS_COUNT - 1) {
			speed += 1;
			show_on_display(0, speed);
			__HAL_TIM_SET_AUTORELOAD(&htim1, speeds[speed]);
		}

		time_up_press = HAL_GetTick();
	}
  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */
	if(! flag_action_press && (HAL_GetTick() - time_action_press) > BUTTON_PRESS_PERIOD)
	{
		flag_action_press = 1;
	}

	if (flag_action_press) {
		flag_action_press = 0;
			
		// start timer and set save state
		if (! is_active) {
			HAL_TIM_Base_Start_IT(&htim1);
			is_active = 1;

			for (int i = 0; i < LEDS_COUNT; i++) {
				if (leds_state[i] == 1) {
					HAL_GPIO_WritePin(leds_pins[i].port, leds_pins[i].pin, GPIO_PIN_RESET);
				}
			}
		}
		// stop timer and reset save state
		else {
			HAL_TIM_Base_Stop_IT(&htim1);
			is_active = 0;

			for (int i = 0; i < LEDS_COUNT; i++) {
				HAL_GPIO_WritePin(leds_pins[i].port, leds_pins[i].pin, GPIO_PIN_SET);
			}
		}

		time_action_press = HAL_GetTick();
	}
  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */
	if(! flag_down_press && (HAL_GetTick() - time_down_press) > BUTTON_PRESS_PERIOD)
	{
		flag_down_press = 1;
	}

	if (flag_down_press) {
		flag_down_press = 0;
		
		// speed decrement
		if (speed > 0) {
			speed -= 1;
			show_on_display(0, speed);
			__HAL_TIM_SET_AUTORELOAD(&htim1, speeds[speed]);
		}

		time_down_press = HAL_GetTick();
	}
  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt.
  */
void TIM1_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_IRQn 0 */

  /* USER CODE END TIM1_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_IRQn 1 */

	// reset prev step
	if (prev_step != -1) {
		HAL_GPIO_WritePin(leds_pins[prev_step].port, leds_pins[prev_step].pin, GPIO_PIN_SET);
		leds_state[prev_step] = 0;
	}

	// reset all steps
	if (leds_state[curr_step] == 1) {
		for (int i = 0; i < LEDS_COUNT; i++) {
			HAL_GPIO_WritePin(leds_pins[i].port, leds_pins[i].pin, GPIO_PIN_SET);
			leds_state[i] = 0;
		}
	}

	// reset curr step
	HAL_GPIO_WritePin(leds_pins[curr_step].port, leds_pins[curr_step].pin, GPIO_PIN_RESET);
	leds_state[curr_step] = 1;

	// update prev and curr steps
	if (leds_state[curr_step + 1] != 1) {
		prev_step = curr_step;
		curr_step++;
	}
	else {
		prev_step = -1;
		curr_step = 0;
	}
	
  /* USER CODE END TIM1_UP_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(B1_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
