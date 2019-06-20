#include <SoftwareServo.h> // Library to run a servo motor in software for micro controllers which are lacking servo support
#include <SoftwareSerial.h>
#define Rx PA1
#define Tx PA0
SoftwareSerial mySerial(PA1, PA0);
  SoftwareServo myservo1; // initialize servo object
  const int motor1 = PA6;   // Pin for a moto
  const int analogInPin = PA7; 
int sensorValue = 0;
  float pos = 0;

  void setup()
   {
     mySerial.begin(9600);
     myservo1.attach(motor1);  // attach servo object to a motor pin
    
       }
void loop() {
  sensorValue = analogRead(analogInPin);
 if(sensorValue < 50)
 {
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    SoftwareServo::refresh();
    mySerial.print("sensor value : ");
    mySerial.println(sensorValue);
    delay(20);                       // waits 20ms for the servo to reach the position
  }
 }
 else
 {
   {
    myservo1.write(0);             
    SoftwareServo::refresh();        // this keeps the servos updated
    mySerial.print("sensor value : ");
    mySerial.println(sensorValue);
    delay(20);                       // waits 20ms for the servo to reach the position
  }
   }
}
