int pwm=3;
int dir=7;
int pushbutton=0;
int value=0;
void setup() {
  Serial.begin(9600);
  pinMode(pushbutton,INPUT);
  pinMode() ;
  pinMode() ;
}

void loop() {
    if(digitalRead(pushbutton)==1)
    value=value+1;
    {
      digitalWrite(dir,1);
      analogWrite(pwm,210);
    }
    else
    {
      digitalWrite(dir,0);
      analogWrite(pwm,120); 
    }    
}
