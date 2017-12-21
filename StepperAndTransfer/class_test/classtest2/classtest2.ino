#include <Rack.h>

Rack rack1(7,8,9,10,11,12,13,'A3');

void setup()
{
  Serial.begin(9600);

}

void loop() 
{
  rack1.Moverack();
}
