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

/*
typedef signed int fix15 ;
#define multfix15(a,b) ((fix15)((((signed long long)(a))*((signed long long)(b)))>>15)) //multiply two fixed 16.15
#define float2fix15(a) ((fix15)((a)*32768.0)) // 2^15
#define fix2float15(a) ((float)(a)/32768.0)
#define absfix15(a) abs(a) 
#define int2fix15(a) ((fix15)(a << 15))
#define fix2int15(a) ((int)(a >> 15))
#define char2fix15(a) (fix15)(((fix15)(a)) << 15)
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)

#define NUM_SAMPLES 8          // the number of gathered samples (power of two)
#define NUM_SAMPLES_M_1 7    // the number of gathered samples minus 1
#define LOG2_NUM_SAMPLES 3     // log2 of the number of gathered samples
#define SHIFT_AMOUNT 13         // length of short (16 bits) minus log2 of number of samples

fix15 Sinewave[NUM_SAMPLES];
fix15 window[NUM_SAMPLES];

fix15 fr[NUM_SAMPLES]; // array of real part of samples (WINDOWED)
fix15 fi[NUM_SAMPLES]; // array of imaginary part of samples (WINDOWED)

void FFTfix(fix15 fr[], fix15 fi[]) {

	unsigned short m;   // one of the indices being swapped
	unsigned short mr ; // the other index being swapped (r for reversed)
	fix15 tr, ti ; // for temporary storage while swapping, and during iteration

	int i, j ; // indices being combined in Danielson-Lanczos part of the algorithm
	int L ;    // length of the FFT's being combined
	int k ;    // used for looking up trig values from sine table

	int istep ; // length of the FFT which results from combining two FFT's

	fix15 wr, wi ; // trigonometric values from lookup table
	fix15 qr, qi ; // temporary variables used during DL part of the algorithm

	//////////////////////////////////////////////////////////////////////////
	////////////////////////// BIT REVERSAL //////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// Bit reversal code below based on that found here:
	// https://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
	for (m=1; m<NUM_SAMPLES_M_1; m++) {
		// swap odd and even bits
		mr = ((m >> 1) & 0x5555) | ((m & 0x5555) << 1);
		// swap consecutive pairs
		mr = ((mr >> 2) & 0x3333) | ((mr & 0x3333) << 2);
		// swap nibbles ...
		mr = ((mr >> 4) & 0x0F0F) | ((mr & 0x0F0F) << 4);
		// swap bytes
		mr = ((mr >> 8) & 0x00FF) | ((mr & 0x00FF) << 8);
		// shift down mr
		mr >>= SHIFT_AMOUNT ;
		// don't swap that which has already been swapped
		if (mr<=m) continue ;
		// swap the bit-reveresed indices
		tr = fr[m] ;
		fr[m] = fr[mr] ;
		fr[mr] = tr ;
		ti = fi[m] ;
		fi[m] = fi[mr] ;
		fi[mr] = ti ;
	}

	//////////////////////////////////////////////////////////////////////////
	////////////////////////// Danielson-Lanczos //////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// Adapted from code by:
	// Tom Roberts 11/8/89 and Malcolm Slaney 12/15/94 malcolm@interval.com
	// Length of the FFT's being combined (starts at 1)
	L = 1 ;
	// Log2 of number of samples, minus 1
	k = LOG2_NUM_SAMPLES - 1 ;
	// While the length of the FFT's being combined is less than the number of gathered samples
	while (L < NUM_SAMPLES) {
		// Determine the length of the FFT which will result from combining two FFT's
		istep = L<<1 ;
		// For each element in the FFT's that are being combined . . .
		for (m=0; m<L; ++m) {
			// Lookup the trig values for that element
			j = m << k ;                         // index of the sine table
			wr =  Sinewave[j + NUM_SAMPLES/4] ; // cos(2pi m/N)
			wi = -Sinewave[j] ;                 // sin(2pi m/N)
			wr >>= 1 ;                          // divide by two
			wi >>= 1 ;                          // divide by two
			// i gets the index of one of the FFT elements being combined
			for (i=m; i<NUM_SAMPLES; i+=istep) {
				// j gets the index of the FFT element being combined with i
				j = i + L ;
				// compute the trig terms (bottom half of the above matrix)
				tr = multfix15(wr, fr[j]) - multfix15(wi, fi[j]) ;
				ti = multfix15(wr, fi[j]) + multfix15(wi, fr[j]) ;
				// divide ith index elements by two (top half of above matrix)
				qr = fr[i]>>1 ;
				qi = fi[i]>>1 ;
				// compute the new values at each index
				fr[j] = qr - tr ;
				fi[j] = qi - ti ;
				fr[i] = qr + tr ;
				fi[i] = qi + ti ;
			}
		}
		--k ;
		L = istep ;
	}
}
*/

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

		// convert to frequency domain

		// send frequencies to ESP32 via SPI
	}
}