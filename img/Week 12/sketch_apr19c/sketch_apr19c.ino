#include <CapacitiveSensor.h>
#include "SoftwareSerial.h"

const int rx=PB0;
const int tx=PB2;

SoftwareSerial mySerial(rx, tx);
CapacitiveSensor   cs_4_2 = CapacitiveSensor(PB2,PA1);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired. 

void setup()
{
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
    mySerial.begin(9600);        //  Begins Serial Communication at 9600baud.
}

void loop()
{
 
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(1000);

    mySerial.print(millis() - start);        // check on performance in milliseconds
    mySerial.print("\t");                    // tab character for debug window spacing
    mySerial.println(total1);                  // Sends the value of total1 to the Serial window of the computer

}
  
