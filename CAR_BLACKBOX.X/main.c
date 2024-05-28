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
    
    /*writing password to external eeprom*/
    write_external_eeprom(200,'0');
    write_external_eeprom(201,'0');
    write_external_eeprom(202,'0');
    write_external_eeprom(203,'0');


for(int j=0; j<4; j++) 
{
    pass[j] = read_external_eeprom(j+200);
}
    pass[4]='\0';

	
}
char key;
char pre_key;
unsigned short adc_reg_val;
extern char flag;
int key_time;


char main_f = 0, menu_f = 0;

void main(void) {
    init_config();

    

    while (1) {
        
        key = read_switches(LEVEL_CHANGE); //reading key
        
        if(key != ALL_RELEASED)
        {
            pre_key=key;
            key_time++;
            if(key_time == 1000)
            {
                key=key+10;
            }
            else
            {
                key=0;
            }
        }
        else if(key_time > 0 && key_time <1000)
        {
            key_time=0;
            key=pre_key;
        }
        else
        {
            key_time=0;
            key=0;
        }
        
        
        adc_reg_val = read_adc(CHANNEL4)/10.33; //reading adc value

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
        }
        else if(main_f == MENU_ENTER)
        {
            
            if(menu_f == VIEWLOG)
            {
                
                view_log(key);
            }
            
            else if(menu_f == DOWNLOADLOG)
            {
                download_log();
            }
            else if(menu_f == CLEARLOG)
            {
                clear_log(key);
            }/*
            else if(menu_f == SETTIME)
            {
                settime(key);
            }
            else if(menu_f == CHANGEPASS)
            {
                change_pass(key);
            }*/
        }
    }
}














