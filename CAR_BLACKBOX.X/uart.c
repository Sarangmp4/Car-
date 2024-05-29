#include <xc.h>
#include "uart.h"

void init_uart(void)
{
	/* Serial initialization */
	RX_PIN = 1;
	TX_PIN = 0;

	/* TXSTA:- Transmitor Status and control Register */
	/* 9bit TX enable or disable bit */ 
	TX9 = 0;
	/* UART Tarsmition enable bit */
	TXEN = 1;
	/* Synchronous or Asynchronous mode selection */
	/* Asynchronous */
	SYNC = 0;
	/* Send the Break character bit */
	SENDB = 0;
	/* Low or High baud rate selection bit */
	/* High Baud Rate */
	BRGH = 1;

	/* RCSTA :- Recepition Status and control Register */
	/* TX/RC7 and RX/RC6 act as serial port */ 
	SPEN = 1;
	/* 9bit RX enable or disable bit */
	RX9 = 0;
	/* Continous reception enable or disable */ 
	CREN = 1;

	/* BAUDCTL:- Baud rate control register */
	/* Auto baud detection overflow bit */
	ABDOVF = 0;
	/* 16bit baud generate bit */ 
	BRG16 = 0;
	/* Wakeup enable bit */
	WUE = 0;
	/* Auto baud detect enable bit */
	ABDEN = 0;

	/* Baud Rate Setting Register */
	/* Set to 10 for 115200, 64 for 19200 and 129 for 9600 */
	SPBRG = 129;

    
	/* TX interrupt enable bit */
	TXIE = 1;
	/* TX interrupt flag bit */
	TXIF = 0;
	/* RX interrupt enable bit */
	RCIE = 1;
	/* RX interrupt enable bit */
	RCIF = 0;
}
/*function to transmit charcter from mc to laptop*/
void putch(unsigned char byte) 
{
	/* Output one byte */
	/* Set when register is empty */
    /*TXIF = 0 means TXREG is not free TXIF=1 means it is free*/
	while(!TXIF) //act as while(1) loop  
	{
		continue;
	}
	TXREG = byte;
} 
/*function fro transmitting string from mc to laptop*/
int puts(const char *s)
{
	while(*s)	//execute upto null character	
	{
		putch(*s++);	
	}
	return 0;
}
/*function to read recived data from RCREG bit
 recieve data send from laptop*/
unsigned char getch(void)
{
	/* Retrieve one byte */
	/* Set when register is not empty */
	while(!RCIF) 
	{
		continue;
	}
	return RCREG;
}
/*function to recieve and transmit back data */
unsigned char getche(void)
{
	unsigned char c;

	putch(c = getch());

	return (c);
}
