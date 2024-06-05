/*
 * File:   set_time.c
 * Author: sarang mp
 *
 * Created on 31 May, 2024, 11:38 AM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "ds1307.h"
#include "external_eeprom_2.h"



char hr, min, sec;
char pos_flag = 0, t_flag = 0;
extern unsigned char time[9];
extern unsigned short adc_reg_val;
extern char store[11];
extern unsigned char clock_reg[3];
extern char main_f;
extern char lap;
extern char i;

void settime(char key) {

    clcd_print("     HH:MM:SS    ", LINE1(0));
    if (t_flag == 0) {
        hr = ((time[0] - 48)*10 + (time[0] - 48));
        min = ((time[3] - 48)*10 + (time[4] - 48));
        sec = ((time[6] - 48)*10 + (time[7] - 48));
        t_flag = 1;
    }

    clcd_putch('0' + (hr / 10), LINE2(5));
    clcd_putch('0' + (hr % 10), LINE2(6));

    clcd_putch(':', LINE2(7));
    clcd_putch('0' + (min / 10), LINE2(8));
    clcd_putch('0' + (min % 10), LINE2(9));

    clcd_putch(':', LINE2(10));
    clcd_putch('0' + (sec / 10), LINE2(11));
    clcd_putch('0' + (sec % 10), LINE2(12));

    if (key == MK_SW5) {
        if (pos_flag == 0) {
            if (sec == 59) {
                sec = 0;
            } else
                sec++;

        } else if (pos_flag == 1) {
            if (min == 59) {
                min = 0;
            }
            min++;
        } else if (pos_flag == 2) {
            if (hr == 23) {
                hr = 0;
            }
            hr++;
        }
    } else if (key == MK_SW6) {
        pos_flag++;

        if (pos_flag == 3) {
            pos_flag = 0;
        }
    }
    if (key == 15) {
        /*saving the time*/

        write_ds1307(HOUR_ADDR, (hr / 10) << 4 | (hr % 10));
        write_ds1307(MIN_ADDR, (min / 10) << 4 | (min % 10));
        write_ds1307(SEC_ADDR, (sec / 10) << 4 | (sec % 10));


        /*storing event*/
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
        lap++;

        main_f = 2;

    }
    if (key == 16) {
        main_f = 2;
    }

}

