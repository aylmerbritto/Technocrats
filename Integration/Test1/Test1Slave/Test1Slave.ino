#include <Rack.h>
#include<Wire.h>

Rack rack1(7,8,9,10,11,12,13,'A3');
Rack rack2();
Rack rack3();

void setup()
{
  Serial.begin(9600);
}

void loop() 
{
  
}

void receiveEvent(int howmany)
{
  while(Wire.available())
}

