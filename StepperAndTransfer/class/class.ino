class Rack
{
  public:
    Rack(byte motorPin1,byte motorPin2,byte motorPin3,byte motorPin4,byte pwm1,byte dir1,byte buttonPin,char sensor);    
    void setOutput(int );                                                                                              //Used to control the motion of the stepper for the rack mechanism
    void Moverack();
    void anticlockwise();                                                                                               //This function will give the closing of the flap to lock the flap for throwing the next ball there after
    void clockwise();                                                                                                   //This Function will open up the flap when the ball is dropped and we start moving backward for the next bal locking
    void backward();                                                                                                    //This function will tell the rack to move backward
    void forward();                                                                                                     //This Function will tell the rack to move forward
    void halt();
    void setOutput(int out);                                                                                            //Used for controlling the stepper motor 
};

Rack::Rack(byte motorPin1,byte motorPin2,byte motorPin3,byte motorPin4,byte pwm1,byte dir1,byte buttonPin,char sensor)
{ 
  sensor= sensor;motorPin1=motorPin1;motorPin2=motorPin2;motorPin3=motorPin3;motorPin4=motorPin4;pwm1=pwm1;dir1=dir1;buttonPin=buttonPin;sensor=sensor;
  int motorSpeed = 1200;                                                                                                //variable to set stepper speed
  int count = 0;                                                                                                        // count of steps made
  int countsperrev =512;                                                                                                // number of steps per full revolution
  int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
  int button;                                                                                                           //Variable to store the digital state value of the button
  int flag=1;                                                                                                           //Used to store the current position where the assembly is currently
  int step_count=0;                                                                                                     //Stores the value of the position where the previous lock was made so the ball can be dropped and new step_count can be set thereafter
  int buttonState=0;                                                                                                    //Tells us whehter the switch is on or not
  int success=0;                                                                  
  pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);
  pinMode(motorPin3,OUTPUT);
  pinMode(motorPin4,OUTPUT);
  pinMode(pwm1,OUTPUT);                                                                                                  //Rack's Main Motor's PWM
  pinMode(dir1,OUTPUT);                                                                                                  //Rack's Main Motor's dir         
  pinMode(buttonPin,INPUT);
  pinMode(sensor,INPUT);
}

void Rack::Moverack()()
{
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
  else if (button==0)
  {
    Serial.println("Button Hitted");
    step_count=flag;
    flag=0;
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
    while(flag!=step_count+1)
    {
      Serial.println("Loop Execution Started");
      float volts = analogRead(sensor)*0.0048828125;                                                                        // value from sensor * (5/1024)
      int distance = 13*pow(volts, -1);                                                                                     // worked out from datasheet graph
      Serial.println("Distance is:");
      Serial.print(distance);
      while((distance>=4)&&(distance<12))
      {
        Serial.println("Distance has Reduced now");
        float volts = analogRead(sensor)*0.0048828125;                                                                      // value from sensor * (5/1024)
        int distance = 13*pow(volts, -1);                                                                                   // worked out from datasheet graph
        if(distance>10)
        {
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
 for( ; ; )
 {
    if( count == 256 )
    {
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

void Rack::anticlockwise()                                                                   //This function will give the closing of the flap to lock the flap for throwing the next ball there after
{
  for(int i = 0; i < 8; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void Rack::clockwise()                                                                        //This Function will open up the flap when the ball is dropped and we start moving backward for the next bal locking
{
  for(int i = 8; i > 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void Rack::backward()                                                                         //This function will tell the rack to move backward
{
  digitalWrite(dir1,LOW);
  analogWrite(pwm1,250);
}

void Rack::forward()                                                                           //This Function will tell the rack to move forward
{
  digitalWrite(dir1,HIGH);
  analogWrite(pwm1,250);
}

void Rack::halt()
{
  digitalWrite(dir1,LOW);
  analogWrite(pwm1,0);  
}

void Rack::setOutput(int out)                                                                  //Used for controlling the stepper motor 
{
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}
