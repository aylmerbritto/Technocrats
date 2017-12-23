#include <Rack.h>
#include<Wire.h>

Rack rack1(7,8,9,10,11,12,13,'A3'); //Stepper motorPin1,motorPin2,motorPin3,motorPin4,pwm1,dir1,buttonPin,ir sensor
Rack rack2(14,15,16,17,18,19,20,'A4');
Rack rack3(21,22,23,24,25,26,27,'A5');

void receiveEvent(int howmany);

void setup()
{
  Serial.begin(9600);
  Wire.onReceive(5);
}

void loop() 
{
  
}

void receiveEvent(int howmany)
{
  while(Wire.available())
  {
    char c=Wire.read();
    if(c=='r1')
    rack1.Moverack();
    else if(c=='r2')
    rack2.Moverack();
    else if(c=='r3')
    rack2.Moverack();
  }
}

