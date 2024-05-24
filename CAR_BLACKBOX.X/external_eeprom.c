#include <xc.h>
#include "main.h"
#include "i2c.h"
#include "external_eeprom_2.h"


/* 
 * DS1307 Slave address
 * A0  -  Write Mode
 * A1  -  Read Mode
 */


void write_external_eeprom(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(SLAVE_WRITE);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
    for(int i=3000; i--;);
}

unsigned char read_external_eeprom(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(SLAVE_WRITE);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(SLAVE_READ);
	data = i2c_read();
	i2c_stop();

	return data;
}