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


char hr, min, sec;
char pos_flag = 0, t_flag = 0;
extern unsigned char time[9];
extern unsigned short adc_reg_val;
extern char store[11];
extern unsigned char clock_reg[3];
extern char main_f;

void settime(char key) {


    clcd_print("     HH:MM:SS    ", LINE1(0));
    if (t_flag == 0) {
        hr = ((time[0] - 48)*10 + (time[0] - 48));
        min = ((time[3] - 48)*10 + (time[4] - 48));
        sec = ((time[6] - 48)*10 + (time[7] - 48));
        t_flag = 1;
    }

    clcd_putch('0' + (hr / 10), LINE2(0));
    clcd_putch('0' + (hr % 10), LINE2(1));

    clcd_putch(':', LINE2(2));
    clcd_putch('0' + (min / 10), LINE2(3));
    clcd_putch('0' + (min % 10), LINE2(4));

    clcd_putch(':', LINE2(5));
    clcd_putch('0' + (sec / 10), LINE2(6));
    clcd_putch('0' + (sec % 10), LINE2(7));

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
        clock_reg[0] = ((hr / 10) << 4) | (hr % 10);
        clock_reg[0] = ((min / 10) << 4) | (min % 10);
        clock_reg[0] = ((sec / 10) << 4) | (sec % 10);

        /*storing event*/
        /*storing time*/
        store[0] = time[0];
        store[1] = time[1];
        store[2] = time[3];
        store[3] = time[4];
        store[4] = time[6];
        store[5] = time[7];

        /*storing event mode*/
        store[6] = 'S';
        store[7] = 'T';

        /*storing speed*/
        store[8] = (adc_reg_val / 10) + 48;
        store[9] = (adc_reg_val % 10) + 48;

        main_f = 2;

    }
    if (key == 16) {
        main_f = 2;
    }

}

