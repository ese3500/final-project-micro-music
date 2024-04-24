#define F_CPU 16000000UL
#define BAUD_RATE 1000000
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "inc/uart.h"

void Initialize()
{
	UART_init(BAUD_PRESCALER);

	cli();
	
	// GPIO configuration
	DDRB |= (1<<DDRB1);
	DDRD &= ~(1<<DDRD5);
	DDRB |= (1<<DDRB5);
	PORTD |= (1<<PORTD5);
	
	// ADC configuration
	PRR0 &= ~(1<<PRADC);
	
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	
	ADCSRA |= (1<<ADPS0);
	ADCSRA |= (1<<ADPS1);
	ADCSRA &= ~(1<<ADPS2);
	
	ADMUX &= ~(1<<MUX0);
	ADMUX &= ~(1<<MUX1);
	ADMUX &= ~(1<<MUX2);
	ADMUX &= ~(1<<MUX3);
	
	ADCSRA |= (1<<ADATE);
	
	ADCSRB &= ~(1<<ADTS0);
	ADCSRB &= ~(1<<ADTS1);
	ADCSRB &= ~(1<<ADTS2);
	
	DIDR0 |= (1<<ADC0D);
	
	ADCSRA |= (1<<ADEN);
	
	ADCSRA |= (1<<ADSC);
	sei();
}

void clone(int* clonedArr[], int* arr[]) {
	// cloning an array (not needed for now)
	for (int i = 0; i < 64; i++) {
		clonedArr[i] = arr[64];
	}
}

void fft(int* amplitudes[]) {
	// FFT (convert from time domain to frequency domain)
}

void send(int* arr[]) {
	// send arr via SPI
}

int main(void)
{
	Initialize();

	// declare array of amplitudes
	int arr[64];

	while (1) {
		int i = 0;

		// fill array of amplitudes using ADC
		while (i < 64) {
			arr[i] = ADC;
			i++;
			_delay_us(30);
		}

		// convert to frequency domain
		fft(arr);

		// send frequencies to ESP32 via SPI
		send(arr);
	}
}