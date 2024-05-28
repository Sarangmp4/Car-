/*
 * File:   password.c
 * Author: sarang mp
 *
 * Created on 20 May, 2024, 9:48 PM
 */


#include <xc.h>
#include "main.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "adc.h"
#include "isr.h"

int index = 0;
char chance = 2; //variable for chance
extern char tick_count;

int delay = 0;
char flag = 0;
char temp_password[5];  
extern char pass[5];

int my_strcmp(char *one, char *two) {
    int k = 0, last = 0;
    while (one[k] != '\0') {
        if (one[k] != two[k]) {
            last = one[k] - two[k];
            break;
        }
        k++;
    }
    return last;
}

void password(char key) {

    clcd_print(" Enter Password ", LINE1(0));

    //providing non blocking delay for blink the '-'
    if (delay++ < 500) {
        clcd_putch('_', LINE2(index));
    } else if (delay > 500 && delay < 1000) {
        clcd_putch(' ', LINE2(index));
    } else
        delay = 0;

    if (key == MK_SW5) {
        temp_password[index] = '0';
        clcd_putch('*', LINE2(index)); //printing star for identify
        index++;

    } else if (key == MK_SW6) {
        temp_password[index] = '1';
        clcd_putch('*', LINE2(index));
        index++;
    }


    if (index == 4) {
        temp_password[index] = '\0';
        if (my_strcmp(pass,temp_password) == 0) {

            clcd_print("               ", LINE1(0));
            clcd_print("      SUCCESS     ", LINE2(0));
            flag = 1;
            return;


        } else {

            if (chance == 0) {
                /* Enabling timer0 overflow interrupt */

                TMR0IE = 1;
                GIE = 1;
                PEIE = 1;

                clcd_print(" System Blocked", LINE1(0));
                clcd_print("     ", LINE2(0));
                clcd_putch('0' + (tick_count / 100), LINE2(5));
                clcd_putch('0' + (tick_count / 10) % 10, LINE2(6));
                clcd_putch('0' + (tick_count % 10), LINE2(7));
                for (unsigned long int delay = 200000; delay--;);

                if (tick_count == 0) {
                    chance = 2;
                    index = 0;
                    CLEAR_DISP_SCREEN;
                }

            } else {

                clcd_print("   Try Again    ", LINE1(0));
                clcd_putch('0' + chance, LINE2(0));
                clcd_print(" Chances Left ", LINE2(1));
                for (unsigned long long int wait = 400000; wait--;);
                chance--;
                index = 0;
                CLEAR_DISP_SCREEN;


            }
        }

    }


}


