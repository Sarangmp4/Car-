/*
 * File:   main.c
 * Author: sarang mp
 *
 * Created on 20 May, 2024, 8:12 AM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "adc.h"

static void init_config(void) {
    init_clcd();
    init_matrix_keypad();
    init_adc();
    
    /*printing the headings*/
    clcd_print("  TIME    EV  SP", LINE1(0));
    clcd_print("00:00:00", LINE2(0));

}
char key;
short adc_reg_val;
void main(void) {
    init_config();
    
    char main_f = 0, menu_f = 0;
    
    while (1) {
        key = read_switches(STATE_CHANGE); //reading key
        
        if(main_f == DASHBOARD)
        {
            dashboard();
        }
        else if(main_f == PASSWORD)
        {
            password(key);
        }

        
        
    }
}
        
        







    




