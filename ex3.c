/*
 * File:   ex3.c
 * Author: alex
 *
 * Created on February 24, 2022, 9:09 AM
 */


#include "config_bits.h"
#include <pic18f8722.h>
#include <stdio.h>
#include "fonctions_LCD.h"
#define _XTAL_FREA 10000000
#define UREF 5

int temp = 30;

void ex3(void) {
    unsigned short int  L_ValeurMesureCan=0; 
    volatile float L_Tension_Can=2.5f;  
     lcdInit();

       PIR1bits.ADIF = 0;
       PIE1bits.ADIE = 0;
       INTCONbits.PEIE = 0;
       ADCON0 = 0x01;
       ADCON1 = 0x0E;
       ADCON2 = 0x89;

   while(1)
       {

        char L_strTension[25];
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO ==1);//   BusyADC());
        L_ValeurMesureCan = (unsigned short int)((ADRESH<<8)|(ADRESL));
        L_Tension_Can=((float)L_ValeurMesureCan * UREF)/1024;
        sprintf (L_strTension,"U =%2.1f   ",L_Tension_Can);
         lcdGoToLC(0,0);
          LCDPutStr(L_strTension);   
        __delay_ms(1000);
        
        // temperature élevée
        if(L_Tension_Can > temp){
            
        }
        
        // temperature basse
        if(L_Tension_Can < temp){
            
        }
        
       }
}
