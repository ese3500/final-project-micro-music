// configure baud rate of 1 MHz
#define F_CPU 16000000UL
#define BAUD_RATE 1000000
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

// include relevant libraries
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "kiss_fft.h"

// define macros for FFT library
#define nfft 32 		// want 32 samples
#define IS_INVERSE 0	// time to frequency domain

// initialize global variables
int high = 0;
int on = 1;
int counter = 0;
int b1JustPressed = 1;
int b0JustPressed = 1;
int b2JustPressed = 1;

// declare FFT objects
kiss_fft_cfg cfg;
kiss_fft_cpx cx_in[32];
kiss_fft_cpx cx_out[32];


// UART FUNCTIONS (modified from uart.c and uart.h provided earlier in the semester)

void UART_init(int BAUD_PRESCALER)
{
  // Set baud rate (same as previous)
  UBRR1H = (unsigned char)(BAUD_PRESCALER>>8);
  UBRR1L = (unsigned char)BAUD_PRESCALER;

  // This part is different. Enable receiver for RXEN1 (instead of RXEN0 and TXEN0), which is for the micro-USB port
  UCSR1B = (1<<RXEN1);
  
  // same as previous
  UCSR1C = (1<<UCSZ11) | (1<<UCSZ10); // 8 data bits
  UCSR1C |= (1<<USBS1); // 2 stop bits
}

// This function is the same as the one provided
void UART_send(unsigned char data)
{
  // Wait for empty transmit buffer
  while(!(UCSR1A & (1<<UDRE1)));
  // Put data into buffer and send data
  UDR1 = data;
  
}

// This function is the same as the one provided
void UART_putstring(char* StringPtr)
{
	while(*StringPtr != 0x00)
	{
		UART_send(*StringPtr);
		StringPtr++;
	}
}

void Initialize()
{
	// configure UART to baud rate of 1 MHz
	UART_init(BAUD_PRESCALER);
	
	cli();

	// configure FFT
	cfg = kiss_fft_alloc(nfft,IS_INVERSE,NULL,NULL);
	
	// GPIO configuration
	DDRD |= (1<<DDRD0);
	DDRC |= (1<<DDRC5);
	DDRD &= ~(1<<DDRD5);
	DDRB &= ~(1<<DDRB0);
	DDRC &= ~(1<<DDRC2);
	
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
	
	// configure pin change interrupts
	PCICR |= (1<<PCIE0);
	PCICR |= (1<<PCIE1);
	PCICR |= (1<<PCIE2);

	// change color of audio visualizer
	PCMSK0 |= (1<<PCINT0);

	// turn off screen and stop polling
	PCMSK1 |= (1<<PCINT10);

	// change level of audio visualizer
	PCMSK2 |= (1<<PCINT21);
	
	sei();
}

ISR(PCINT2_vect) {
	if (b2JustPressed) {
		// change high variable to its opposite (see its use in main)
		high = !high;
	}

	// ensure interrupt doesn't execute again when button unpressed
	b2JustPressed = !b2JustPressed;
}

ISR(PCINT1_vect) {
	if (b1JustPressed) {
		// pull up a pin that will cause ESP32 to change colors
		PORTC &= ~(1<<PORTC5);
		_delay_ms(50);
		PORTC |= (1<<PORTC5);
	}

	// ensure interrupt doesn't execute again when button unpressed
	b1JustPressed = !b1JustPressed;
}

ISR(PCINT0_vect) {
	if (b0JustPressed) {
		// change on variable to its opposite, so ADC, FFT and UART in main will stop
		on = !on;

		// pull up a pin that will cause ESP32 to clear the screen
		PORTD &= ~(1<<PORTD0);
		_delay_ms(50);
		PORTD |= (1<<PORTD0);
	}

	// ensure interrupt doesn't execute again when button unpressed
	b0JustPressed = !b0JustPressed;
}

int main(void)
{
	Initialize();
	
	while (1) {
		// check on boolean (for on/off button)
		if (on) {
			int i = 0;
			char string[10];

			// fill array of amplitudes using ADC
			while (i < 32) {
				cx_in[i].r = ADC;
				cx_in[i].i = 0;
				i++;

				_delay_us(30);
				// delay to match sampling rate of ADC
			}
			
			// perform FFT using Kiss FFT
			kiss_fft( cfg , cx_in , cx_out );
			
			// iterate through each frequency obtained from FFT
			for (int j = 0; j < 16; j++) {
				// calculate magnitude of the frequency (how prominent it is compared to other frequencies)
				int mag = sqrt((double)(cx_out[j].i * cx_out[j].i) + (double)(cx_out[j].r * cx_out[j].r));
				int normalized;

				// check high boolean (for high/low level audio visualization)
				if (high) {
					// normalize frequency to be between 4 through 9
					if (mag > 4400 * scaler) {
						normalized = 9;
						} else if (mag > 4200) {
						normalized = 9;
						} else if (mag > 3600) {
						normalized = 9;
						} else if (mag > 3000) {
						normalized = 9;
						} else if (mag > 2300) {
						normalized = 8;
						} else if (mag > 1600) {
						normalized = 7;
						} else if (mag > 1000) {
						normalized = 6;
						} else if (mag > 400) {
						normalized = 5;
						} else {
						normalized = 4;
					}
				} else {
					// normalize frequqency to be between 1 through 9
					if (mag > 4400 * scaler) {
						normalized = 9;
						} else if (mag > 4200) {
						normalized = 8;
						} else if (mag > 3600) {
						normalized = 7;
						} else if (mag > 3000) {
						normalized = 6;
						} else if (mag > 2300) {
						normalized = 5;
						} else if (mag > 1600) {
						normalized = 4;
						} else if (mag > 1000) {
						normalized = 3;
						} else if (mag > 400) {
						normalized = 2;
						} else {
						normalized = 1;
					}
				}

				// send frequency prominence via UART
				sprintf(string, "%d", normalized);
				UART_putstring(string);
			}

			// send 'x' character through UART, which allows ESP32 to delineate strings of frequencies
			sprintf(string,"x");
			UART_putstring(string);
		}
	}
}