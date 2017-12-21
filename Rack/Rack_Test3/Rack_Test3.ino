const byte pushButton = 7 ;     //PushButton 
const byte motorPinDir = 6;     //Direction Pin
const byte motorPinPwm = 5;     //PWM pin
int byte pwm=0;

byte dir=1;                     //Motor Direction

byte value=0;                   //Sendor value

void setup() {
  // put your setup code here, to run once:
  for(byte i = 5; i < 7; i++ )
    pinMode(i,OUTPUT) ;
  pinMode(pushButton,INPUT) ;
  Serial.begin(9600) ;
}

void loop() {
  value=digitalRead(pushButton);
  ir=digitalRead(irread);
  if(ir==1)
  ircount++;
  if( value == 1 )
  {
      dir = !dir ;
  }
}
void MotorMotion()
{
    digitalWrite(motorPinDir, dir);
    analogWrite(motorPinPwm, 150) ;
}
void checkir()
