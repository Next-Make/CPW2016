/*
 * Next_Make_CPW_2015.c
 *
 * Created: 2/28/2015 10:54:56 PM
 * Author: Next-Makers
 */ 


#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>


//PA0 clock line to temp sensor
//PA1 2nd LED
//PA2 3rd LED
//PA3 4th LED
//PA4 5th LED
//PA5 6th LED
//PA6 7th LED
//PA7 8th LED
//PB0 I/O line to temp sensor
//PB1 9th LED
//PB2 10th LED

// num is a number from 0 to 511
void displayAsBinary(int num)
{
	int tempA = PORTA;
	int tempB = PORTB;
	
	tempA = tempA | 0b11111111;
	tempB = tempB | 0b00000110;
	
	if(num >= 256)
	{
		//turn on 10th LED
		tempB &= ~(1 << 2);
		num = num - 256;
	}
	if(num >= 128)
	{
		//turn on 9th LED
		tempB &= ~(1 << 1);
		num = num - 128;
	}
	if(num >= 64)
	{
		//turn on 8th LED
		tempA &= ~(1 << 7);
		num = num - 64;
	}
	if(num >= 32)
	{
		//turn on 7th LED
		tempA &= ~(1 << 6);
		num = num - 32;
	}
	if(num >= 16)
	{
		//turn on 6th LED
		tempA &= ~(1 << 5);
		num = num - 16;
	}
	if(num >= 8)
	{
		//turn on 5th LED
		tempA &= ~(1 << 4);
		num = num - 8;
	}
	if(num >= 4)
	{
		//turn on 4th LED
		tempA &= ~(1 << 3);
		num = num - 4;
	}
	if(num >= 2)
	{
		//turn on 3rd LED
		tempA &= ~(1 << 2);
		num = num - 2;
	}
	if(num >= 1)
	{
		//turn on 2nd LED
		tempA &= ~(1 << 1);
		num = num - 1;
	}
	
	//set to outputs
	PORTA = tempA;
	PORTB = tempB;
}

void runCoolAnimation(void)
{
	int animationVal = 1;

	for(int count = 0; count < 10; count++){
		displayAsBinary(animationVal);
		_delay_ms(50);

		animationVal = animationVal << 1;
	}

	for(int count = 0; count < 10; count++){
		animationVal = animationVal >> 1;

		displayAsBinary(animationVal);
		_delay_ms(50);
	}

	int animationSeries[10] = {0b1000000001, 0b0100000010, 0b0010000100, 0b0001001000, 0b0000110000, 0b0001001000, 0b0010000100, 0b0100000010, 0b1000000001, 0b0000000000};

	for(int seriesIndex = 0; seriesIndex < 10; seriesIndex++){
		displayAsBinary(animationSeries[seriesIndex]);
		_delay_ms(50);
	}
}

int main(void)
{
	// These set whether our pins are input (0) or output (1) for port A and B
	DDRA = 0b11111111;
	DDRB = 0b00000110;
	
	// Divide clock frequency by 128 because ADCs freak out at 8MHz
	ADCSRA |= 0b00000111;
	
	// ADC auto trigger enable
	//ADCSRA |= 1 << ADATE;
	
	// ADC enable
	//ADCSRA |= 1 << ADEN;
		
	// ADC start conversion
	//ADCSRA |= 1 << ADSC;
	
	//set internal 1.1V as ADC reference
	//ADMUX |= 1 << REFS1;
	
	// Our initial temperature output. Stripy!
	float output = 0b1010101010;
	int rawInput = 0;
	
	// TA = ambient temperature in degrees C, which is what we want to display
	float TA;
	
	// display all LEDs to signify start
	displayAsBinary(0b111111111);
	_delay_us(10000);
	
	displayAsBinary(0b000000000);
	_delay_us(10000);

	// cool animation
	//runCoolAnimation();

	//int x = 0;

    while(1)
    {
		// ADCH should grab the temperature
		// Do a moving average because it looks gross otherwise
		//rawInput = ADCL;
		//rawInput = rawInput + (ADCH<<8);
		//output = 0.9 * output + 0.1 * rawInput;
		
		//VOUT = TC*TA + V0C
		// TA = (VOUT - V0C) / TC
		// We also need to convert the output back to a voltage
		//TA = output/1024.0;
		//TA = TA*2.2;
		//TA = TA - 0.4;
		//TA = TA * 51.28;

		//displayAsBinary((int)(TA*10.0));
		
		int input = 0;
		char neg = 0;
		
		//change IO line to read
		DDRB = 0b00000110;
		_delay_us(100);
		
		//clock in data to uC from temp sensor
		for(int a=0; a<16; a++)
		{
			PORTA = PORTA | (0b00000001);
			_delay_us(1000);
			PORTA = PORTA & (0b11111110);
			_delay_us(1000);
			if(a==0)
			{
				neg = (PINB & (1<<0));
			}
			//else if(a==1)
			//{
				//do nothing
			//	;
			//}
			else if(a<10)
			{
				input = input + (1<<(9-a))*(PINB & (1<<0));
			}
			
		}
		if(neg == 1)
		{
			input = 0;
		}
		
		//change IO line to write
		DDRB = 0b00000111;
		_delay_us(100);
		
		//clock out config info
		PORTB = PORTB & 0b11111110;
		
		for(int a=0; a<16; a++)
		{
			PORTA = PORTA | (0b00000001);
			_delay_us(1000);
			PORTA = PORTA & (0b11111110);
			_delay_us(1000);
		}
		
		/*
		x = x + 1;
		if(x>=512)
		{
			x = 0;
		}
		*/
		displayAsBinary(input);
		
		_delay_us(500000);
    }
}