/*
 * File:   download_log.c
 * Author: sarang mp
 *
 * Created on 29 May, 2024, 11:54 AM
 */

#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "uart.h"
#include "external_eeprom_2.h"

extern char store[11];
extern unsigned char time[9];
extern char lap;
extern char overflow;
extern char main_f;
extern unsigned short adc_reg_val;
extern char i;

char download_array[11];
extern char lap;
char start = 0;
extern char *events[8];

char var;
char last;

void download_log() {
    clcd_print("  Download Log   ", LINE1(0));
    clcd_print(" SUCCESSFULL ", LINE2(3));



    if (overflow == 1) {
        var = 10;
    }
    if (overflow == 0) {
        var = lap;
    }

    puts("# TIME   EV   SP \n\r");

    for (last = 0; last < var; last++) {


        for (int j = 0; j < 5; j++) {
            download_array[j] = read_external_eeprom((start + last) % 10 * 10 + j);
        }

        putch(download_array[0]/10+48);
        putch(download_array[0]%10+48);
        putch(':');
        putch(download_array[1]/10+48);
        putch(download_array[1]%10+48);
        putch(':');
        putch(download_array[2]/10+48);
        putch(download_array[2]%10+48);
        putch(' ');

        /*event*/
        puts(events[download_array[3]]);
        putch(' ');

        /*speed*/
        putch(download_array[4]/10+48);
        putch(download_array[4]%10+48);

        puts("\n\r");

    }


    /*storing event mode*/
    /*storing time*/
    store[0]=(((time[0]-48)*10)+(time[1]-48)); 
    store[1]=(((time[3]-48)*10)+(time[4]-48));
    store[2]=(((time[6]-48)*10)+(time[7]-48));
   
    /*storing event mode*/
    store[3]=i;
    
    /*storing speed*/
    store[4]=adc_reg_val;

    for (char k = 0; k < 5; k++) {
        write_external_eeprom((k), store[k]);
    }
    //lap++;


    main_f = 2;

}
