#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=4MHz)


int1 toggle_direction = 0;        // To toggle motor direction
unsigned int16 motor_run_time = 15000; // Adjust motor run time in milliseconds
int i=0;
void main()
{
  int i=0;
   port_b_pullups(TRUE);// Enable pull-ups on Port B

   output_high(PIN_C7);            // Turn on propeller initially

   while (TRUE)
   {
      if (i>0)
      {
         delay_ms(60000);
         }
      i++;// Check Rain Sensor (B0)
      if (!input(PIN_B0))         // If B0 is LOW (rain detected)
      {
         output_low(PIN_C7);     // Turn off propeller
         output_low(PIN_D4);      // Turn off motor IN1
         output_low(PIN_D5);      // Turn off motor IN2
         output_low(PIN_D6);      // Turn off motor IN3
         output_low(PIN_D7);      // Turn off motor IN4
                      // Skip the rest of the loop
      }
      else
      {
         output_high(PIN_C7);     // Turn on propeller


      // Read Air Quality Sensors (B1 and B2)
      int1 sensor_b1 = input(PIN_B1);
      int1 sensor_b2 = input(PIN_B2);


      if ((sensor_b1 == 0 && sensor_b2 == 1) || (sensor_b1 == 0 && sensor_b2 == 0))
      {
         // Motor runs in the same direction based on toggle state
         if (toggle_direction)
         {
            // Clockwise direction
            output_high(PIN_D4);
            output_low(PIN_D5);
            output_high(PIN_D6);
            output_low(PIN_D7);
         }
         else
         {
            // Anti-clockwise direction
            output_low(PIN_D4);
            output_high(PIN_D5);
            output_low(PIN_D6);
            output_high(PIN_D7);
         }

         delay_ms(motor_run_time); // Run motor for adjustable time
         output_low(PIN_D4);       // Stop motor IN1
         output_low(PIN_D5);       // Stop motor IN2
         output_low(PIN_D6);       // Stop motor IN3
         output_low(PIN_D7);       // Stop motor IN4

         toggle_direction = !toggle_direction; // Toggle direction for next run
      }
      else
      {
         // No motion (both motors off)
         output_low(PIN_D4);
         output_low(PIN_D5);
         output_low(PIN_D6);
         output_low(PIN_D7);
      }}
   }
}

