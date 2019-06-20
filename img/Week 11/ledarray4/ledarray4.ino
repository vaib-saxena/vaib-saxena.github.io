#include <SoftwareSerial.h>
#define RX PA3
#define TX PA2

SoftwareSerial mySerial(PA3, PA2); // RX, TX
#define A PA0
#define B PA1
#define C PA2
#define D PA3
#define E PA4
#define trigPin PA7

int c2[5][4][2] =
  {
    { {B, A}, {C, A}, {D, A}, {E, A} },
    { {A, B}, {C, B}, {D, B}, {E, B} },
    { {A, C}, {B, C}, {D, C}, {E, C} },
    { {A, D}, {B, D}, {C, D}, {E, D} },
    { {A, E}, {B, E}, {C, E}, {D, E} }
  };

int distance;
int duration;
void setup(){
  mySerial.begin(9600);
  pinMode( A, INPUT );
  pinMode( B, INPUT );
  pinMode( C, INPUT );
  pinMode( D, INPUT );
  pinMode( E, INPUT );
}


void light( int pins[2] ){
  pinMode( pins[0], OUTPUT );
  digitalWrite( pins[0], HIGH ); //making anode HIGH

  pinMode( pins[1], OUTPUT );
  digitalWrite( pins[1], LOW ); //making cathode LOW
}


void loop()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);
    pinMode(trigPin, INPUT);
    duration = pulseIn(trigPin, HIGH);
    distance = duration/58.2;
 if(duration<100)
 {
for(int i=0; i<5; i++)
{
  for(int j=0; j<4; j++)
  {
    light(c2[i][j]);
    }
    delay(10);
  } 
}
else
 {
for(int i=0; i<5; i++)
{
  for(int j=0; j<4; j++)
  {
    light(c2[i][j]);
    }
    delay(50);
  } 
}
}
