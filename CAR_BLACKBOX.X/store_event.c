/*
 * File:   store_event.c
 * Author: sarang mp
 *
 * Created on 26 May, 2024, 11:30 AM
 */


#include <xc.h>
#include "main.h"
#include "external_eeprom_2.h"
#include "i2c.h"

char store[11];
extern unsigned char time[9];
extern char *events[8];
extern char i;
char lap=0;
char overflow=0;
extern unsigned short adc_reg_val;

void store_event()
{
    /*storing time*/
    store[0]=time[0];
    store[1]=time[1];
    store[2]=time[3];
    store[3]=time[4];
    store[4]=time[6];
    store[5]=time[7];
    
    /*storing event mode*/
    store[6]=events[i][0];
    store[7]=events[i][1];
    
    /*storing speed*/

        store[8]=(adc_reg_val / 10) + 48;
        store[9]=(adc_reg_val % 10) + 48;
        
    for(char k=0; k<10; k++)
    {
        write_external_eeprom( (lap*10+k),store[k]);
    }
    
    lap++;
    if(lap==10)
    {
        lap=0;
        overflow=1;
    }
}
