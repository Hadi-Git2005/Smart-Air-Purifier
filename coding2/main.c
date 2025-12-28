#include <16F877A.h>
#device ADC=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=4MHz)
#include <math.h>


void main()
{
long int value1, value2, diff;
port_b_pullups (TRUE);

  setup_adc_ports(AN0_AN1_AN3);

   while(TRUE)
   {
      //TODO: User Code
set_adc_channel(0);
value1 = read_adc();
delay_ms(10);
set_adc_channel(1);
value2 = read_adc();
delay_ms(10);
diff = abs(value1 - value2);

if(input(pin_b0))  //No rain
{
output_high(pin_d6);   // propleer
if(diff>=200)
{
output_high(pin_d7);   //motor
delay_ms(1000);
output_low(pin_d7);
}
else
{
output_low(pin_d7);
}
}
///////////////////////////////////////
else
{
output_low(pin_d6);
output_low(pin_d7);
}

}
}
