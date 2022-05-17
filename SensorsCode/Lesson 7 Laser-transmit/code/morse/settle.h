#ifndef __SETTLE_H__
#define __SETTLE_H__

#include <stdio.h>
#include "retrieval.h"
#include <arduino.h>

const int laserPin = 9;
static int dotDelay = 200;
void flashDot(char cha)
{
  digitalWrite(laserPin, HIGH);
  if(cha == '.')
  {
    delay(dotDelay);
  }
  else
  {
    delay(dotDelay * 3);
  }
  digitalWrite(laserPin, LOW);
  delay(dotDelay);
}
void flashSequence(char *sequence)
{
  int i = 0;
  while(sequence[i] != NULL)
  {
    flashDot(sequence[i]);
    i++;
  }
  delay(dotDelay * 3);
}
void morseSignal(char ch)
{
  if(ch >= 'a' && ch <= 'z')
  {
    flashSequence(letters[ch - 'a']);
  }
  else if(ch >= 'A' && ch <= 'Z')
  {
    flashSequence(letters[ch - 'A']);
  }
  else if(ch >= '0' && ch <= '9')
  {
    flashSequence(numbers[ch - '0']);
  }
  else if(ch == ' ')
  {
    delay(dotDelay * 4);
  }
}

#endif
