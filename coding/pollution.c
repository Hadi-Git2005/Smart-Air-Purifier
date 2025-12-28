#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=4MHz)



void main()
{
port_b_pullups (TRUE);
   while(TRUE)
   {
   if( !input(PIN_B0) )
{
      output_high(PIN_C0);
      delay_ms(500);
}
else
{
      output_low(PIN_C0);
      delay_ms(500);
}

   }

}
