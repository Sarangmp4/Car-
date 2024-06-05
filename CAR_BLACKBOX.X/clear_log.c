/*
 * File:   clear_log.c
 * Author: sarang mp
 *
 * Created on 28 May, 2024, 8:14 PM
 */


extern char store[11];
extern char overflow;
extern char lap;
extern char main_f;
extern unsigned short adc_reg_val;
extern unsigned char time[9];
extern char i;
#include <xc.h>
#include "main.h"
#include"clcd.h"
#include "matrix_keypad.h"
#include "external_eeprom_2.h"

void clear_log(char key) {
    lap = 0; //clear and store 
    overflow = 0;


    clcd_print("   LOG CLEARED   ", LINE1(0));
    clcd_print("                 ", LINE2(0));


    if (key == 16) {



        /*storing time*/
        store[0] = (((time[0] - 48)*10)+(time[1] - 48));
        store[1] = (((time[3] - 48)*10)+(time[4] - 48));
        store[2] = (((time[6] - 48)*10)+(time[7] - 48));

        /*storing event mode*/
        store[3] = i;

        /*storing speed*/
        store[4] = adc_reg_val;

        for (char k = 0; k < 5; k++) {
            write_external_eeprom((k), store[k]);
        }
        main_f = 2;

    }



}