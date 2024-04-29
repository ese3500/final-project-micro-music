#define F_CPU 16000000UL
#define BAUD_RATE 1000000
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "kiss_fft.h"
#include "inc/uart.h"



#define nfft 16
#define IS_INVERSE 0

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

int main(void)
{
	Initialize();
	
	kiss_fft_cfg cfg = kiss_fft_alloc(nfft,IS_INVERSE,NULL,NULL);
	kiss_fft_cpx cx_in[16];
	kiss_fft_cpx cx_out[16];

	while (1) {
		int i = 0;
		char string[10];
		// fill array of amplitudes using ADC
		while (i < 16) {
			cx_in[i].r = ADC;
			cx_in[i].i = 0;
			i++;
			_delay_us(30);
		}
		
		kiss_fft( cfg , cx_in , cx_out );
		
		for (int j = 0; j < 8; j++) {
			int mag = sqrt((double)(cx_out[j].i * cx_out[j].i) + (double)(cx_out[j].r * cx_out[j].r));
			int normalized;
			if (mag > 5000) {
				normalized = 9;
			} else if (mag > 4444) {
				normalized = 8;
			} else if (mag > 3888) {
				normalized = 7;
			} else if (mag > 3333) {
				normalized = 6;
			} else if (mag > 2777) {
				normalized = 5;
			} else if (mag > 2222) {
				normalized = 4;
			} else if (mag > 1666) {
				normalized = 3;
			} else if (mag > 1111) {
				normalized = 2;
			} else if (mag > 555) {
				normalized = 1;
			} else {
				normalized = 0;
			}
			sprintf(string, "%d", normalized);
			UART_putstring(string);
		}
		sprintf(string,"x");
		UART_putstring(string);

	}
}
