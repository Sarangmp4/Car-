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

void init_config(void) {
    init_clcd();
    init_matrix_keypad();
    init_adc();
    init_i2c();
    init_ds1307();
    
    PEIE = 1;

	init_timer0();

	GIE = 1;
}
char key;
unsigned short adc_reg_val;

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
            
        }
    }
}














