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

char store[5];
extern unsigned char time[9];
extern char *events[8];
extern char i;
char lap=0;
char overflow=0;
extern unsigned short adc_reg_val;

void store_event()
{
    /*storing time*/
    store[0]=(((time[0]-48)*10)+(time[1]-48)); 
    store[1]=(((time[3]-48)*10)+(time[4]-48));
    store[2]=(((time[6]-48)*10)+(time[7]-48));
   
    /*storing event mode*/
    store[3]=i;
    
    /*storing speed*/

        store[4]=adc_reg_val;
        
    for(char k=0; k<5; k++)
    {
        write_external_eeprom( (lap*10+k),store[k]);
    }
    
//    lap++;
    if(lap==10)
    {
        lap=0;
        overflow=1;
    }
}
