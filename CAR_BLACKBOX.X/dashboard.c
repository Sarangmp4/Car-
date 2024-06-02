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
#include "ds1307.h"
#include "i2c.h"

extern char key;
extern unsigned short adc_reg_val;
char  i = 0;
unsigned char clock_reg[3];
unsigned char time[9];

 /*Array of pointer for storing the gear and event names*/
    char *events[8] = {"ON", "GR", "GN", "G1", "G2", "G3", "G4", "C "};

void display_time(void) {
    clcd_print(time, LINE2(0));
}

 void get_time(void) {
    clock_reg[0] = read_ds1307(HOUR_ADDR);
    clock_reg[1] = read_ds1307(MIN_ADDR);
    clock_reg[2] = read_ds1307(SEC_ADDR);

    if (clock_reg[0] & 0x40) { /* 12 hr*/
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    } else {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    time[2] = ':';
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
    time[4] = '0' + (clock_reg[1] & 0x0F);
    time[5] = ':';
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
    time[7] = '0' + (clock_reg[2] & 0x0F);
    time[8] = '\0';
}
 
void dashboard() {
    /*printing the headings*/
    clcd_print("  TIME    EV  SP", LINE1(0));
    
   


    /*printing the events(gears)*/
    clcd_print(events[i], LINE2(10));

    /*incrementing i when mk_sw2 is pressed*/
    if (key == MK_SW2 && i < 6) {
            i++;
            store_event();
        
    }
    /*incrementing i when mk_sw2 is pressed*/
    if (key == MK_SW3 && i != 7) {
        if (i > 1) {
            i--;
            store_event();
        }
    }
    /*Jumping to collision when mk sw1 is pressed*/
    if (key == MK_SW1 ) {
        i = 7;
        store_event();
    }
    /*for exit from collison mode */
    if (i == 7 && key == MK_SW2) {
        i = 2;
        store_event();
    }


    /*displaying speed*/
        clcd_putch(((adc_reg_val / 10) + 48), LINE2(14));
        clcd_putch(((adc_reg_val  % 10) + 48), LINE2(15));
    

    /*----------------Displaying time-----------------------------------------------------*/
    get_time();
    display_time();

}
