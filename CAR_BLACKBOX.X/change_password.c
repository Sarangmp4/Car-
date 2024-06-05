/*
 * File:   change_password.c
 * Author: sarang mp
 *
 * Created on 29 May, 2024, 8:40 PM
 */


#include <xc.h>
#include "main.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "external_eeprom_2.h"


extern char pass[5];
char temp1[5], temp2[5];
extern char main_f;
char ind = 0;
int del = 0;
char reset_flag = 0;
extern char i;
extern unsigned short adc_reg_val;



extern char store[11];
extern unsigned char time[9];
extern char lap;

int my_strcp(char *one, char *two) {
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

void change_pass(char key) {
    if (reset_flag == 0) {
        clcd_print("  New Password : ", LINE1(0));


        if (del++ < 500) {
            clcd_putch('_', LINE2(ind));
        } else if (del > 500 && del < 1000) {
            clcd_putch(' ', LINE2(ind));
        } else
            del = 0;

        if (key == MK_SW5) {
            temp1[ind] = '0';
            clcd_putch('*', LINE2(ind));
            ind++;
        } else if (key == MK_SW6) {
            temp1[ind] = '1';
            clcd_putch('*', LINE2(ind));
            ind++;
        }
        if (ind == 4) {
            temp1[ind] = '\0';
            reset_flag = 1;
            ind = 0;
            CLEAR_DISP_SCREEN;
        }
    } else if (reset_flag == 1) {
        clcd_print("  Retype Password : ", LINE1(0));

        if (del++ < 500) {
            clcd_putch('_', LINE2(ind));
        } else if (del > 500 && del < 1000) {
            clcd_putch(' ', LINE2(ind));
        } else
            del = 0;

        if (key == MK_SW5) {
            temp2[ind] = '0';
            clcd_putch('*', LINE2(ind));
            ind++;
        } else if (key == MK_SW6) {
            temp2[ind] = '1';
            clcd_putch('*', LINE2(ind));
            ind++;
        }
        if (ind == 4) {
            temp2[ind] = '\0';
            if (my_strcp(temp1, temp2) == 0) {
                pass[0] = temp1[0];
                write_external_eeprom((200), temp1[0]);
                pass[1] = temp1[1];
                write_external_eeprom((201), temp1[1]);
                pass[2] = temp1[2];
                write_external_eeprom((202), temp1[2]);
                pass[3] = temp1[3];
                write_external_eeprom((203), temp1[3]);

                clcd_print(" Password Change  ", LINE1(0));
                clcd_print("   SUCCESSFULL  ", LINE2(0));
                for (unsigned long int delay = 200000; delay--;);
                ind = 0;
                reset_flag = 0;


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

//                lap++;

                main_f = 2;
            } else {
                main_f = 2;
            }
        }


    }
}

//write_external_eeprom( (ind+200) ,'0');