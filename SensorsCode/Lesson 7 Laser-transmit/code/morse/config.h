#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <arduino.h>

void Initial(void)
{
  pinMode(laserPin, OUTPUT);
  Serial.begin(9600);
}

#endif