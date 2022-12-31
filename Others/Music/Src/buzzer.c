#include "buzzer.h"

MUSIC_TYPE musics[5] = {
	{
		1.05,
		89,
		{
			NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,
			NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,
			NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,
			NOTE_A3, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4,
			NOTE_F4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_D4,
			0, NOTE_A3, NOTE_C4, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_E4, NOTE_F4,
			NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4,
			NOTE_D4, 0, 0, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4,
			NOTE_G4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4,
			NOTE_A4, NOTE_D4, 0, NOTE_D4, NOTE_E3, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_A4,
			NOTE_D4, 0, NOTE_D4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_D4
		},
		{
			4, 8, 4, 8, 4, 8, 8, 8, 8, 4, 8, 4, 8, 4, 8, 8, 8, 8, 4, 8, 4, 8,
			4, 8, 8, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8,
			8, 4, 8, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 8, 4,
			4, 8, 8, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8,
			8, 4, 8, 8, 8, 4, 4, 4, 8, 4, 8, 8, 8, 4, 4, 8, 8
		}
	},
	{
		1.5,
		31,
		{
			NOTE_D4, 0, NOTE_F4, NOTE_D4, 0, NOTE_D4, NOTE_G4, NOTE_D4, NOTE_C4,
			NOTE_D4, 0, NOTE_A4, NOTE_D4, 0, NOTE_D4, NOTE_AS4, NOTE_A4, NOTE_F4,
			NOTE_D4, NOTE_A4, NOTE_D5, NOTE_D4, NOTE_C4, 0, NOTE_C4, NOTE_A3, NOTE_E4, NOTE_D4,
			0, NOTE_D4, NOTE_D4
		},
		{
			8, 8, 6, 16, 16, 16, 8, 8, 8, 
			8, 8, 6, 16, 16, 16, 8, 8, 8,
			8, 8, 8, 16, 16, 16, 16, 8, 8, 2,
			8, 4, 4
		}
	},
	{
		2.0,
		56,
		{
			NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_AS3, NOTE_AS4, 0, 0,
			NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_AS3, NOTE_AS4, 0, 0,
			NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,NOTE_DS3, NOTE_DS4, 0, 0,
			NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4, NOTE_DS3, NOTE_DS4, 0,
			0, NOTE_DS4, NOTE_CS4, NOTE_D4,
			NOTE_CS4, NOTE_DS4, NOTE_DS4, NOTE_GS3, NOTE_G3, NOTE_CS4,
			NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
			NOTE_GS4, NOTE_DS4, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_GS3, 0, 0, 0
		},
		{
			12, 12, 12, 12, 12, 12, 6,3,
			12, 12, 12, 12, 12, 12, 6, 3,
			12, 12, 12, 12, 12, 12, 6,
			3, 12, 12, 12, 12,
			12, 12, 6, 6, 18, 18, 18,
			6, 6, 6, 6, 6, 6,
			18, 18, 18, 18, 18, 18, 10, 10, 10,
			10, 10, 10, 3, 3, 3
		}
	},
	{
		3.0,
		74,
		{
			NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5,
			NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4,
			NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E4, NOTE_B4, NOTE_E5,
			NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4,
			NOTE_F5, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4,
			NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_B3,
			NOTE_E4, NOTE_E4, NOTE_E4, NOTE_B3, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_F4,
			NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4
		},
		{
			8, 8, 8, 8, 8, 8, 4, 8, 8, 8,
			8, 8, 8, 4, 8, 8, 8, 8, 8, 8,
			4, 8, 8, 8, 8, 4, 4, 8, 8, 8,
			8, 8, 8, 4, 8, 8, 8, 8, 8, 8,
			4, 8, 8, 8, 8, 8, 8, 1, 8, 8,
			8, 8, 4, 4, 4, 8, 4, 4, 8, 8,
			8, 8, 4, 8, 8, 4, 8, 4, 8, 8,
			4, 8, 4, 1
		}
	},
	{
		1.2,
		112,
		{
			NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
			NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
			NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
			NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
			NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
			NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5,
			NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, 
			NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, 
			NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
			NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
			NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
			NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_F4,
			NOTE_G4, 0, NOTE_G4, NOTE_D5,
			NOTE_C5, 0, NOTE_AS4, 0,
			NOTE_A4, 0, NOTE_A4, NOTE_A4,
			NOTE_C5, 0, NOTE_AS4, NOTE_A4, 
			NOTE_G4,0, NOTE_G4, NOTE_AS5,
			NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
			NOTE_G4,0, NOTE_G4, NOTE_AS5,
			NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
			NOTE_G4, 0, NOTE_G4, NOTE_D5,
			NOTE_C5, 0, NOTE_AS4, 0,
			NOTE_A4, 0, NOTE_A4, NOTE_A4,
			NOTE_C5, 0, NOTE_AS4, NOTE_A4, 
			NOTE_G4,0, NOTE_G4, NOTE_AS5,
			NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
			NOTE_G4,0, NOTE_G4, NOTE_AS5,
			NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5
		},
		{
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4,
			4, 4, 4, 4
		}
	}
};

extern TIM_HandleTypeDef htim2;

void play_music(uint8_t music)
{
	MUSIC_TYPE curr_music = musics[music];

	for (int curr = 0; curr < curr_music.notes_count; curr++) {
		if (curr_music.notes[curr] == 0) {
			HAL_Delay((MS * curr_music.tempo) / (2 * curr_music.durations[curr]));

			continue;
		}

		uint32_t pres = SystemCoreClock / (PRESCALER * VOLUME * curr_music.notes[curr]) - 1;
		__HAL_TIM_SET_PRESCALER(&htim2, pres);

		GPIO_InitTypeDef GPIO_InitStruct = {0};

		GPIO_InitStruct.Pin = GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		HAL_Delay((MS * curr_music.tempo) / curr_music.durations[curr]);

		GPIO_InitStruct.Pin = GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		HAL_Delay(curr_music.durations[curr] * LOW_FACTOR);
	}
}