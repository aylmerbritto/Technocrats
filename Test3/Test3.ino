/*
 * uncomment ps2
 * change rx and tx pins
 * 
*/
int inputpin=A0;
int SensorValues=0;
int outputpin=8;
#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>
Cytron_PS2Shield ps2(2,3);
//Cytron_PS2Shield ps2;
void setup()
{
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  ps2.begin(57600);
}
void loop()
{
  int Select=1,Start=1,Ps2_UP=1,Ps2_LEFT=1,Ps2_DOWN=1,Ps2_RIGHT=1,Ps2_LEFT1=1,Ps2_LEFT2=1,Ps2_RIGHT1=1,Ps2_RIGHT2=1,Ps2_TRIANGLE=1,Ps2_CIRCLE=1,Ps2_CROSS=1,Ps2_SQUARE=1; 
  Select=ps2.readButton(PS2_SELECT);
  Start=ps2.readButton(PS2_START);
  Ps2_UP=ps2.readButton(PS2_UP);
  Ps2_DOWN=ps2.readButton(PS2_DOWN);
  Ps2_RIGHT=ps2.readButton(PS2_RIGHT);
  Ps2_LEFT=ps2.readButton(PS2_LEFT);
  Ps2_LEFT1=ps2.readButton(PS2_LEFT_1);
  Ps2_LEFT2=ps2.readButton(PS2_LEFT_2);
  Ps2_RIGHT1=ps2.readButton(PS2_RIGHT_1);
  Ps2_RIGHT2=ps2.readButton(PS2_RIGHT_2);
  Ps2_TRIANGLE=ps2.readButton(PS2_TRIANGLE);
  Ps2_CIRCLE=ps2.readButton(PS2_CIRCLE);
  Ps2_CROSS=ps2.readButton(PS2_CROSS);
  Ps2_SQUARE=ps2.readButton(PS2_SQUARE);
  SensorValues=analogRead(inputpin);
  Serial.println(SensorValues);
  if(SensorValues<950)
    digitalWrite(4,HIGH);
  else if(Ps2_UP== 0)
  {
  Serial.println("PS2_LEFT");
  digitalWrite(5,HIGH);
  }
  else
  {
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }  
  /*else if(Ps2_UP== 0)
  Serial.println("PS2_UP");
  else if(Ps2_DOWN== 0)
  Serial.println("PS2_DOWN");
  else if(Ps2_LEFT1== 0)
  Serial.println("PS2_LEFT1");
  else if(Ps2_LEFT2== 0)
  Serial.println("PS2_LEFT2");
  else if(Ps2_LEFT2== 0)
  Serial.println("PS2_LEFT2");
  else if(Ps2_RIGHT1== 0)
  Serial.println("PS2_RIGHT1");
  else if(Ps2_RIGHT2== 0)
  Serial.println("PS2_RIGHT2");
  else if(Ps2_CIRCLE==0)
  Serial.println("CIRCLE");
  else if(Ps2_TRIANGLE== 0)
  Serial.println("PS2_TRIANGLE");
  else if(Ps2_CROSS== 0)
  Serial.println("PS2_CROSS");
  else if(Ps2_SQUARE== 0)
  Serial.println("PS2_SQUARE");*/
}

