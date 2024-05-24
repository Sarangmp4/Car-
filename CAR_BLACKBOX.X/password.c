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
#include <string.h>
#include "isr.h"

int i = 0;
char chance = 3; //variable for chance
extern char tick_count;

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
char pass[5] = "0000";
char temp_password[5];
int delay = 0;

void password(char key) {
    int flag = 0;
    clcd_print(" Enter Password ", LINE1(0));


    //providing non blocking delay for blink the '-'
    if (delay++ < 500) {
        clcd_putch('_', LINE2(i));
    } else if (delay > 500 && delay < 1000) {
        clcd_putch(' ', LINE2(i));
    } else
        delay = 0;

    if (key == MK_SW5) {
        temp_password[i] = '0';
        clcd_putch('*', LINE2(i)); //printing star for identify
        i++;

    } else if (key == MK_SW6) {
        temp_password[i] = '1';
        clcd_putch('*', LINE2(i));
        i++;
    }


    if (i == 4) {
        temp_password[i] = '\0';

        if (my_strcmp(pass, temp_password) == 0) {

            clcd_print("               ", LINE1(0));
            clcd_print("      SUCCESS     ", LINE2(0));
            while (1);

            /*password not matching*/
        } else {
            chance--; //decrementing chances
            i = 0; //for reattempt of the password
            if (chance == 0) {
                clcd_print(" Attempt Failed", LINE1(0));
                clcd_putch('0' + (tick_count / 100), LINE2(5));
                clcd_putch('0' + (tick_count / 10) % 10, LINE2(6));
                clcd_putch('0' + (tick_count % 10), LINE2(7));
                flag = 1;
            } else {

                clcd_print("   Try Again    ", LINE1(0));
                clcd_putch('0' + chance, LINE2(0));
                clcd_print(" Chances Left ", LINE2(1));
                for (unsigned long long int wait = 500000; wait--;);
                CLEAR_DISP_SCREEN;
            }
        }

    }


}
/*clcd_putch('0' + (tick_count / 100), LINE2(5));
clcd_putch('0' + (tick_count / 10) % 10, LINE2(6));
clcd_putch('0' + (tick_count % 10), LINE2(7));

 */

