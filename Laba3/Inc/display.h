#include "stm32f1xx_hal.h"

#define DIGITS_COUNT 10
#define SEGMENTS_COUNT 4
#define TRIGGERS_COUNT 8
#define DELAY 1

typedef struct PIN_TYPE
{
  GPIO_TypeDef* port;
  uint16_t pin;
} PIN_TYPE;

void show_on_display(uint8_t segment, uint8_t digit);
void shift_out(uint8_t value);
void increment(int32_t digit[SEGMENTS_COUNT + 1], uint8_t count);
void decrement(int32_t digit[SEGMENTS_COUNT + 1], uint8_t count);