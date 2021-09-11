/*
 * File:   buzzwire_firmware.c
 * Author: liyanage kalana perera
 *
 * Created on August 28, 2021, 10:06 PM
 */
// PIC12F675 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
//#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High speed crystal/resonator on GP4/OSC2/CLKOUT and GP5/OSC1/CLKIN)
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = ON          // Code Protection bit (Program Memory code protection is enabled)
#pragma config CPD = ON         // Data Code Protection bit (Data memory code protection is enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 4000000
/*
 * 
 */

#define wire_input GPIObits.GPIO0
#define green_out GPIObits.GPIO1
#define red_out GPIObits.GPIO2
#define reset_ GPIObits.GPIO4

int game_over = 0;
void main()
{
// OSCCALbits.CAL = 0xFF;// Set Maximum Oscillator frequency.
 ANSEL = 0x00;
 CMCONbits.CM = 0x07;
 TRISIObits.TRISIO0 = 1;
 TRISIObits.TRISIO1 = 0;
 TRISIObits.TRISIO2 = 0;
 TRISIObits.TRISIO4 = 1;
 GPIO = 0x00;
 __delay_ms(10);
 // Initializing the game.
 for(int i=0;i<3;i++)
     {
         red_out = 1;
         __delay_ms(500);
         red_out = 0;
         __delay_ms(500);
     }
 while(1)
 {
     START:
     while(wire_input != 1 && game_over == 0)
     {
         green_out = 1;
         red_out = 0;
     }
     game_over = 1;
     green_out = 0;
     red_out = 1;
     if(reset_ == 1)
     {
         __delay_ms(10);
        if(reset_ == 0)
        {
            __delay_ms(1000);
            game_over = 0;
            green_out = 0;
            for(int i=0;i<3;i++)
            {
                red_out = 1;
                __delay_ms(500);
                red_out = 0;
                __delay_ms(500);
            }
            goto START;
        }
     }
 }
}