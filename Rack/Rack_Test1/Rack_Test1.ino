const byte pushButton = 13;     //PushButton 
int motorPinDir = 6;     //Direction Pin
int motorPinPwm = 5;     //PWM pin

int dir=1;                     //Motor Direction

int value=0;                   //Sendor value

void setup() {
  // put your setup code here, to run once:
  for(byte i = 5; i < 7; i++ )
    pinMode(i,OUTPUT) ;
  pinMode(pushButton,INPUT) ;
  Serial.begin(9600) ;

    digitalWrite(motorPinDir, dir);
    analogWrite(motorPinPwm,255) ;
}

void loop() {
  value=digitalRead(pushButton);
  Serial.println(value);
  if( value == 1 )
  {
      dir = !dir ;
  }
    //Serial.println("a");
}
