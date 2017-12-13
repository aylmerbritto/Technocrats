#include<PS2X.h>
PS2X ps2x;
int a;
void setup()
{
    ps2x.config_gamepad(5,4,3,2, false, false);
    pinMode(13,OUTPUT); //pnuematic1Valve1
    pinMode(12,OUTPUT); //pnuematic1Valve2 
    pinMode(11,OUTPUT); //pnuematic2Valve1
    pinMode(10,OUTPUT); //pnuematic2Valve2
    pinMode(9,OUTPUT);  //pnuematic1Valve2
    pinMode(8,OUTPUT);  //gripperHold
    pinMode(7,OUTPUT);  //gripperLeave
}

void loop()
{
  ps2x.read_gamepad();
  if(ps2x.ButtonPressed(PSB_PAD_UP))
  {
    activetepin(13);
  }
  else if(ps2x.ButtonPressed(PSB_PAD_DOWN))
  {
    activetepin(12);
  }
  else if(ps2x.ButtonPressed(PSB_PAD_LEFT))
  {
    activetepin(11);
  }
  else if(ps2x.ButtonPressed(PSB_PAD_RIGHT))
  {
    activetepin(10);
  }
  else if(ps2x.ButtonPressed(PSB_GREEN))
  {
    gripperHold(9);
  }
  
  else if(ps2x.ButtonPressed(PSB_GREEN))
  {
    gripperleave(8); //only single press allowed
  }
}
void activetepin(a)
{
  digitalWrite(a,HIGH);
}
void gripperHold(a)
{
  digitalWrite(a,HIGH);
}
void gripperLeave(a)
{
  digitalWrite(a,LOW);
}

