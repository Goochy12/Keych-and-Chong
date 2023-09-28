#ifndef MATRIX_H_
#define MATRIX_H_

#include <avr/io.h>
#include <LUFA/Drivers/USB/USB.h>

#define NUM_ROWS 3
#define NUM_COLS 3

typedef struct  
{
	volatile uint8_t * port;
	uint8_t pin;
}portPin_tuple;

void matrix_init();
void matrix_scan();

const uint16_t keyboard_layout[NUM_ROWS][NUM_COLS];

bool key_states_layer[NUM_ROWS][NUM_COLS];

uint16_t keys_pressed[6];

#endif /* MATRIX_H_ */