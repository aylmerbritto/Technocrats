#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>
int Select=1,Start=1,Ps2_UP=1,Ps2_LEFT=1,Ps2_DOWN=1,Ps2_RIGHT=1,Ps2_LEFT1=1,Ps2_LEFT2=1,Ps2_RIGHT1=1,Ps2_RIGHT2=1,Ps2_TRIANGLE=1,Ps2_CIRCLE=1,Ps2_CROSS=1,Ps2_SQUARE=1;
Cytron_PS2Shield ps2(2,3);

//Stepper Motor
byte motorPin1 = 8;    // Blue   - 28BYJ48 pin 1
byte motorPin2 = 9;    // Pink   - 28BYJ48 pin 2
byte motorPin3 = 10;    // Yellow - 28BYJ48 pin 3
byte motorPin4 = 11;    // Orange - 28BYJ48 pin 4
                        // Red    - 28BYJ48 pin 5 (VCC)
int a=12;
int c=0;
int f=1;
#define sensor A3

int motorSpeed = 1200;  //variable to set stepper speed
int count = 0;          // count of steps made
int countsperrev =512; // number of steps per full revolution
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
byte buttonPin=6;
int buttonState;
byte pwm1=7;
byte dir1=A0;
int button;
void setOutput(int );
int pos=1;
int step_count=0;

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
  delay(2000);
  
  
//  pinMode(LEDPIN, OUTPUT);
//  digitalWrite(LEDPIN, LOW);
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

  button = digitalRead(buttonPin);
  Serial.println("Button:");
  Serial.print(digitalRead(buttonPin));
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 13*pow(volts, -1); // worked out from datasheet graph
  if(button==1)
  {
    forward();
  }
  else if (button==0)
  {
    Serial.println("Button Hitted");
    step_count=pos;
    pos=0;
    for( ; ; )
    {
      if( count == 128 )
      {    
        break ;
      }    
    clockwise();
    count++ ;
    }
    backward();
    while(pos!=step_count+1)
    {
      Serial.println("Loop Execution Started");
      float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
      int distance = 13*pow(volts, -1); // worked out from datasheet graph
      Serial.println("Distance is:");
      Serial.print(distance);
      while((distance>=4)&&(distance<10))
      {
        Serial.println("Distance has Reduced now");
        float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
        int distance = 13*pow(volts, -1); // worked out from datasheet graph
        flag=1;
        if(distance>10)
        {
          Serial.println("Hand Removed");
          pos+=1;
          Serial.println("The position value now is:");
          Serial.print(pos);
          break;
         }

      }
      Serial.println("Loop Executed");
      delay(200);
    }
    for( ; ; )
    {
      if( count == 256 )
      {
        break ;
      }
      anticlockwise();
      count++;  
    }
    count = 0 ;
   }
}
void anticlockwise()
{
  for(int i = 0; i < 8; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void clockwise()
{
  for(int i = 8; i > 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void backward()
{
  digitalWrite(dir1,LOW);
  analogWrite(pwm1,200);
}

void forward()
{
  digitalWrite(dir1,HIGH);
  analogWrite(pwm1,200);
}


void setOutput(int out)
{
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}
