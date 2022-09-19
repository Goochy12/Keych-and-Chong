/*
 * KeychChongFirmware.c
 *
 * Created: 12/09/2022 10:23:03 PM
 * Author : liamg
 */ 

#define F_CPU 1000000UL	//1mhz until program fuses
#include <avr/io.h>
#include <util/delay.h>
#include "keymap.c"

const uint16_t pinmap[2][3] = {
	{PINB4, PINB5, PINB6},
	{PINB7, PINC7, PINC6}
};

int main(void)
{
	
	
    while (1) 
    {
	    
    }
}

void keyRelease();

void sendKeyPress();

void scanMatrix(){
	//set pins
	DDRB = 1 << PORTB;
	DDRC = 1 << PORTC;
	for (uint16_t i = 0; i < sizeof(pinmap); i++)
	{
		PORTB = 1 << PINB7;
		
	}
		
};

void setLEDs();









/* 
DDRB = (1<<DDB0);
		
BLINKING LED
		
PORTB = 1 << PINB0;
_delay_ms(500);
PORTB = 0 << PINB0;
_delay_ms(500);
*/
