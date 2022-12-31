#include "stm32f1xx_hal.h"

#define PRESCALER 5
#define VOLUME 10
#define LOW_FACTOR 5
#define MUL 2
#define NOTES_COUNT 200

void init_notes();

uint8_t save_note(uint32_t duration, uint8_t curr);

void play_notes();
