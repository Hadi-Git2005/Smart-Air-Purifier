#include <16F877A.h>
#device ADC=10

#FUSES NOWDT                     // No Watch Dog Timer
#FUSES PUT                       // Power Up Timer
#FUSES NOBROWNOUT                // No brownout reset
#FUSES NOLVP                     // No low voltage programming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=4MHz)

int1 toggle_direction = 0;        // To toggle motor direction
unsigned int16 motor_run_time = 2000; // Adjust motor run time in milliseconds

void main()
{
   port_b_pullups(TRUE);           // Enable pull-ups on Port B
   set_tris_a(0b11111101);         // Set RA1 as output (Propeller)
   set_tris_b(0xFF);               // Port B as input
   set_tris_d(0x00);               // Port D as output for motor driver

   output_high(PIN_A1);            // Turn on propeller initially

   while (TRUE)
   {
      // Check Rain Sensor (B0)
      if (!input(PIN_B0))         // If B0 is LOW (rain detected)
      {
        output_high(PIN_A1);     // Turn on propeller
         output_low(PIN_D1);      // Turn off motor IN1
         output_low(PIN_D2);      // Turn off motor IN2
         output_low(PIN_D3);      // Turn off motor IN3
         output_low(PIN_D4);      // Turn off motor IN4
         continue;                // Skip the rest of the loop
      }
      else
      {
         output_high(PIN_A1);     // Turn on propeller
      

      // Read Air Quality Sensors (B1 and B2)
      int1 sensor_b1 = input(PIN_B1);
      int1 sensor_b2 = input(PIN_B2);

      if ((sensor_b1 == 0 && sensor_b2 == 1) || (sensor_b1 == 1 && sensor_b2 == 1))
      {
         // Motor runs in the same direction based on toggle state
         if (toggle_direction)
         {
            // Clockwise direction
            output_high(PIN_D1);
            output_low(PIN_D2);
            output_high(PIN_D3);
            output_low(PIN_D4);
         }
         else
         {
            // Anti-clockwise direction
            output_low(PIN_D1);
            output_high(PIN_D2);
            output_low(PIN_D3);
            output_high(PIN_D4);
         }

         delay_ms(motor_run_time); // Run motor for adjustable time
         output_low(PIN_D1);       // Stop motor IN1
         output_low(PIN_D2);       // Stop motor IN2
         output_low(PIN_D3);       // Stop motor IN3
         output_low(PIN_D4);       // Stop motor IN4

         toggle_direction = !toggle_direction; // Toggle direction for next run
      }
      else
      {
         // No motion (both motors off)
         output_low(PIN_D1);
         output_low(PIN_D2);
         output_low(PIN_D3);
         output_low(PIN_D4);
   }}
   }
}
