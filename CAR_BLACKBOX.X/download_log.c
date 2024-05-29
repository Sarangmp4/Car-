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


extern char lap;
extern char overflow;
extern char main_f;


char download_array[11];
char start = 0;

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


        for (int j = 0; j < 10; j++) {
            download_array[j] = read_external_eeprom((start + last) % 10 * 10 + j);
        }

        putch(download_array[0]);
        putch(download_array[1]);
        putch(':');
        putch(download_array[2]);
        putch(download_array[3]);
        putch(':');
        putch(download_array[4]);
        putch(download_array[5]);
        putch(' ');

        /*event*/
        putch(download_array[6]);
        putch(download_array[7]);
        putch(' ');

        /*speed*/
        putch(download_array[8]);
        putch(download_array[9]);

        puts("\n\r");

    }
    main_f = 2;

}