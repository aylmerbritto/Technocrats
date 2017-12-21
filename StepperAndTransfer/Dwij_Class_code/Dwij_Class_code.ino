byte motorPin1 = 8,motorPin2 = 9,motorPin3 = 10,motorPin4 = 11;
int a=12,c=0,flag=0,f=1;

#define sensor A3



int motorSpeed = 1200,pos=1,count = 0,countsperrev =512;lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
byte buttonPin=6,buttonState,pwm1=7,dir1=A0;
int button;

void setOutput(int );
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

  Serial.begin(9600);

}



//////////////////////////////////////////////////////////////////////////////

void loop()
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
