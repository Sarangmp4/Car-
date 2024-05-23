
#include <xc.h>

void init_i2c(void)
{
	/* Set SCL and SDA pins as inputs */
	TRISC3 = 1;
	TRISC4 = 1;
	/* Set I2C master mode */
	SSPCON1 = 0x28;

	SSPADD = 0x31;
	/* Use I2C levels, worked also with '0' */
	CKE = 0;
	/* Disable slew rate control  worked also with '0' */
	SMP = 1;
	/* Clear SSPIF interrupt flag */
	SSPIF = 0;
	/* Clear bus collision flag */
	BCLIF = 0;
}

void i2c_idle(void) //for checkig each condition is idle
{
	while (!SSPIF);
	SSPIF = 0;
}

void i2c_ack(void) //for checking acknowledgement
{
	if (ACKSTAT)
	{
		/* Do debug print here if required */
	}
}

void i2c_start(void) //start condition
{
	SEN = 1;
	i2c_idle(); //checking is it completed or not
}

void i2c_stop(void) //stop condition
{
	PEN = 1;
	i2c_idle();
}

void i2c_rep_start(void) //repeat start
{
	RSEN = 1;
	i2c_idle();
}

void i2c_write(unsigned char data)  //for transmission of data
{
	SSPBUF = data; //load to sspbuf for transmission
	i2c_idle();
}

void i2c_rx_mode(void)  //eneabling reciving
{
	RCEN = 1;
	i2c_idle();
}

void i2c_no_ack(void)
{
	ACKDT = 1;  // not acknowlwdge 
	ACKEN = 1;  //
}

unsigned char i2c_read(void) //read mode
{
	i2c_rx_mode();
	i2c_no_ack();

	return SSPBUF; //returning the data
}