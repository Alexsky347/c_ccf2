/*
 * File:   ex2.c
 * Author: alex
 *
 * Created on February 24, 2022, 9:09 AM
 */

#include <xc.h>
#include <pic18f8722.h>
#include "config_bits.h"
#include "fonctions_LCD.h"
#define _XTAL_FREQ 10000000 
#include <stdio.h>

// exercice 1

int temp = 30;

void initPortTOR()
{
    TRISD = 0; // RD0 en sortie
    TRISBbits.TRISB0 = 1; //RB0 en entree
    TRISAbits.TRISA5 = 1; //RB0 en entree
    ADCON1 = 0b00001110;  // vref+/vref- = vdd/vss RA0 entre ana Ra1-Ra7 IO TOR
}

int testBtnPressed()
{
    if(temp < 40 || temp >= 20){
        if(PORTBbits.RB0 == 0 || PORTAbits.RA5 == 0) // RD0 appuye)
        {
            __delay_ms(20);
            if(PORTBbits.RB0 == 0)
            {
                 temp++;
            }
            else
            {
                if(PORTAbits.RA5 == 0)
                {
                    temp--;

                }

            }
        }
        return temp;
    }
    
}


void ex2(void) 
{

    int L_ret = 0;
    initPortTOR();
    lcdInit();

    while(1) //boucle infinie
    {
        L_ret = testBtnPressed();
        
        //led allumée
        PORTD= L_ret % 10 ;
         lcdGoToLC(1,0);

         switch(L_ret)
         {
             case 1:
               LCDPutStr("Btn 1 ON        ");
               break;
             case 2: 
               LCDPutStr("Btn 2 ON        ");
               break;
             default :
               LCDPutStr("Btn 1 et 2 OFF  ");
               break; 
         }
        __delay_ms(100);
    }
}
