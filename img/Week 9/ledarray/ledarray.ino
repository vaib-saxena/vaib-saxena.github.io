#define A PA0
#define B PA1
#define C PA2
#define D PA3
#define E PA4

#define DELAY 500

int c[5][4][2] = {
{ {A, B}, {A, C}, {A, D}, {A, E} },
{ {B, A}, {B, C}, {B, D}, {B, E} },
{ {C, A}, {C, B}, {C, D}, {C, E} },
{ {D, A}, {D, B}, {D, C}, {D, E} },
{ {E, A}, {E, B}, {E, C}, {E, D} }
};

int c1[5][4][2] =
  {
    { {A, E}, {B, E}, {C, E}, {D, E} },
    { {A, D}, {B, D}, {E, D}, {C, D} },
    { {E, C}, {A, C}, {D, C}, {B, C} },
    { {E, B}, {D, B}, {C, B}, {A, B} },
    { {E, A}, {D, A}, {C, A}, {B, A} }
  };

int c2[5][4][2] =
  {
    { {B, A}, {C, A}, {D, A}, {E, A} },
    { {A, B}, {C, B}, {D, B}, {E, B} },
    { {A, C}, {B, C}, {D, C}, {E, C} },
    { {A, D}, {B, D}, {C, D}, {E, D} },
    { {A, E}, {B, E}, {C, E}, {D, E} }
  };
int c3[5][4][2] =
  {
    { {D, C}, {D, B}, {C, B}, {B, C} },
    { {A, C}, {A, D}, {B, D}, {C, D} },
    { {D, A}, {C, A}, {B, A}, {A, B} },
    { {E, D}, {E, C}, {E, B}, {E, A} },
    { {A, E}, {B, E}, {C, E}, {D, E} }
  };
  
int times = 0;
int duration = 10;
void setup(){
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
  while ( times < duration )
  {
for(int i=0; i<5; i++)
{
  for(int j=0; j<4; j++)
  {
    light(c1[i][j]);
    }
    delay(1000);
  }
  times++;
  } 
}
