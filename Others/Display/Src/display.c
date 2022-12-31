#include "display.h"

// from 0 to 9 digit
uint8_t digits_map[DIGITS_COUNT] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0X80, 0X90};
// from 1 to 4 segment
uint8_t segments_map[SEGMENTS_COUNT] = {0xF8, 0xF4, 0xF2, 0xF1};

// show a digit
void show_on_display(uint8_t segment, uint8_t digit)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);

	shift_out(digits_map[digit]);
	shift_out(segments_map[segment]);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
}

// shift out register
void shift_out(uint8_t value)
{
	for (uint8_t i = 0; i < TRIGGERS_COUNT; i++)  {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, !!(value & (1 << (TRIGGERS_COUNT - 1 - i))));		

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);        
	}
}

// digit += count
void increment(int32_t digit[SEGMENTS_COUNT + 1], uint8_t count)
{
	if (count > DIGITS_COUNT - 1) {
		return;
	}

	digit[0] += count;
	for (int i = 0; i < SEGMENTS_COUNT; i++) {
		if (digit[i] > DIGITS_COUNT - 1) {
			digit[i + 1] += 1;
		}

		digit[i] %= DIGITS_COUNT;
	}
};

// digit -= count
void decrement(int32_t digit[SEGMENTS_COUNT + 1], uint8_t count)
{
	if (count > DIGITS_COUNT - 1) {
		return;
	}

	digit[0] -= count;
	for (int i = 0; i < SEGMENTS_COUNT; i++) {
		if (digit[i] < 0) {
			digit[i + 1] -= 1;
		}

		digit[i] = (digit[i] + DIGITS_COUNT) % DIGITS_COUNT;
	}
};