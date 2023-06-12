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

double saldo= 0;
double tempSaldo= 0;
int contadorms= 0;
int temp= 0;

int botaoPress1(){
	if(PIND & (1 << PD5)){
		while(PIND &(1 <<PD5)){
			_delay_ms(10);
		}
		return 1;
	}
	return 0;
}
int botaoPress2(){
	if(PIND & (1 << PD7)){
		while(PIND &(1 <<PD7)){
			_delay_ms(10);
		}
		return 1;
	}
	return 0;
}

int botaoPress3(){
	if(PIND & (1 << PD6)){
		while(PIND &(1 <<PD6)){
			_delay_ms(10);
		}
		return 1;
	}
	return 0;
}

int botaoContagem(){
	if(PINB & (1 << PB0)){
		while(PINB &(1 << PB0)){
			_delay_ms(10);
		}
	return 1;
	}
return 0;
}

void checaSaldo(){
		if(saldo == 0){
			nokia_lcd_clear();
			nokia_lcd_write_string("Saldo = 0,00 ",1); //atualiza saldo
			nokia_lcd_render();
		}else if(saldo == 0.25){
			nokia_lcd_clear();
			nokia_lcd_write_string("Saldo = 0,25 ",1); //atualiza saldo
			nokia_lcd_render();
		}else if(saldo == 0.50){
			nokia_lcd_clear();
			nokia_lcd_write_string("Saldo = 0,50 ",1); //atualiza saldo
			nokia_lcd_render();
		}else if(saldo == 0.75){
			nokia_lcd_clear();
			nokia_lcd_write_string("Saldo = 0,75 ",1); //atualiza saldo
			nokia_lcd_render();
		}else if(saldo == 1.00){
			nokia_lcd_clear();
			nokia_lcd_write_string("Saldo = 1,00 ",1); //atualiza saldo
			nokia_lcd_render();
		}else if(saldo == 1.25){
			nokia_lcd_clear();
			nokia_lcd_write_string("Saldo = 1,25 ",1); //atualiza saldo
			nokia_lcd_render();
		}else if(saldo == 1.50){
			nokia_lcd_clear();
			nokia_lcd_write_string("Saldo = 1,50 ",1); //atualiza saldo
			nokia_lcd_render();
		}else if(saldo == 1.75){
			nokia_lcd_clear();
			nokia_lcd_write_string("Saldo = 1,75 ",1); //atualiza saldo
			nokia_lcd_render();
		}else if(saldo == 2.00){
			nokia_lcd_clear();
			nokia_lcd_write_string("Saldo = 2,00 ",1); //atualiza saldo
			nokia_lcd_render();
		}else if(saldo == 2.25){
			nokia_lcd_clear();
			nokia_lcd_write_string("Saldo = 2,25 ",1); //atualiza saldo
			nokia_lcd_render();
		}
}

int main(void)
{
	
	//PORTD2 - led verde - acende quando o parquímetro pode receber moeda
	//PORTD3 - led amarelo - acende quando o parquímetro começa a contar
	//PORTD4 - led vermelho - pisca quando terminar a contagem, 
	//parando quando o usuario adicionar mais crédito
	
	DDRD |= (1 << PD2);
    DDRD |= (1 << PD3);
    DDRD |= (1 << PD4); //setam as portas leds como saída

	
	DDRB &= ~(1 << PB0); //seta pb0 como entrada
	//PORTB &= ~(1 << PB0); //desabilita pull up
	
	DDRD &= ~(1 << PD7); //seta pd7 como entrada
	//PORTD &= ~(1 << PD7); //desabilita pull up
	
	DDRD &= ~(1 << PD6); //seta pd6 como entrada
	//PORTD &= ~(1 << PD6); //desabilita pull up
	
	DDRD &= ~(1 << PD5); //seta pd5 como entrada
	//PORTD &= ~(1 << PD5); //desabilita pull up
	
    nokia_lcd_init(); //inicia painel
    nokia_lcd_clear(); //clear no painel
    nokia_lcd_custom(1,glyph); 
    nokia_lcd_write_string("Saldo = 0",1); //escreve no painel
    nokia_lcd_set_cursor(0, 12); //muda local de escrita no painel
    nokia_lcd_render(); //renderiza painel
	
	while(1){
		checaSaldo();
		while(tempSaldo == saldo){
			_delay_ms(1);
			contadorms++;
			if(contadorms == 500){
				PORTD ^= (1 << PD4); //pisca led vermelha
				contadorms = 0;
			}
			if(botaoPress1() == 1){
				PORTD &= ~(1 << PD4); //desliga led vermelha
				saldo += 1.00;
			}else if(botaoPress2() == 1){
				PORTD &= ~(1 << PD4); //desliga led vermelha
				saldo += 0.25;
			}else if(botaoPress3() == 1){
				PORTD &= ~(1 << PD4); //desliga led vermelha
				saldo += 0.50;
			}
		}
		
		if(temp == 0){
		PORTD ^= (1 << PD2); //liga led verde
		temp=1;
		}
		
		//botao 1(PD5) = 1.00
		//botao 2(PD7) = 0.25
		//botao 3(PD6) = 0.50
		
		checaSaldo();
		
		if(botaoPress1() == 1){
			saldo += 1.00;
		}else if(botaoPress2() == 1){
			saldo += 0.25;
		}else if(botaoPress3() == 1){
			saldo += 0.50;
		}
		
		checaSaldo();
		if(saldo >= 1.50){
			_delay_ms(500);
		}
		while(saldo >= 1.50){
			PORTD &= ~(1 << PD2); //desliga led verde
			
			nokia_lcd_clear();
			nokia_lcd_write_string("Saldo suficiente, pressione o botao de   baixo para   ocupar a vaga. ",1); //atualiza saldo
			nokia_lcd_render();
			if(botaoContagem() == 1){
				PORTD ^= (1 << PD3); //liga led amarelo
				nokia_lcd_clear();
				nokia_lcd_write_string("Vaga adquirida com sucesso, 5 ",1); //atualiza saldo
				nokia_lcd_render();
				_delay_ms(1000);
				PORTD &= ~(1 << PD3); //desliga led amarelo
				nokia_lcd_clear();
				nokia_lcd_write_string("Vaga adquirida com sucesso, 4",1); //atualiza saldo
				nokia_lcd_render();
				_delay_ms(1000);
				PORTD ^= (1 << PD3); //liga led amarelo
				nokia_lcd_clear();
				nokia_lcd_write_string("Vaga adquirida com sucesso, 3",1); //atualiza saldo
				nokia_lcd_render();
				_delay_ms(1000);
				PORTD &= ~(1 << PD3); //desliga led amarelo
				nokia_lcd_clear();
				nokia_lcd_write_string("Vaga adquirida com sucesso, 2",1); //atualiza saldo
				nokia_lcd_render();
				_delay_ms(1000);
				PORTD ^= (1 << PD3); //liga led amarelo
				nokia_lcd_clear();
				nokia_lcd_write_string("Vaga adquirida com sucesso, 1",1); //atualiza saldo
				nokia_lcd_render();
				_delay_ms(1000);
				PORTD &= ~(1 << PD3); //desliga led amarelo
				nokia_lcd_clear();
				nokia_lcd_write_string("Vaga adquirida com sucesso, 0",1); //atualiza saldo
				nokia_lcd_render();
				_delay_ms(1000);
				PORTD ^= (1 << PD3); //liga led amarelo
				nokia_lcd_clear();
				nokia_lcd_write_string("Vaga liberada, adicione moedas para ocupar novamente",1);
				nokia_lcd_render();
				_delay_ms(1000);
				PORTD &= ~(1 << PD3); //desliga led amarelo
				checaSaldo();
				temp = 0;
				tempSaldo = saldo;
				tempSaldo -= 1.50;
				saldo-= 1.50;
				
			}
		}
		
	}
}
