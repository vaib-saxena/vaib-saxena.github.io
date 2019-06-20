 #include <SoftwareServo.h> // Library to run a servo motor in software for micro controllers which are lacking servo support

  SoftwareServo myservo1; // initialize servo object
  SoftwareServo myservo2; // initialize servo object
  const int motor1 = PA6;   // Pin for a motor
  const int motor2 = PA7;   // Pin for a motor
  float pos = 0;

   // setup function runs once on startup of the microcontroller
   void setup()
   {
     myservo1.attach(motor1);  // attach servo object to a motor pin
     myservo2.attach(motor2);  // attach servo object to a motor pin
       }

   void loop() {

    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos);
    SoftwareServo::refresh();
    delay(20);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees

    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos);
    SoftwareServo::refresh();        // this keeps the servos updated
    delay(20);                       // waits 15ms for the servo to reach the position
  }
   }
  
