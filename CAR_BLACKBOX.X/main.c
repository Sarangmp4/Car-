/*
 * File:   main.c
 * Author: sarang mp
 *
 * Created on 20 May, 2024, 8:12 AM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "adc.h"
#include "ds1307.h"
#include "i2c.h"
#include "timer0.h"
#include "external_eeprom_2.h"

char pass[5];

void init_config(void) {
    init_clcd();
    init_matrix_keypad();
    init_adc();
    init_i2c();
    init_ds1307();
	init_timer0();
    write_external_eeprom(200,'0');
    write_external_eeprom(201,'0');
    write_external_eeprom(202,'0');
    write_external_eeprom(203,'0');


for(int j=0; j<4; j++) 
{
    pass[j] = read_external_eeprom(j);
}

	
}
char key;
unsigned short adc_reg_val;
extern char flag;

void main(void) {
    init_config();

    char main_f = 0, menu_f = 0;

    while (1) {
        key = read_switches(STATE_CHANGE); //reading key
        adc_reg_val = read_adc(CHANNEL4); //reading adc value

        if (main_f == DASHBOARD) {
            dashboard();
            if (key == MK_SW5) { 
                CLEAR_DISP_SCREEN;
                main_f = 1;   
            }
        } else if (main_f == PASSWORD) {
            password(key);
            if(flag==1)
            {
                CLEAR_DISP_SCREEN;
                main_f=2;
            }
        }
        else if(main_f == MENU)
        {
            menu(key);
            clcd_print("Menu Entered", LINE1(0));
        }
    }
}














