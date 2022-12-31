#include "buzzer.h"

uint32_t notes[NOTES_COUNT];

extern TIM_HandleTypeDef htim2;

void init_notes()
{
	for (int curr = 0; curr < NOTES_COUNT; curr++) {
		notes[curr] = 0;
	}
}

uint8_t save_note(uint32_t duration, uint8_t curr)
{
	notes[curr] = duration;

	curr++;

	return curr;
}

void play_notes()
{
	int curr = 0;

	while (notes[curr] != 0) {
		GPIO_InitTypeDef GPIO_InitStruct = {0};

		GPIO_InitStruct.Pin = GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		HAL_Delay(notes[curr]);

		GPIO_InitStruct.Pin = GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		HAL_Delay(LOW_FACTOR * MUL);
		
		curr++;
	}
}