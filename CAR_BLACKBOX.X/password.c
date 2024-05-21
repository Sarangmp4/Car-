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

int i=0;
int my_strcmp(char *one, char *two)
{   
    int i=0,flag=0;
    while(one[i])
    {
        if(one[i] != two[i])
        {
            flag= one[i]-two[i];
            break;
        }
    }
    return flag;
}
void password(char key)
{
    clcd_print(" Enter Password ", LINE1(0));
    char pass[4]="0000";
    char temp_password[4];
    
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
        }
       
}
