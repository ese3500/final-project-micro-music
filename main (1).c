#define F_CPU 16000000UL
#define BAUD_RATE 1000000
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "inc/uart.h"

// int notes[8] = {1, 2, 3, 4, 5, 6, 7, 8};
int notes[25] = {1, 3, 5, 7, 8, 6, 6, 0, 2, 4, 6, 7, 5, 5, -1, 1, 3, 5, 6, 4, 4, 3, 2, 3, 1};// 
// int freq[16];
char amplitudeBuffer[100];
// int notes[27] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 1, 1, 1};
char String[10];
int counter = 0;
int i = 0;

unsigned posY = 0; 
int qSize = 25;
int arr[25];
int qStart = 0;
int numElements = 0;
int qPointer = 0;

void enqueue(int element) {
	
	if (numElements < qSize) {
		if (qPointer >= qSize - 1) {
			qPointer = 0;
			
			} else {
			qPointer++;
		}
		arr[qPointer] = element;
		numElements++;
	}
	
}

int dequeue() {
	if (numElements > 0) {
		numElements--;
		if (qPointer == 0) {
			qPointer = qSize - 1;
			} else {
			qPointer = qPointer - 1;
		}
		int posPrev = qStart;
		if( qStart == qSize - 1) {
			qStart = 0;
			} else {
			qStart++;
		}
		
		return arr[posPrev];
	}
	return 0;
}

void Initialize()
{
	UART_init(BAUD_PRESCALER);
	cli();
	
	DDRB |= (1<<DDRB1);
	DDRD &= ~(1<<DDRD5);
	DDRB |= (1<<DDRB5);
	PORTD |= (1<<PORTD5);
	PCICR |= (1<<PCIE2);
	PCMSK2 |= (1<<PCINT21);
	
	TCCR1B &= ~(1<<CS10);
	TCCR1B |= (1<<CS11);
	TCCR1B &= ~(1<<CS12);
	
	TCCR1A |= (1<<COM1A0);
	TCCR1A &= ~(1<<COM1A1);
	
	TCCR1A |= (1<<WGM10);
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12);
	TCCR1B |= (1<<WGM13);
	
	TCCR0B &= ~(1<<CS00);
	TCCR0B &= ~(1<<CS01);
	TCCR0B |= (1<<CS02);
	
	TCCR0A |= (1<<COM0A0);
	
	TCCR0A |= (1<<WGM00);
	TCCR0A |= (1<<WGM01);
	TCCR0B &= ~(1<<WGM02);
	OCR0A = 249;
	TIMSK0 |= (1<<OCIE0A);
	sei();
	
	repopulate();
}

ISR(PCINT2_vect) {
	PORTB ^= (1<<PORTB5);
	_delay_ms(50);
}

int getOcr(int freq) {
	return (16000000 / (2 * 8 * freq)) - 1;
}

int getFreq(int note) {
	switch (note) {
		case -1: return 220;
		case 0: return 247;
		case 1: return 262;
		case 2: return 294;
		case 3: return 330;
		case 4: return 349;
		case 5: return 392;
		case 6: return 440;
		case 7: return 494;
		case 8: return 523;
		default: return 1000;
	}
}

void flush() {
	//handle flushing
}

void recieveAmplitude() {
	char soundAmplitude = USART_Receive(); 
	amplitudeBuffer[posY] = soundAmplitude; 
	if (posY >= 100) {
		flush();
	} else {
		posY++; 
	}
}



void createFrequency() {
	
}

void repopulate() {
	for (int i = 0; i  < 25; i++) {
		enqueue(notes[i]);
	}
}

int main(void)
{
	Initialize();
	int counter; 
	while (1) {
		
		
		//recieveAmplitude();
		int note = dequeue();
		int freq = getFreq(note);
		int pos;
		if (freq <= 100) {
			pos = 0;
			} else if (freq <= 4000) {
			pos = (61 * freq)/ 3900;
			} else {
			pos = ((2 * freq) / 18000) + 61;
		}
		sprintf(String, "%dx", pos);
		UART_putstring(String);
		OCR1A = getOcr(freq);
		OCR1B = OCR1A;
		if (PINB & (1<<PINB5)) {
			_delay_ms(50);
			} else {
			_delay_ms(10);
		}
		
		if (counter == 0) {
			counter = 24;
			repopulate();
		} else {
			counter--;
		}
		
		_delay_ms(600);
	}
}