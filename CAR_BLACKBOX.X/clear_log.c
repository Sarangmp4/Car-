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
#include <xc.h>
#include "main.h"
#include"clcd.h"
#include "matrix_keypad.h"

void clear_log(char key)
{
    lap=0; //clear and store 
    overflow=0;
    
    
    clcd_print("   LOG CLEARED   ",LINE1(0));
    clcd_print("                 ",LINE2(0));
    
     /*storing time*/
    store[0]=time[0];
    store[1]=time[1];
    store[2]=time[3];
    store[3]=time[4];
    store[4]=time[6];
    store[5]=time[7];
    
    /*storing event mode*/
    store[6]='C';
    store[7]='L';
    
    /*storing speed*/

        store[8]=(adc_reg_val / 10) + 48;
        store[9]=(adc_reg_val % 10) + 48;
    
    if(key==16)
    {
        main_f=2;   
    }
   
}