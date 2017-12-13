#include <PS2X_lib.h>
PS2X ps2x;
#define PS2_DAT        13 
#define PS2_CMD        11 
#define PS2_SEL        10  
#define PS2_CLK        12  
int green=0;  int red=0; int blue=0; int pink=0;
int L1=0; int L2=0; int R1=0; int R2=0;
int UP=0; int DOWN=0; int LEFT=0; int RIGHT=0;
int SELECT=0; int START=0;
void setup() {
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
  Serial.begin(9600);
  delay(5000);
  Serial.print("Controller Initialised");
}
void loop() 
{
   ps2x.read_gamepad();
   green=ps2x.ButtonPressed(PSB_GREEN);
   red=ps2x.ButtonPressed(PSB_RED);
   blue=ps2x.ButtonPressed(PSB_BLUE);
   pink=ps2x.ButtonPressed(PSB_PINK);
   L1=ps2x.ButtonPressed(PSB_L1);
   L2=ps2x.ButtonPressed(PSB_L2);
   R1=ps2x.ButtonPressed(PSB_R1);
   R2=ps2x.ButtonPressed(PSB_R2);
   UP=ps2x.ButtonPressed(PSB_PAD_UP);
   DOWN=ps2x.ButtonPressed(PSB_PAD_DOWN);
   LEFT=ps2x.ButtonPressed(PSB_PAD_LEFT);
   RIGHT=ps2x.ButtonPressed(PSB_PAD_RIGHT);
   SELECT=ps2x.ButtonPressed(PSB_SELECT);
   START=ps2x.ButtonPressed(PSB_START);
   if(green==1)
   {
      if(L1==1)
        Serial.println("Pnuematic one is activated");
      else if(L2==1)
        Serial.println("Pnuematic two is activated");
   }
}
