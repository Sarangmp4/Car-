#include <xc.h>
#include "uart.h"

void init_uart(void)
{
	/* Serial initialization */
	RX_PIN = 1;
	TX_PIN = 0;

	
	BRGH = 1;
	SPEN = 1;
	
	/* TX/RC7 and RX/RC6 act as serial port */
	/* Continous reception enable or disable */ 
	CREN = 1;
	
	

	/* Baud Rate Setting Register */
	/* Set to 10 for 115200, 64 for 19200 and 129 for 9600 */
	SPBRG = 129;
/* Receive Interruot Enable Bit (Enabling the serial port Interrupt) */
    RCIE = 1;

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
