#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>

Cytron_PS2Shield ps2(2, 3);
int rx=0,ly=0;
int Select=1,Start=1,Ps2_UP=1,Ps2_LEFT=1,Ps2_DOWN=1,Ps2_RIGHT=1,Ps2_LEFT1=1,Ps2_LEFT2=1,Ps2_RIGHT1=1,Ps2_RIGHT2=1,Ps2_TRIANGLE=1,Ps2_CIRCLE=1,Ps2_CROSS=1,Ps2_SQUARE=1;
int pwmx=0;
int pwmy=0;
int dir_lf=6;
int dir_rf=4;
int dir_lb=8;`
int dir_rb=13;
int pwm_lf=9;
int pwm_rf=5;
int pwm_lb=10;
int pwm_rb=11;
void setup()
{
  ps2.begin(9600); // This baudrate must same with the jumper setting at PS2 shield
  Serial.begin(9600); // Set monitor baudrate to 9600
}

void loop()
{
  rx=128-ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS);
  ly=128-ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS);
  pwmx=map(rx,0,128,0,255);
  pwmy=map(ly,0,128,0,255);
  if(pwmy>10)
  {
    movemotor(pwmy,pwmy,pwmy,pwmy,1,0,1,0);
  }
  else if(pwmy<-10)
  {
    movemotor(-pwmy,-pwmy,-pwmy,-pwmy,0,1,0,1);
  }
  else if(pwmx>10)
  {
    movemotor(pwmx,pwmx,pwmx,pwmx,0,0,1,1);
  }
  else if(pwmx<-10)
  {
    movemotor(-pwmx,-pwmx,-pwmx,-pwmx,1,1,0,0);
  }
  else
  {
    movemotor(0,0,0,0,0,0,0,0);
  }
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
