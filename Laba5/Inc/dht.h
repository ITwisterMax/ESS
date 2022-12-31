#ifndef DHT_H_
#define DHT_H_

#include "main.h"

#define DHT_TIMEOUT 10000
#define DHT_POLLING_INTERVAL 2000

typedef struct {
	float hum;
	float temp;
} DHT_DATA;

typedef struct {
	GPIO_TypeDef* port;
	uint16_t pin;

	uint32_t last_polling_time;

	float last_temp;
	float last_hum;
} DHT;

DHT_DATA get_dht_data(DHT *sensor);

#endif
