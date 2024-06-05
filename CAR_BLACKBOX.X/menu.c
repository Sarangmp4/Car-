/*
 * File:   menu.c
 * Author: sarang mp
 *
 * Created on 25 May, 2024, 11:29 AM
 */


#include <xc.h>
#include "main.h"
#include "matrix_keypad.h"
#include "clcd.h"

char *logs[5]= {" View Log      "," Download log   "," Clear Log       " ," Set time       "," Change Passwrd"};
extern char main_f, menu_f;
extern char key;
char star_flag=0;
char star_index=0;
char log_index=0;
short press_delay=0;
void menu(char key)
{
    clcd_print(logs[log_index], LINE1(1));
    clcd_print(logs[(log_index+1)], LINE2(1));
    
    if(star_flag==0)
    {
        clcd_putch('*',LINE1(0));
        clcd_putch(' ',LINE2(0));
    }
    else
    {
        clcd_putch(' ',LINE1(0));
        clcd_putch('*',LINE2(0));
    }
    
    
    if(key==MK_SW5 )
    {
        if(star_flag==0)
        {
            star_flag=1;
            star_index++;
        }
        else if(log_index<3)
        {
            log_index++;
            star_index++;
        }
        
    }
    if(key==MK_SW6  )
    {
         if(star_flag==1)
         {
           star_flag=0;
           star_index--;
         }
            
        else if(log_index>0)
        {
            log_index--;
            star_index--;
        }
    }
    
    
    if(key==15)
    {
        CLEAR_DISP_SCREEN;
        main_f=3;
        menu_f=star_index;
    }
    if(key==16)
    {
        CLEAR_DISP_SCREEN;
        main_f=0;
    }
   
    
}
