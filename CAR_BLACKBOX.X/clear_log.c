/*
 * File:   clear_log.c
 * Author: sarang mp
 *
 * Created on 28 May, 2024, 8:14 PM
 */


extern char lap;
#include <xc.h>
#include "main.h"
#include"clcd.h"

void clear_log(char key)
{
    lap=0; //clear and store 
    clcd_print("   LOG CLEARED   ",LINE1(0));
    clcd_print("                 ",LINE2(0));
    
 
   
}