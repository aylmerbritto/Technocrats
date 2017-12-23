
#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>
#include<Wire.h>

int Select=1,Start=1,Ps2_UP=1,Ps2_LEFT=1,Ps2_DOWN=1,Ps2_RIGHT=1,Ps2_LEFT1=1,Ps2_LEFT2=1,Ps2_RIGHT1=1,Ps2_RIGHT2=1,Ps2_TRIANGLE=1,Ps2_CIRCLE=1,Ps2_CROSS=1,Ps2_SQUARE=1;
int pwmx=0,pwmy=0,rx=0,ly=0;
Cytron_PS2Shield ps2(2,3);
//Cytron_PS2Shield ps2;

#define pwm 200

void communicate(char message);

class BaseMotor
{
  public:
    int lf,lb,rf,rb,dlf,drf,dlb,drb;
    int dir_lf=6,dir_rf=4,dir_lb=8,dir_rb=13,pwm_lf=9,pwm_rf=5,pwm_lb=10,pwm_rb=11;
    void movemotor(int lf,int lb,int rf,int rb,int dlf,int drf,int dlb, int drb);
}m;

void setup()
{
  ps2.begin(9600); 
  Wire.begin();
  delay(2000);
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
  rx=128-ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS);
  ly=128-ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS);
  pwmx=map(rx,0,128,0,255);
  pwmy=map(ly,0,128,0,255);  
  if(Ps2_LEFT== 0)
    m.movemotor(150,150,150,150,0,0,1,1);
  else if(Ps2_RIGHT== 0)
    m.movemotor(150,150,150,150,1,1,0,0);
  else if(Ps2_UP== 0)
    m.movemotor(30,30,30,30,1,1,0,0);
  else if(Ps2_DOWN== 0)
    m.movemotor(30,30,30,30,0,0,1,1);
  else if (Ps2_TRIANGLE==0)
    //rack1
    communicate('r1');
  else if(Ps2_CIRCLE==0)
    //rack2
    communicate('r2');
  else if(Ps2_CROSS==0)
    //rack3
    communicate('r3');
  else if(Ps2_SQUARE==0)
    //pnuematics
    communicate('r4');
  else if(Ps2_LEFT1==0)
    //transfer
    communicate('r4');
  else if(Ps2_LEFT2==0)
    //transfer
    communicate('r4');
  else if (Ps2_RIGHT1==0)
    //
    communicate('r4');
  else if(Ps2_RIGHT2==0)
    //
    communicate('r4');
  else if(pwmy>10)
    m.movemotor(pwmy,pwmy,pwmy,pwmy,1,1,1,1);
  else if(pwmy<-10)
    m.movemotor(-pwmy,-pwmy,-pwmy,-pwmy,0,0,0,0);
  else if(pwmx>10)
    m.movemotor(pwmx,pwmx,pwmx,pwmx,1,0,0,1);
  else if(pwmx<-10)
    m.movemotor(-pwmx,-pwmx,-pwmx,-pwmx,0,1,1,0);  
  else
    m.movemotor(0,0,0,0,0,0,0,0);
}

void BaseMotor::movemotor(int lf,int lb,int rf,int rb,int dlf,int drf,int dlb, int drb)
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

void communicate(char message)
{
  Wire.beginTransmission(5);
  Wire.write(message);
  Wire.endTransmission();
}

