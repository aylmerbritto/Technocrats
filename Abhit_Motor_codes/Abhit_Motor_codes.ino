#include <Cytron_PS2Shield.h>
int Select=1,Start=1,Ps2_UP=1,Ps2_LEFT=1,Ps2_DOWN=1,Ps2_RIGHT=1,Ps2_LEFT1=1,Ps2_LEFT2=1,Ps2_RIGHT1=1,Ps2_RIGHT2=1,Ps2_TRIANGLE=1,Ps2_CIRCLE=1,Ps2_CROSS=1,Ps2_SQUARE=1;
Cytron_PS2Shield ps2(2,3);
int lsa=A0;

int maxspeed=200;
//int junc=13;
//int junction=0;
int dir_lf=10;
int dir_rf=6;
int dir_lb=8;
int dir_rb=4;
int pwm_lf=11;
int pwm_rf=5;
int pwm_lb=9;
int pwm_rb=7;
int positionx=0;
int setpoint=35;



void setup() {
  // put your setup code here, to run once:
  pinMode(lsa,INPUT);
  Serial.begin(9600);
  ps2.begin(9600);
}

void loop() {
    
  //movemotor(40,40,40,40,0,0);
  // put your main code here, to run repeatedly:
 /* positionx=analogRead(lsa);
  positionx=((float)positionx/921)*70;
  pidcalc();
  pidcalcturn();*/
  char inp=Serial.read();
  if(inp=='f'){
    movemotor(40,40,40,40,1,1,0,0);
    Serial.println("f");
  }
  else if(inp=='b'){
    movemotor(0,0,0,0,0,0,0,0);
  }
  else if(inp=='l'){
    movemotor(40,40,40,40,0,1,0,1);
  }
  else if(inp=='r'){
   movemotor(40,40,40,40,1,0,1,0);
  }
  else if(inp=='s'){
    movemotor(0,0,0,0,0,0,0,0);
  }
  else if(inp=='t'){
    movemotor(50,50,50,50,1,0,0,1);
  }
  else if (inp=='q'){
    for(int i=0;i<5;i++){
    movemotor(40,40,40,40,1,0,1,0);
    delay(1000);
    movemotor(40,40,40,40,0,1,0,1);
    delay(1000);
    }
    movemotor(0,0,0,0,0,0,0,0);
  }
}

void movemotor(int lf,int lb,int rf,int rb,int dlf,int drf,int dlb, int drb){
   digitalWrite(dir_lf,dlf);
  analogWrite(pwm_lf,lf); // Left Forward

  digitalWrite(dir_rf,drf);
  analogWrite(pwm_rf,rf); // Right Forward
  
  digitalWrite(dir_lb,dlb);
  analogWrite(pwm_lb,lb); // Left Backward
  
  digitalWrite(dir_rb,drb);
  analogWrite(pwm_rb,rb); // Right Backward
}

int i=0;
int p=0;
int d=0;
int lp=0;
int error=0;
int kp=0;
int ki=0;
int kd=0;

void pidcalc(){
  p= positionx-setpoint;
  i= i+p;
  d=p-lp;
  error=kp*p+ki*i+kd*d; 
}

/*void pidcalcturn(){
  if (error<-40){
    error=-40;
  }
  else if (error>40){
    error=40;
  }
  if (error<0){
    rf=maxspeed-error/2;
    rb=maxspeed-error/2;
    lf=maxspeed+error/2;
    lb=maxspeed+error/2;
  }
  else{
    rf=maxspeed-error/2;
    rb=maxspeed-error/2;
    lf=maxspeed+error/2;
    lb=maxspeed+error/2;
  }
}*/
