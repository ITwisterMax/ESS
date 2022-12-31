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
#include "stdlib.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "display.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
	#define LEDS_COUNT 4
	#define SPEEDS_COUNT 3
	#define DIGIT_LEN 10
	#define RANDOM_RANGE 6
	#define BUTTON_PRESS_PERIOD 100
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

// common values
// ---------------------------------------------------------
	uint8_t mode = 0;

	RTC_TimeTypeDef sTime = {0};

	uint32_t speeds[SPEEDS_COUNT] = {50000, 150000, 200000};
	uint8_t speed = 1;

	_Bool is_active = 0;
	_Bool is_init_digit = 0;

	_Bool flag_down_press = 1;
	uint32_t time_down_press = 0;

	_Bool flag_up_press = 1;
	uint32_t time_up_press = 0;

	_Bool flag_action_press = 1;
	uint32_t time_action_press = 0;
// ---------------------------------------------------------


// mode 1 values
// ---------------------------------------------------------
	PIN_TYPE leds_pins[LEDS_COUNT] = { {GPIOA, GPIO_PIN_5}, {GPIOA, GPIO_PIN_6}, {GPIOA, GPIO_PIN_7}, {GPIOB, GPIO_PIN_6} };

	_Bool leds_state[LEDS_COUNT + 1] = {0, 0, 0, 0, 1};

	uint8_t curr_step = 0;
	int8_t prev_step = 0;
// ---------------------------------------------------------


// mode 2 values
// ---------------------------------------------------------
	int32_t digit_mode2[DIGIT_LEN] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	uint8_t offset = 0;
// ---------------------------------------------------------


// mode 3 values
// ---------------------------------------------------------
	int32_t digit_mode3[SEGMENTS_COUNT] = { 0, 0, 0, 0 };
// ---------------------------------------------------------

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern RTC_HandleTypeDef hrtc;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
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

		switch (mode) {
			// speed increment for mode 1
			case 1:
				if (speed < SPEEDS_COUNT - 1) {
					speed += 1;
					show_on_display(SEGMENTS_COUNT - 1, speed);
					__HAL_TIM_SET_AUTORELOAD(&htim1, speeds[speed]);
				}

				break;

			// speed increment for mode 2 and 3
			case 2:
			case 3:
				if (speed < SPEEDS_COUNT - 1) {
					speed += 1;
					__HAL_TIM_SET_AUTORELOAD(&htim2, speeds[speed]);
				}

				break;

			default:
				break;
		}

		// set current mode
		if (mode == 0) {
			mode = 3;
			show_on_display(SEGMENTS_COUNT - 1, mode);
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

		switch (mode) {
			case 1:
				// start or stop timer
				if (! is_active) {
					HAL_TIM_Base_Start_IT(&htim1);
					is_active = 1;

					for (int i = 0; i < LEDS_COUNT; i++) {
						if (leds_state[i] == 1) {
							HAL_GPIO_WritePin(leds_pins[i].port, leds_pins[i].pin, GPIO_PIN_RESET);
						}
					}
				}
				else {
					HAL_TIM_Base_Stop_IT(&htim1);
					is_active = 0;

					for (int i = 0; i < LEDS_COUNT; i++) {
						HAL_GPIO_WritePin(leds_pins[i].port, leds_pins[i].pin, GPIO_PIN_SET);
					}
				}

				break;

			case 2:
				// generate random digit for mode 2
				if (!is_init_digit) {
					HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

					srand(sTime.Seconds);
					for (int i = 0; i < DIGIT_LEN; i++) {
						digit_mode2[i] = rand() % 10;
					}
					
					is_init_digit = 1;
				}

				// start or stop timer
				if (! is_active) {
					HAL_TIM_Base_Start_IT(&htim2);
					is_active = 1;
				}
				else {
					HAL_TIM_Base_Stop_IT(&htim2);
					is_active = 0;

					for (int i = 0; i < DIGIT_LEN; i++) {
						digit_mode2[i] = rand() % 10;
					}

					offset = 0;
				}

				break;

			case 3:
				// initialize random digit generator for mode 3
				if (! is_init_digit) {
					HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

					srand(sTime.Seconds);
					is_init_digit = 1;
				}

				// start or stop timer
				if (! is_active) {
					HAL_TIM_Base_Start_IT(&htim2);
					is_active = 1;
				}
				else {
					HAL_TIM_Base_Stop_IT(&htim2);
					is_active = 0;
				}

				break;

			default:

				break;
		}

		// set current mode
		if (mode == 0) {
			mode = 1;
			show_on_display(SEGMENTS_COUNT - 1, mode);
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

		switch (mode) {
			// speed decrement for mode 1
			case 1:
				if (speed > 0) {
					speed -= 1;
					show_on_display(SEGMENTS_COUNT - 1, speed);
					__HAL_TIM_SET_AUTORELOAD(&htim1, speeds[speed]);
				}

				break;

			// speed decrement for mode 2 and 3
			case 2:
			case 3:
				if (speed > 0) {
					speed -= 1;
					__HAL_TIM_SET_AUTORELOAD(&htim2, speeds[speed]);
				}

				break;

			default:
				break;
		}

		// set current mode
		if (mode == 0) {
			mode = 2;
			show_on_display(SEGMENTS_COUNT - 1, mode);
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

	// mode 1
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

	// set curr step
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
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */
 
	// generate random digits for mode 3
	for (int i = 1; i < SEGMENTS_COUNT; i += 2) {
		digit_mode3[i] = rand() % RANDOM_RANGE + 1;
	}

	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim3);

	// calculate digit offset for mode 2
	offset++;

	if (offset == DIGIT_LEN) {
		offset = 0;
	}

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

	// mode 2
	if (mode == 2) {
		for (int i = 0; i < SEGMENTS_COUNT; i++) {
			int index = (i + offset) % DIGIT_LEN;
			show_on_display(i, digit_mode2[index]);
		}
	}
	// mode 3
	else {
		for (int i = 1; i < SEGMENTS_COUNT; i += 2) {
			show_on_display(i, digit_mode3[i]);
		}
	}

  /* USER CODE END TIM3_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
