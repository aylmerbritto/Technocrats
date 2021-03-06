/*
 * uncomment ps2
 * change rx and tx pins
 * 
*/
//Cytron_PS2Shield ps2;
#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>
int Select=1,Start=1,Ps2_UP=1,Ps2_LEFT=1,Ps2_DOWN=1,Ps2_RIGHT=1,Ps2_LEFT1=1,Ps2_LEFT2=1,Ps2_RIGHT1=1,Ps2_RIGHT2=1,Ps2_TRIANGLE=1,Ps2_CIRCLE=1,Ps2_CROSS=1,Ps2_SQUARE=1;
Cytron_PS2Shield ps2(2,3);
//Stepper Motor

byte motorPin1 = 8;                                                                   // Blue   - 28BYJ48 pin 1
byte motorPin2 = 9;                                                                   // Pink   - 28BYJ48 pin 2
byte motorPin3 = 10;                                                                  // Yellow - 28BYJ48 pin 3
byte motorPin4 = 11;                                                                  // Orange - 28BYJ48 pin 4
                                                                                      // Red    - 28BYJ48 pin 5 (VCC)
#define sensor A3                                                                     //Sharp IR connection on the arduino
int motorSpeed = 1200;                                                                //variable to set stepper speed
int count = 0;                                                                        // count of steps made
int countsperrev =512;                                                                // number of steps per full revolution
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
byte buttonPin=6;                                                                     //Pin to which the button is connected
byte pwm1=7;                                                                          //PWM1 pin of cytron for the rack motor
byte dir1=A0;                                                                         //dir0 pin of the cytron for the rack motor
int button;                                                                           //Variable to store the digital state value of the button
void setOutput(int );                                                                 //Used to control the motion of the stepper for the rack mechanism
int flag=1;                                                                           //Used to store the current position where the assembly is currently
int step_count=0;                                                                     //Stores the value of the position where the previous lock was made so the ball can be dropped and new step_count can be set thereafter
int buttonState;
int success=0;
void setup()
{
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(sensor,INPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(dir1,OUTPUT);
  analogWrite(pwm1,0);
  pinMode(buttonPin,INPUT);
  buttonState=0;
  ps2.begin(9600); 
  // This baudrate must same with the jumper setting at PS2 shield
  Serial.begin(9600);
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
  /*if(Ps2_LEFT== 0)
  .
  
  Serial.println("PS2_LEFT");
  else if(Ps2_RIGHT== 0)
  Serial.println("PS2_RIGHT");
  else if(Ps2_UP== 0)
  Serial.println("PS2_UP");
  else if(Ps2_DOWN== 0)
  Serial.println("PS2_DOWN");*/
  if(Ps2_LEFT1== 0)
  {
    rack1();
  }
}
//////////////////////////////////////////////////////////////////////////////
void rack1(){
  success=0;
  while(success==0){
  button = digitalRead(buttonPin);
  Serial.println("Button:");
  Serial.print(digitalRead(buttonPin));
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 13*pow(volts, -1); // worked out from datasheet graph
  if(button==1)
  {
    forward();
  }
  else if (button==0){
    Serial.println("Button Hitted");
    step_count=flag;
   flag=0;
    for( ; ; ){
    if( count == 128 ){    
      break ;
    }    
  clockwise();
  count++ ;
    }
     backward();
    while(flag!=step_count+1){
    Serial.println("Loop Execution Started");
   float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 13*pow(volts, -1); // worked out from datasheet graph
  Serial.println("Distance is:");
  Serial.print(distance);
    while((distance>=4)&&(distance<12)){
      Serial.println("Distance has Reduced now");
      float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 13*pow(volts, -1); // worked out from datasheet graph
      if(distance>10){
        Serial.println("Hand Removed");
        flag+=1;
        Serial.println("The position value now is:");
        Serial.print(flag);
        break;
       }
     }
     
      Serial.println("Loop Executed");
      delay(200);
 }
    for( ; ; ){
    if( count == 256 ){
    break ;
    }
  anticlockwise();
  count++;  
  //Serial.print("Count:");
  //Serial.println(count);
 }
 count = 0 ;
 success=1;
 halt();
 Serial.println("Loop Execution finished");
 return;
  }
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////
void anticlockwise()                                                                   //This function will give the closing of the flap to lock the flap for throwing the next ball there after
{
  for(int i = 0; i < 8; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void clockwise()                                                                        //This Function will open up the flap when the ball is dropped and we start moving backward for the next bal locking
{
  for(int i = 8; i > 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void backward()                                                                         //This function will tell the rack to move backward
{
  digitalWrite(dir1,LOW);
  analogWrite(pwm1,250);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void forward()                                                                           //This Function will tell the rack to move forward
{
  digitalWrite(dir1,HIGH);
  analogWrite(pwm1,250);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void halt()
{
  digitalWrite(dir1,LOW);
  analogWrite(pwm1,0);  
}
void setOutput(int out)                                                                  //Used for controlling the stepper motor 
{
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}

