#include "uart.h"
#include <avr/io.h>



void UART_init(int BAUD_PRESCALER)
{
  
  /*Set baud rate */
  UBRR1H = (unsigned char)(BAUD_PRESCALER>>8);
  UBRR1L = (unsigned char)BAUD_PRESCALER;
  //Enable receiver and transmitter 
  UCSR1B = (1<<RXEN1)|(1<<TXEN1);
  /* Set frame format: 2 stop bits, 8 data bits */
  UCSR1C = (1<<UCSZ11) | (1<<UCSZ10); // 8 data bits
  UCSR1C |= (1<<USBS1); // 2 stop bits
}

void UART_send(unsigned char data)
{
  // Wait for empty transmit buffer
  while(!(UCSR1A & (1<<UDRE1)));
  // Put data into buffer and send data
  UDR1 = data;
  
}

void UART_putstring(char* StringPtr)
{
	while(*StringPtr != 0x00)
	{
		UART_send(*StringPtr);
		StringPtr++;
	}
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR1A & (1<<RXC1)) )
	;
	/* Get and return received data from buffer */
	return UDR1;
}