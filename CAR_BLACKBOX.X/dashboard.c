/*
 * File:   dashboard.c
 * Author: sarang mp
 *
 * Created on 20 May, 2024, 8:45 PM
 */


#include <xc.h>
#include "main.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "adc.h"

extern char key;
extern short adc_reg_val;
int i = 0;

void dashboard() {
    /*Array of pointer for storing the gear and event names*/
    char *events[8] = {"ON", "GR", "GN", "G1", "G2", "G3", "G4", "C "};


    /*printing the events(gears)*/
    clcd_print(events[i], LINE2(10));

    /*incrementing i when mk_sw2 is pressed*/
    if (key == MK_SW2) {
        if (i < 6) {
            i++;
        }
    }
    /*incrementing i when mk_sw2 is pressed*/
    if (key == MK_SW3) {
        if (i > 1) {
            i--;
        }
    }
    /*Jumping to collision when mk sw1 is pressed*/
    if (key == MK_SW1) {
        i = 7;
    }
    /*for exit from collison mode */
    if (i == 7 && (key == MK_SW2 || key == MK_SW3)) {
        i = 2;
    }


    /*displaying speed*/
    adc_reg_val = read_adc(CHANNEL4);
    if (adc_reg_val < 100) //maximum speed upto 99
    {
        clcd_putch(((adc_reg_val / 10) + 48), LINE2(14));
        clcd_putch(((adc_reg_val % 10) + 48), LINE2(15));
    }

}