/* Nokia 5110 LCD AVR Library example
 *
 * Copyright (C) 2015 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 *
 * Original library written by SkewPL, http://skew.tk
 * Custom char code by Marcelo Cohen - 2021
 */

#include <avr/io.h>
#include <util/delay.h>
#include "nokia5110.h"

uint8_t glyph[] = { 0b00010000, 0b00100100, 0b11100000, 0b00100100, 0b00010000 };


int botaoPress1(){
	if(PIND & (1 << PD5)){
		while(PIND &(1 <<PD5)){
		PORTB |= (1 << PB6);
			_delay_ms(1);
		}
		return 1;
	}
	PORTB &= ~(1<<PB6);
	return 0;
}


int main(void)
{


	
	
	DDRD &= ~(1 << PD5); //seta pd5 como entrada
	//PORTD &= ~(1 << PD5); //desabilita pull up
	while(1){
	
		
		if(botaoPress1() == 1){
			
		}else{
			
		}
		_delay_ms(10);
	}
}
