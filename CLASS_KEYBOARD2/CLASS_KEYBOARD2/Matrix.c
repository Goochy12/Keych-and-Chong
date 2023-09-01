/*
 * Matrix.c
 *
 * Created: 7/06/2023 9:55:08 PM
 *  Author: Liam
 */ 


#include "Matrix.h"
//#include "Keyboard.h"
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

bool key_states_layer[NUM_ROWS][NUM_COLS] = {
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
};

const uint16_t keyboard_layout[NUM_ROWS][NUM_COLS] = {
	{HID_KEYBOARD_SC_A, HID_KEYBOARD_SC_B, HID_KEYBOARD_SC_C},
	{HID_KEYBOARD_SC_1_AND_EXCLAMATION, HID_KEYBOARD_SC_2_AND_AT, HID_KEYBOARD_SC_3_AND_HASHMARK},
	{HID_KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEYBOARD_MODIFIER_LEFTGUI, HID_KEYBOARD_SC_CAPS_LOCK}
};

portPin_tuple rows[NUM_ROWS] = {{&PORTB, PINB7},
								{&PORTC, PINC6},
								{&PORTC, PINC7}};
									
portPin_tuple cols[NUM_COLS] = {{&PORTB, PINB7}, {&PORTC, PINC6}, {&PORTC, PINC7}};
	
uint16_t keys_pressed[6] = {0,0,0,0,0,0};

//uint8_t secondTest[NUM_ROWS][2] = {{PORTB, PINB7}, {PORTC, PINC6}, {PORTC, PINC7}};

//configure input and output pins
//columns output
//rows input
void matrix_init(){
	DDRB = 0b10000001;	//set pin B7 (row1) and caps to high (direction -> output)
	DDRC = 0b11000000;	//set pin c6 (row2) and c7 (row3) to high (direction -> output)
	
	//this does the same as above
	DDRB = (1 << DDB0);
	DDRC = (1 << DDC6);
	DDRC &= (1 << DDC7);
	
	
	portPin_tuple rowTuple[NUM_ROWS];
	//pin_tuple colTuple[NUM_COLS];
	
	//rowTuple[0]
	
		
	for (int i = 0; i < NUM_ROWS; i++)
	{
		//printf("Port: %d, Pin: %d", rows[i].port, rows[i].pin);
	}
}

void matrix_scan(){
	//TODO: Switch rows and cols
	bool key_state;
	
	for (int i = 0; i < NUM_COLS; i++)
	{
		_delay_ms(10);
		
		*cols[i].port &= (1 << cols[i].pin);	//set port to high
		
		for (int j = 0; j < NUM_ROWS; j++)
		{
			_delay_ms(10);
			cli();
			
			//if pin state is different to the current keystate
			if (((bool)rows[j].pin & (1 << rows[j].pin)) != key_states_layer[i][j])
			{
				//key down
				if(rows[j].pin & (1 << rows[j].pin)){
					//check if modifier
					
					key_states_layer[i][j] = 1;
					for (int k = 0; k < 6; k++)
					{
						//if no keys pressed at this location
						if (keys_pressed[k] == 0)
						{
							keys_pressed[k] = keyboard_layout[i][j];
							break;
						}
					}
				}else{
					key_states_layer[i][j] = 0;
					for (int k = 0; k < 6; k++)
					{
						//if no keys pressed at this location
						if (keys_pressed[k] == keyboard_layout[i][j])
						{
							keys_pressed[k] = 0;
							break;
						}
					}
				}
			}
			
		}
	}
}