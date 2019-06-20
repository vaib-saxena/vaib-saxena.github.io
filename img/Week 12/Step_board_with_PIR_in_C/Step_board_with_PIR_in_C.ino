//original code by Neil Gershenfeld , modified by Vaibhav Saxena

#include <avr/io.h>
#include <util/delay.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set
#define bit_delay_time 102 // bit delay for 9600 with overhead
#define bit_delay() _delay_us(bit_delay_time) // RS232 bit delay
#define half_bit_delay() _delay_us(bit_delay_time/2) // RS232 half bit delay
#define char_delay() _delay_ms(10) // char delay
#define position_delay() _delay_ms(1000)

#define serial_port PORTA
#define serial_direction DDRA
#define serial_pin_out (1 << PA0)
#define out_pins PINA
#define out_pin (1 << PA7)
#define PWM_port PORTA
#define PWM_direction DDRA
#define PWM_pin_0 (1 << PA6)


#define loop_count 30

void put_char(volatile unsigned char *port, unsigned char pin, char txchar) {
   //
   // send character in txchar on port pin
   //    assumes line driver (inverts bits)
   //
   // start bit
   //
   clear(*port,pin);
   bit_delay();
   //
   // unrolled loop to write data bits
   //
   if bit_test(txchar,0)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,1)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,2)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,3)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,4)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,5)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,6)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,7)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   //
   // stop bit
   //
   set(*port,pin);
   bit_delay();
   //
   // char delay
   //
   bit_delay();
   }

int main(void) {
   //
   // main
   //
   uint8_t i;
   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
   //
   // initialize serial pin
   //
   set(serial_port,serial_pin_out);
   output(serial_direction,serial_pin_out);
   // set PWM pins to output
   clear(PWM_port, PWM_pin_0);
   output(PWM_direction, PWM_pin_0);
   //
   // main loop
   //
   while (1) {
      //
      if ((out_pins & out_pin) == 0)
         {
          for (i = 0; i < loop_count; ++i) {
         set(PWM_port,PWM_pin_0);
         _delay_us(1500);
         clear(PWM_port,PWM_pin_0);
         _delay_us(18500);
         }
         }
        else
        {
        for (i = 0; i < loop_count; ++i) {
         set(PWM_port,PWM_pin_0);
         _delay_us(700);
         clear(PWM_port,PWM_pin_0);
         _delay_us(19300);
         }
       for (i = 0; i < loop_count; ++i) {
         set(PWM_port,PWM_pin_0);
         _delay_us(2700);
         clear(PWM_port,PWM_pin_0);
         _delay_us(17300);
         }
     }
   }
}
