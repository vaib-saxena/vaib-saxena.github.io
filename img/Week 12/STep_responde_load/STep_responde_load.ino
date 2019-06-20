//
// Touch Slider
// Akash Badshah
//
// 9600 baud FTDI interface
//

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set
#define bit_delay_time 100 // bit delay for 9600 with overhead
#define bit_delay() _delay_us(bit_delay_time) // RS232 bit delay
#define half_bit_delay() _delay_us(bit_delay_time/2) // RS232 half bit delay
#define charge_delay_1() _delay_us(1) // charge delay 1
#define settle_delay() _delay_us(100) // settle delay
#define char_delay() _delay_ms(10) // char delay

#define serial_port PORTA
#define serial_direction DDRA
#define serial_pin_out (1 << PA0)
#define charge_port PORTB
#define charge_direction DDRB
#define charge_pin (1 << PB2)

#define ref (0 << REFS1) | (0 << REFS0) // reference voltage


#define sense1 (0 << MUX2) | (0 << MUX1) | (1 << MUX0) // PA1
#define sense2 (0 << MUX2) | (1 << MUX1) | (0 << MUX0) // PA2
#define sense3 (0 << MUX2) | (1 << MUX1) | (1 << MUX0) // PA3
#define sense4 (1 << MUX2) | (0 << MUX1) | (0 << MUX0) // PA4

#define threshold 750
//Neil's Code to transmit chars
void put_char(volatile unsigned char *port, unsigned char pin, char txchar) {
  //
  // send character in txchar on port pin
  //   assumes line driver (inverts bits)
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

//Check an ADCPin identified by bitmask
int check_pin(unsigned char pin) {
  unsigned char up_lo,up_hi,down_lo,down_hi;
  int up_value, down_value, value;
  
  //
  // set the A/D pin
  //
  ADMUX = ref | pin;
  
  //
  // settle, charge, and wait 1
  //
  settle_delay();
  set(charge_port, charge_pin);
  charge_delay_1();
  //
  // initiate conversion
  //
  ADCSRA |= (1 << ADSC);
  //
  // wait for completion
  //
  while (ADCSRA & (1 << ADSC))
    ;
  //
  // save result
  //
  up_lo = ADCL;
  up_hi = ADCH;
  //
  // settle, discharge, and wait 1
  //
  settle_delay();
  clear(charge_port, charge_pin);
  charge_delay_1();
  //
  // initiate conversion
  //
  ADCSRA |= (1 << ADSC);
  //
  // wait for completion
  //
  while (ADCSRA & (1 << ADSC))
    ;
  //
  // save result
  //
  down_lo = ADCL;
  down_hi = ADCH;
  //
  // process result
  //
  up_value = 256 * up_hi + up_lo;
  down_value = 256 * down_hi + down_lo;
  value = (up_value + (1023 - down_value)) / 2; 
  return threshold - value <= 0 ? 0 : threshold - value;
  
}
void print_int(int value) {
  char str[4] = "    ";
  itoa(value, str, 10);
  int i;
  for(i=0; i<4; i++)
  {
    put_char(&serial_port, serial_pin_out, str[i]);
    char_delay();
  }
}
int main(void) {
  //
  // main
  //
  //
  // set clock divider to /1
  //
  CLKPR = (1 << CLKPCE);
  CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
  //
  // initialize output pins
  //
  set(serial_port, serial_pin_out);
  output(serial_direction, serial_pin_out);
  clear(charge_port, charge_pin);
  output(charge_direction, charge_pin);
  //
  // init A/D
  //
  ADMUX = ref; // Vcc ref
  ADCSRA = (1 << ADEN) // enable
    | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // prescaler /128
  ADCSRB = (0 << ADLAR); // right adjust

  int measurements[4];
  //
  // main loop
  //
  while (1) {
  
    // sense pins
    //
    
    measurements[1] = check_pin(sense1); 
    print_int(measurements[1]);
      put_char(&serial_port, serial_pin_out, '\r');
      char_delay();
      put_char(&serial_port, serial_pin_out, '\t');
      char_delay();
    measurements[2] = check_pin(sense2); 
    print_int(measurements[2]);
      put_char(&serial_port, serial_pin_out, '\r');
      char_delay();
      put_char(&serial_port, serial_pin_out, '\t');
      char_delay();
    measurements[3] = check_pin(sense3); 
    print_int(measurements[3]);
      put_char(&serial_port, serial_pin_out, '\r');
      char_delay();
      put_char(&serial_port, serial_pin_out, '\t');
      char_delay();
    measurements[4] = check_pin(sense4); 
    print_int(measurements[4]);
      put_char(&serial_port, serial_pin_out, '\r');
      char_delay();
      put_char(&serial_port, serial_pin_out, '\n');
      char_delay();
  }
}
