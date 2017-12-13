/*
 * uncomment ps2
 * change rx and tx pins 
 * 6 5 
 * 10 11
 * 8 9
 * 7 4
*/
#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>
int Select=1,Start=1,Ps2_UP=1,Ps2_LEFT=1,Ps2_DOWN=1,Ps2_RIGHT=1,Ps2_LEFT1=1,Ps2_LEFT2=1,Ps2_RIGHT1=1,Ps2_RIGHT2=1,Ps2_TRIANGLE=1,Ps2_CIRCLE=1,Ps2_CROSS=1,Ps2_SQUARE=1;
Cytron_PS2Shield ps2(2,3);
//Cytron_PS2Shield ps2;
int dir_lf=6;
int dir_rf=4;
int dir_lb=8;
int dir_rb=13;
int pwm_lf=9;
int pwm_rf=5;
int pwm_lb=10;
int pwm_rb=11;
int pwm=255;
void setup()
{
  ps2.begin(9600); 
  // This baudrate must same with the jumper setting at PS2 shield
  //Serial.begin(9600);
  //delay(2000);
  //Serial.println("Initialized"); 
  //pinMode(LEDPIN, OUTPUT);
  //digitalWrite(LEDPIN, LOW);
}
void loop()
{
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
  if(Ps2_LEFT== 0)
  movemotor(pwm,pwm,pwm,pwm,0,0,1,1);
  else if(Ps2_RIGHT== 0)
  movemotor(pwm,pwm,pwm,pwm,1,1,0,0);
  else if(Ps2_UP== 0)
  movemotor(pwm,pwm,pwm,pwm,1,0,1,0);
  else if(Ps2_DOWN== 0)
  movemotor(pwm,pwm,pwm,pwm,0,1,0,1);
  else
  movemotor(0,0,0,0,0,0,0,0);
}
void movemotor(int lf,int lb,int rf,int rb,int dlf,int drf,int dlb, int drb)
{
   digitalWrite(dir_lf,dlf);
  analogWrite(pwm_lf,lf); // Left Forward

  digitalWrite(dir_rf,drf);
  analogWrite(pwm_rf,rf); // Right Forward
  
  digitalWrite(dir_lb,dlb);
  analogWrite(pwm_lb,lb); // Left Backward
  
  digitalWrite(dir_rb,drb);
  analogWrite(pwm_rb,rb); // Right Backward
}
