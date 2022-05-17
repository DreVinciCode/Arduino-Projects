#include "color.h"
#include "rgb.h"
#include "buzzer.h"

int band = 70;

void setup()
{
  pinMode(8, OUTPUT);//the buzzer pin attach to
  pinMode(9, OUTPUT);//the r pin of the RGB attach to 
  pinMode(10, OUTPUT);//the g pin of the RGB attach to 
  pinMode(11, OUTPUT);//the b pin of the RGB attach to 
}

void loop()
{
  int potVal = analogRead(A1);
  int senVal = analogRead(A0);
  if(senVal < potVal - band)
  {
    setColor(9, 10, 11, Blue);
  }
  else if(senVal > potVal + band)
  {
    setColor(9, 10, 11, Red);
    beep(8);
  }
  else
  {
    setColor(9, 10, 11, Green);
  }
}
